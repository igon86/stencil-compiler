import config

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.53$"

import numpy as np
import util

from point import *
from TreeNode import *

import time

import pdb

def chooseWinner(x,y):
    ''' This function is a reduce function which just return the best point for code generation
        coolness is a point property and depends on the section that the point lives in
        
    '''
    if (x.coolness() == y.coolness()):
        #this should  be changed
        return x
    elif (x.coolness() < y.coolness()):
        return y
    else:
        return x

def tagToIndex(tag):
    ''' map a n-dimensional tag of a section into an index in a one dimensional domain'''
    out = 0
    for index,item in enumerate(reversed(tag)):
        out += item * pow(3,index)
    return out

class Section(object):

    #tricky magari ripensaci con un iteratore
    def orecursiveInit(self,element,level,coordinate):
        #print "ELEMENT:\n"+ str(element) + "\nLEVEL:\n" +str(level) + "\nCOORDINATE\n" +str(coordinate)
        if element is not None:
            for index, item in enumerate(element):
                #print "sono nella recursiveInit" ,index,item,element
                coordinate.append(index)
                isLast = self.orecursiveInit(item,level+1,coordinate)
                if isLast:
                    #print "sto per modificare", str(element[index])
                    p = SectionPoint(copy.deepcopy(coordinate), util.addList(coordinate , self.outsideCoordinates),self,True)
#                    if self.minPoint is None or p < self.minPoint:
#                        self.minPoint = p
#                    if self.maxPoint is None or p > self.maxPoint:
#                        self.MaxPoint = p
                    element[index] = p
                    #print "stampo cosa ho fatto: " + str(element[index])
                    #print self
                coordinate.pop()
            return False
        else:
            return True

    #tricky magari ripensaci con un iteratore
    def recursiveInit(self,element,level,coordinate):
        #print "ELEMENT:\n"+ str(element) + "\nLEVEL:\n" +str(level) + "\nCOORDINATE\n" +str(coordinate)
        if element is not None:
            for index, item in enumerate(element):
                #print "sono nella recursiveInit" ,index,item,element
                coordinate.append(index)
                isLast = self.recursiveInit(item,level+1,coordinate)
                if isLast:
                    # coordinates of this point in the partition
                    globalCoordinates = util.addList(coordinate , self.sendCoordinates)

                    #initialize and assign the point
                    p = SectionPoint(copy.deepcopy(coordinate),globalCoordinates,self,False)
#                    if self.minPoint is None or p < self.minPoint:
#                        self.minPoint = p
#                    if self.maxPoint is None or p > self.maxPoint:
#                        self.MaxPoint = p
                    element[index] = p

                    #CHECK if it is a shift point
                    lowerBound = self.computationCoordinates
                    print lowerBound
                    upperBound = util.addList(self.computationCoordinates,self.computationDim)
                    print upperBound
                    isLower = reduce(lambda x,y:x or y,map(lambda x,y: x<y,globalCoordinates,lowerBound))
                    isUpper = reduce(lambda x,y:x or y,map(lambda x,y: x>=y,globalCoordinates,upperBound))
                    if isLower or isUpper :
                        print str(p)+"is a shift point"
                        self.shiftPoints.append(p)
                    else:
                        print str(p)+"is not a shift point"
                        
                coordinate.pop()
            return False
        else:
            return True

    def getDim(self):
        if config.RUNTIME_DIM:
            out = ""
            for i in self.sendDim:
                if i > self.father.ordine:
                    out += "("+str(i)+"+extension)*"
                else:
                    out += str(i)+"*"
            out+="1"
        else:
            out=1
            for i in self.realSendDim:
                out *= i

        return out

    def getOdim(self):
        if config.RUNTIME_DIM:
            out = ""
            for i in self.outsideDim:
                if i > self.father.ordine:
                    out += "("+str(i)+"+extension)*"
                else:
                    out += str(i)+"*"
            out+="1"
        else:
            out = 1
            for i in self.realOutsideDim:
                out *= i

        return out

    def initSize(self):
        self.sendCoordinates = []
        self.sendDim = []

        self.outsideCoordinates = []
        self.outsideDim = []
        
        self.computationCoordinates = []
        self.computationDim = []
        
        self.realSendCoordinates = []
        self.realSendDim = []

        self.realOutsideCoordinates = []
        self.realOutsideDim = []

        self.realComputationCoordinates = []
        self.realComputationDim = []
        
        self.isLocal = True
        # FIX there is no big differences among these parameters
        # they will be difference with the shift method
        # in general I need to be more general than this
        # this piece of code sucks :(
        for item in self.tag:
            if item == 0:
                self.isLocal = False

                self.sendCoordinates.append(0)
                self.sendDim.append(self.shape.ordine)

                self.outsideCoordinates.append(-self.shape.ordine)
                self.outsideDim.append(self.shape.ordine)

                self.computationCoordinates.append(0)
                self.computationDim.append(self.shape.ordine)

                if not config.RUNTIME_DIM:
                    self.realSendCoordinates.append(0)
                    self.realSendDim.append(self.shape.ordine)

                    self.realOutsideCoordinates.append(-self.shape.ordine)
                    self.realOutsideDim.append(self.shape.ordine)

                    self.realComputationCoordinates.append(0)
                    self.realComputationDim.append(self.shape.ordine)

            elif item == 1:
                self.sendCoordinates.append(0)
                self.sendDim.append(self.father.size)

                self.outsideCoordinates.append(0)
                self.outsideDim.append(self.father.size)

                self.computationCoordinates.append(0)
                self.computationDim.append(self.father.size)

                if not config.RUNTIME_DIM:
                    self.realSendCoordinates.append(0)
                    self.realSendDim.append(self.father.finalSize)

                    self.realOutsideCoordinates.append(0)
                    self.realOutsideDim.append(self.father.finalSize)

                    self.realComputationCoordinates.append(0)
                    self.realComputationDim.append(self.father.finalSize)

            elif item == 2:
                self.isLocal = False

                self.sendCoordinates.append(self.father.size - self.shape.ordine)
                self.sendDim.append(self.shape.ordine)

                self.outsideCoordinates.append(self.father.size)
                self.outsideDim.append(self.shape.ordine)

                self.computationCoordinates.append(self.father.size - self.shape.ordine)
                self.computationDim.append(self.shape.ordine)

                if not config.RUNTIME_DIM:
                    self.realSendCoordinates.append(self.father.finalSize - self.shape.ordine)
                    self.realSendDim.append(self.shape.ordine)

                    self.realOutsideCoordinates.append(self.father.finalSize)
                    self.realOutsideDim.append(self.shape.ordine)

                    self.realComputationCoordinates.append(self.father.finalSize - self.shape.ordine)
                    self.realComputationDim.append(self.shape.ordine)

        #central section is a special case
        if self.isLocal:
            for index in range( len(self.sendDim) ):

                self.sendCoordinates[index] = self.shape.ordine
                self.sendDim[index] = self.father.size - 2*self.shape.ordine

                self.computationCoordinates[index] = self.shape.ordine
                self.computationDim[index] = self.father.size - 2*self.shape.ordine

                if not config.RUNTIME_DIM:
                    self.realSendCoordinates[index] = self.shape.ordine
                    self.realSendDim[index] = self.father.finalSize - 2*self.shape.ordine

                    self.realComputationCoordinates[index]= self.shape.ordine
                    self.realComputationDim[index] = self.father.finalSize - 2*self.shape.ordine
                

    def __init__(self,tag,father):
        #coordinate nello spazio delle sezioni
        self.tag = tag

        #partition which owns this section
        self.father  = father

        # shape della computazione
        self.shape = father.shape

        # flags that indicates if the section has to be sent
        # or reveived (initially false)
        self.needsReceive = False
        self.needsSend    = False

        #computing the size of the section is quite complex
        self.sendCoordinates = []
        self.sendDim = []

        self.outsideCoordinates = []
        self.outsideDim = []

        self.computationCoordinates = []
        self.computationDim = []

        self.realSendCoordinates = []
        self.realSendDim = []

        self.realOutsideCoordinates = []
        self.realOutsideDim = []

        self.realComputationCoordinates = []
        self.realComputationDim = []        

        # this will be checked in the initSize method
        self.isLocal = True
        #FIX some section are entirely contained in other section
        #they are NOT good
        self.isGood = True

        self.initSize()

        #this has been determined in the initSize method
        if self.isGood:
            #pdb.set_trace()
            self.sendEnd = []
            self.outsideEnd = []
            print "SEZIONE ",self.tag
            for index in range(len(self.tag)):
                print "coordinata",index
                print "SOMMO ",self.sendCoordinates[index],self.sendDim[index]
                self.sendEnd.append(self.sendCoordinates[index] + self.sendDim[index]-1)
                print "SOMMO ",self.outsideCoordinates[index],self.outsideDim[index]
                self.outsideEnd.append(self.outsideCoordinates[index] + self.outsideDim[index]-1)

            print "il risultato e",self.sendEnd,self.outsideEnd
            #the offset between computation and send coordinates is stored
            # it will be used in tree expansion
            self.offset = []
            for item1,item2 in zip(self.computationCoordinates,self.sendCoordinates):
                self.offset.append(item1-item2)

            #THIS points are used by the getCandidates functions


            # internal points of the section are initialized (they may contain shift points)
            self.points = np.empty(self.sendDim,dtype=Point)
            self.shiftPoints = []
            self.recursiveInit(self.points,0,[])

        # external points of the section are initialized
        if self.isLocal:
            # FIX
            self.opoints = np.empty(1,dtype=Point)
        else:
            self.opoints = np.empty(self.outsideDim,dtype=Point)
            self.orecursiveInit(self.opoints,0,[])

            
    def getPoint(self,point):
        ''' this method return the SectionPoint belonging to self
            which is similar (same global coordinates) to point

            point   -- SectionPoint to be found in self
        '''
        if self.isInner(point):
            coordinates = map(lambda x,y:x-y,point.gcoordinates,self.sendCoordinates)
            out = self.points            
            for i in coordinates:
                out = out[i]
            assert out.isSimilar(point)
            return out

        if self.isOuter(point):
            coordinates = map(lambda x,y:x-y,point.gcoordinates,self.outsideCoordinates)
            out = self.opoints
            try:
                for i in coordinates:
                    out = out[i]
            except:
                print "This is section ",self.tag,"richiesto il punto",point,"che dovrebbe sta",str(coordinates)
            return out

        return None


    def getOppositeTag(self):
        oppositeTag = []
        for item in self.tag:
            if item is 0:
                oppositeTag.append(2)
            elif item is 2:
                oppositeTag.append(0)
            else:
                oppositeTag.append(1)
        return oppositeTag

    def getOpposite(self):
        return self.father[self.getOppositeTag()]

    def isNotShiftPoint(self,point):
        
        for item0,item1 in zip(point.gcoordinates,self.computationCoordinates):
            
            if item0 < item1 :
                if point in self.shiftPoints:
                    return False
                else:
                    print "point is",point
                    print "section is",self
                    raise ValueError('Problema: punti di shift non sono corretti'+str(point))
                
        for item0,item1 in zip(point.gcoordinates,util.addList(self.computationCoordinates,self.computationDim)):
            
            if item0 >= item1 :
                if point in self.shiftPoints:
                    return False
                else:
                    print "point is",point
                    print "section is",self
                    raise ValueError('Problema: punti di shift non sono corretti')
        return True

    def buildTree(self):
        debugFilename = "sectionCalc"+self.generaId()
        with open(debugFilename,"w") as f:
            f.write("Section"+self.generaId()+"\n")
            #a section which is not good would fail
            #alternatively I could modify the __iter__ of partition to ignore bad sections
            if self.isGood:
                time1=time.time()
                elapsedTime = 0
                self.root = Node()
                #iterate over the INTERNAL points of the section
                
                for point in filter( self.isNotShiftPoint,self.points.flat):
                    
                    f.write("\nSection "+self.generaId()+ "has point "+str(point) +"who needs points: \n")

                    offsets = []
                    #iterate over the points of the shape
                    for shift in self.shape:
                        # I compute the point needed,
                        # coordinates has no useful info
                        # gcoordinates contain the gcoord of the point needed
                        toBeFound = point + shift
                        f.write(str(toBeFound)+"\n")

                        #this is a list of SectionPoints
                        #ISSUE: this should become a method of partition (forse)
                        timeC1 = time.time()
                        possiblePoints = self.father.getCandidates(toBeFound)
                        timeC2 = time.time()

                        elapsedTime += (timeC2-timeC1)

                        #now we have to choose the winner among the list of points
                        goodBoy = reduce(chooseWinner,possiblePoints)
                        f.write("this guy has won: "+str(goodBoy)+"\n\n")

                        if goodBoy.isOuter:
                            goodBoy.father.needsReceive = True
                            goodBoy.father.getOpposite().needsSend = True

                        # compute the offset
                        offset = point.getOffset(goodBoy)

                        offsets.append(offset)
                    
                    self.root.addChild(point,offsets)

                
                f.write("\nALBERO TRIVIAL\n"+str(self.root))

                time2=time.time()
                tempo = time2-time1
                if tempo > 1:
                    print "TIME ALBERO TRIVIAL DI",self.tag,":",tempo
                    print "OF WHICH ",elapsedTime,"were spent on getCandidates"

                time1 = time.time()
                self.root.reduceTree()
                time2=time.time()
                tempo = time2-time1
                if tempo > 1:
                    print "TIME REDUCE ALBERO DI",self.tag,":",tempo

                f.write("\nALBERO RIDOTTO\n"+str(self.root))
                if config.RUNTIME_DIM:
                    self.root.expandTreeLiteral(self.shape.ordine)
                else:
                    if self.father.finalSize > self.father.size:
                        time1 = time.time()
                        f.write("\nESPANSIONE ALBERO\n")
                        self.root.expandTree(self.shape.ordine,self.father.finalSize - self.father.size)
                        f.write("\nALBERO ESPANSO\n"+str(self.root))
                        time2=time.time()
                        tempo = time2-time1
                        if tempo > 1:
                            print "TIME ESPANSIONE ALBERO DI",self.tag,":",tempo

    def buildCommTree(self):
        ''' This method should be invoked on shift sections in order to computer the dependencies
            in a similar manner to what done with the comp tree.            

        '''
        debugFilename = "sectionComm"+self.generaId()+"_"+str(self.father.id)
        self.commTree = Node()
        with open(debugFilename,"w") as f:
            if self.isGood:
                for p in self.shiftPoints:
                    externalPoint = filter(lambda x:x != p ,self.father.getCandidates(p))
                    assert len(externalPoint) == 1 , "Multiple sections for a shift point"+str(p)+"can be found in"+str(externalPoint)
                    externalPoint = externalPoint[0]

                    offset = p.getOffset(externalPoint)
                    assert offset.isOuter ,"Un punto usato nella memcpy non e esterno"
                    self.commTree.addChild(p,[offset])
                f.write("\nALBERO TRIVIAL\n"+str(self.commTree))

                self.commTree.reduceTree()

                f.write("\nALBERO RIDOTTO\n"+str(self.commTree))
                if config.RUNTIME_DIM:
                    self.commTree.expandCommTreeLiteral(self.shape.ordine,self.father.size)
                else:
                    if self.father.finalSize > self.father.size:
                            f.write("\nESPANSIONE ALBERO\n")
                            self.commTree.expandCommTree(self.shape.ordine,self.father.finalSize - self.father.size,self.father.size)
                            f.write("\nALBERO ESPANSO\n"+str(self.commTree))
            
    def generaId(self):
        out = ""
        for i in self.tag:
            out +=str(i)
        return out


    def generaFillSection(self):
        ''' This method generates the piece of code where data is copied
            from the scatter input buffer to the section buffers

        '''
        out = ""
        if self.isGood or self.isLocal:
            #if the section has a shift then the offset will be non zero
            offset = []
            for item0,item1 in zip(self.computationCoordinates,self.sendCoordinates):
                offset.append(item0-item1)
            print "la section",self.tag,"ha offset",offset

            # FIX mettere una spiegazione di cosa sta succedendo
            if config.RUNTIME_DIM:
                for index,dimension in enumerate(self.computationDim):
                    if dimension > self.father.ordine:
                        out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <" +str(self.computationDim[index]+offset[index])+"+extension;i"+str(index)+"++){\n")
                    else:
                        out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <" +str(self.computationDim[index]+offset[index])+";i"+str(index)+"++){\n")

                out += "s"+self.generaId()+"_0"
                for index in range(len(self.computationDim)):
                    out+="[i"+str(index)+"]"

                out += "= local"
                for index,dimension in enumerate(self.computationDim):
                    if dimension > self.father.ordine:
                        if self.sendCoordinates[index] >=0:
                            out+="[i"+str(index)+"+"+str(self.sendCoordinates[index])+"extension]"
                        else:
                            out +="[i"+str(index)+str(self.sendCoordinates[index])+"extension]"
                    else:
                        if self.sendCoordinates[index] >=0:
                            out+="[i"+str(index)+"+"+str(self.sendCoordinates[index])+"]"
                        else:
                            out +="[i"+str(index)+str(self.sendCoordinates[index])+"]"

                out+=";\n"
                for index in range(len(self.computationDim)):
                    out+="}\n"
            else:

                for index,dimension in enumerate(self.realComputationDim):
                    out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <" +str(self.realComputationDim[index]+offset[index])+";i"+str(index)+"++){\n")

                out += "s"+self.generaId()+"_0"
                for index in range(len(self.realComputationDim)):
                    out+="[i"+str(index)+"]"

                out += "= local"
                for index in range(len(self.realComputationDim)):
                    if self.realSendCoordinates[index] >=0:
                        out+="[i"+str(index)+"+"+str(self.realSendCoordinates[index])+"]"
                    else:
                        out +="[i"+str(index)+str(self.realSendCoordinates[index])+"]"

                out+=";\n"
                for index in range(len(self.realComputationDim)):
                    out+="}\n"
        return out

    def generaCondensa(self):
        out = ""
        if self.isGood or self.isLocal:
            #if the section has a shift then the offset will be non zero
            offset = []
            for item0,item1 in zip(self.realComputationCoordinates,self.realSendCoordinates):
                offset.append(item0-item1)

            for index,dimension in enumerate(self.realComputationDim):
                out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <" +str(self.realComputationDim[index])+";i"+str(index)+"++){\n")

            out += "local"
            for index in range(len(self.realComputationDim)):
                if self.realSendCoordinates[index] >=0:
                    out+="[i"+str(index)+"+"+str(self.realSendCoordinates[index])+"]"
                else:
                    out +="[i"+str(index)+str(self.realSendCoordinates[index])+"]"

            
            out += "=s"+self.generaId()+"_0"
            for index in range(len(self.realComputationDim)):
                out+="[i"+str(index)+"]"

            out+=";\n"
            for index in range(len(self.realComputationDim)):
                out+="}\n"
        return out

    def generaBrackets(self):
        #FIX nome non dignificativo
        ''' questa funzione ritorna una stringa contenente le
            dimensioni (del buffer di send) della sezione
        '''
        out = ""
        for i in self.realSendDim:
            out += ("["+str(i)+"]")
        return out

    def generaInitC(self):
        
        out = ""
        if self.isGood:
            partition = self.father
            id = self.generaId()

            # genero le s
            #FIX non e detto che sono solo due...se ho step model con oversending
            for j in range(2):
                out += ("\t"+config.DATATYPE+ " (* s"+id+"_"+str(j)+")")
                for index,item in enumerate(self.realSendDim):
                    if index > 0:
                        out += ("["+str(item)+"]")
                out += " = malloc(sizeof("+     config.DATATYPE +")"
                for item in self.realSendDim:
                    out += ("*"+str(item))
                out += ")"
                # THIS IS THE METHOD FOR STACK ALLOCATION
                #out += ("\t"+config.DATATYPE+ " s"+id+"_"+str(j)+self.generaBrackets())
                #for i in range(partition.dim):
                #    out += ("["+str(self.realDim[i])+"]")
                out+=";\n"

            #genero la o
            out += ("\t"+config.DATATYPE+ " (* o"+id+")")
            for index,item in enumerate(self.realSendDim):
                if index > 0:
                    out += ("["+str(item)+"]")
            out += " = malloc(sizeof("+     config.DATATYPE +")"
            for item in self.realOutsideDim:
                out += ("*"+str(item))
            out += ");\n"

            #genero quella riga strana
            out += ("\tsezioni["+str(tagToIndex(self.tag))+"].buffer = ("+config.DATATYPE+"*) s"+id+"_0;\n")

        return out

    def generaSend(self,index):
        print "GeneraSend ",index
        out = ""
        if self.needsSend:
            for c in self.commTree.childs:
                out += c.generaMemCpy(self.generaId(), index)
            #FIX ASSERT che sia una sezione buona
            out += ("SEND(s"+self.generaId()+"_"+str(index)+","+str(self.getDim()))
            out += (",MPI_"+config.DATATYPE.upper()+",sezioni["+str(tagToIndex(self.tag))+"].rank,")
            out += (str(tagToIndex(self.getOppositeTag()))+",MPI_COMM_WORLD")
            out += ");\n"
        return out

    def generaReceive(self):
        out = ""
        if self.needsReceive:
            out += ("RECEIVE(o"+self.generaId()+","+str(self.getDim()))
            out += (",MPI_"+config.DATATYPE.upper()+",sezioni["+str(tagToIndex(self.tag))+"].rank,")
            out += (str(tagToIndex(self.tag))+",MPI_COMM_WORLD,&status")
            out += ");\n"
        return out

    def generaCalcoloC(self,sourceId,targetId,start = None,end = None):
        ''' This method generates the for loops in C relative to section self

            self        - section which invoke code generation
            sourceId    - string containing the subscript of the sections which are read targets
            targetId    - string containing the subscript of the sections which are write targets
            start,end   - interval for the outermost loop

            output  - string containing generated code
        '''
        out = ""
        print "Section ",self.tag,"start: ",start,"end",end
        if self.isGood:
            
            for node in self.root.childs:
                if config.OPEN_MP:
                    codice = ""
                    size = node.checkInterval(start, end)
                    if size > 0:
                        codice = node.generaNodeC(self.generaId(),sourceId,targetId,start,end)                        
                    
                    if self.isLocal:
                        if size > self.shape.ordine:
                            aggiunta = "#pragma omp parallel for private("
                            for i in range(len(self.tag)):
                                if i>1:
                                    aggiunta += ","
                                if i >0:
                                    aggiunta += ( "i"+str(i) )
                            aggiunta += ")\n"
                            codice=aggiunta+codice
                    else:
                        codice='#pragma omp section\n{\n'+codice+'\n}\n'
                    if size >0:
                        out +=codice            
                else:
                    out += node.generaNodeC(self.generaId(),sourceId,targetId,start,end)

        return out

    def generaCalcoloRuntimeDim(self,sourceId,targetId,step):
        ''' This method generates the for loops in C relative to section self

            self        - section which invoke code generation
            sourceId    - string containing the subscript of the sections which are read targets
            targetId    - string containing the subscript of the sections which are write targets
            step        - step to be generated
            
            output  - string containing generated code
        '''
        out = ""

        if self.isGood:

            for node in self.root.childs:
                if config.OPEN_MP:
                    raise NotImplementedError("Runtime Dim does not work yet")
                else:
                    out += node.generaNodeC(self.generaId(),sourceId,targetId)

        return out

    def generaClose(self):
        out = ""
        if self.isGood:
            staticOffset = []
            for i in range(self.father.dim):
                staticOffset.append(1)


            id = self.generaId()
            start = util.addList(staticOffset, self.realCoordinates)
            end = util.addList(start, self.realDim)
            #print start,end
            out += ("b(")
            count = 0
            merged = zip(start,end)
            for i in merged:
                #print i
                count +=1
                out += (str(i[0])+":"+str(i[1]-1))
                if count < len(merged):
                    out += (",")

            out += (") = s" +str(id)+"_1 ;\n")
            
        return out

    def isOuter(self,item):
        if self.isLocal:
            return False
        for index in range(len(self.tag)):
            if item[index] > self.outsideEnd[index] or item[index] < self.outsideCoordinates[index]:
                return False
        return True

    def isInner(self,item):
        for index in range(len(self.tag)):
            if item[index] > self.sendEnd[index] or item[index] < self.sendCoordinates[index]:
                return False
        return True

    def __contains__(self,item):
        ''' Implements the in operator for a section '''
#        if item in self.points or item in self.opoints:
#            return True
#        else:
#            return False
        if self.isOuter(item) or self.isInner(item):
            return True
        return False


    def generaDebugPrint(self,subscript):
        out = ""
        if self.isGood:
            out+= "#if DEBUG\n"
            if config.OPEN_MP and not self.isLocal:
                out += '#pragma omp master\n{\n'
            
            out +='fprintf(localfp,"\\nSEZIONE '+str(self.tag)+'\\n")'+";\n"
            #for cycle
            for index,item in enumerate(self.realSendDim):
                out+="for (i"+str(index)+"=0;i"+str(index)+"<"+str(item)+";i"+str(index)+"++){\n"
            
            out+= 'fprintf(localfp,FORMAT,s'+self.generaId()+"_"+subscript
            #indexes
            for index in range(len(self.sendDim)):
                out+="[i" +str(index)+"]"
            out+=");\n"
            #newlines and closure
            for i in range(len(self.sendDim)):
                if i > 0:
                    out +='fprintf(localfp,"'
                    for j in range(i):
                        out+="\\n"
                    out+='");\n'
                out+="}\n"
            
            if config.OPEN_MP and not self.isLocal:
                out += '\n}\n'
            out+="#endif\n"
        return out

    def __str__(self):
        if self.isGood:
            return " sono la Section: " +str(self.tag) + \
            "\n ostart" + str(self.outsideCoordinates) +" odim"+str(self.outsideDim)+" oend "+str(self.outsideEnd)+"p"+str(self.opoints) + \
            "\n sendBuffer" + str(self.sendCoordinates) +"dim"+str(self.sendDim) +"Computation Buffer "+str(self.computationCoordinates) +" dim"+str(self.computationDim)+"p"+str(self.points) +\
            "\n SHIFT POINTS: "+str(self.shiftPoints)+"\n"
        else:
            return " sono la Section: " +str(self.tag) +" e sono CATTIVA\n"

    def __repr__(self):
        return self.__str__()

class SectionShift(Section):

    def initSize(self):
        ''' this is more complex than the default initSize,
            some sctions are not "good"
            dimensions of send and computation buffer also differ
            NOTICE: if the section is not local it implies that a coordinate different than zero has been found
            during the previous execution of the loop
        '''
        self.isGood = True

        for item in self.tag:
            if item == 0:
                if self.isLocal:
                    self.isLocal = False

                    self.sendCoordinates.append(0)
                    self.sendDim.append(self.shape.ordine)

                    self.outsideCoordinates.append(-self.shape.ordine)
                    self.outsideDim.append(self.shape.ordine)

                    self.computationCoordinates.append(0)
                    self.computationDim.append(self.shape.ordine)

                    if not config.RUNTIME_DIM:
                        self.realSendCoordinates.append(0)
                        self.realSendDim.append(self.shape.ordine)

                        self.realOutsideCoordinates.append(-self.shape.ordine)
                        self.realOutsideDim.append(self.shape.ordine)

                        self.realComputationCoordinates.append(0)
                        self.realComputationDim.append(self.shape.ordine)
                else:
                    # a second coordinate different than 1 (central coordinate) has been found
                    # therefore the section does not have to be generated
                    self.isGood = False

            elif item == 1:
                if self.isLocal:
                    self.sendCoordinates.append(0)
                    self.sendDim.append(self.father.size)

                    self.outsideCoordinates.append(0)
                    self.outsideDim.append(self.father.size)

                    self.computationCoordinates.append(0)
                    self.computationDim.append(self.father.size)

                    if not config.RUNTIME_DIM:
                        self.realSendCoordinates.append(0)
                        self.realSendDim.append(self.father.finalSize)

                        self.realOutsideCoordinates.append(0)
                        self.realOutsideDim.append(self.father.finalSize)

                        self.realComputationCoordinates.append(0)
                        self.realComputationDim.append(self.father.finalSize)
                else:                    
                    # a coordinate different than one has been found BUT the section is ok if all the OTHER coordinates are 1
                    # MOREOVER we nees to expand because of the shift method
                    self.sendCoordinates.append(-self.shape.ordine)
                    self.sendDim.append(self.father.size +2*self.shape.ordine)

                    self.outsideCoordinates.append(-self.shape.ordine)
                    self.outsideDim.append(self.father.size+2*self.shape.ordine)

                    self.computationCoordinates.append(0)
                    self.computationDim.append(self.father.size)

                    if not config.RUNTIME_DIM:
                        self.realSendCoordinates.append(-self.shape.ordine)
                        self.realSendDim.append(self.father.finalSize +2 *self.shape.ordine)

                        self.realOutsideCoordinates.append(-self.shape.ordine)
                        self.realOutsideDim.append(self.father.finalSize+2 *self.shape.ordine)

                        self.realComputationCoordinates.append(0)
                        self.realComputationDim.append(self.father.finalSize)

            elif item == 2:
                if self.isLocal:
                    self.isLocal = False

                    self.sendCoordinates.append(self.father.size - self.shape.ordine)
                    self.sendDim.append(self.shape.ordine)

                    self.outsideCoordinates.append(self.father.size)
                    self.outsideDim.append(self.shape.ordine)

                    self.computationCoordinates.append(self.father.size - self.shape.ordine)
                    self.computationDim.append(self.shape.ordine)

                    if not config.RUNTIME_DIM:
                        self.realSendCoordinates.append(self.father.finalSize - self.shape.ordine)
                        self.realSendDim.append(self.shape.ordine)

                        self.realOutsideCoordinates.append(self.father.finalSize)
                        self.realOutsideDim.append(self.shape.ordine)

                        self.realComputationCoordinates.append(self.father.finalSize - self.shape.ordine)
                        self.realComputationDim.append(self.shape.ordine)
                else:
                    self.isGood = False

        #central section is a special case
        if self.isLocal:
            for index in range( len(self.sendDim) ):

                self.sendCoordinates[index] = self.shape.ordine
                self.sendDim[index] = self.father.size - 2*self.shape.ordine

                self.computationCoordinates[index] = self.shape.ordine
                self.computationDim[index] = self.father.size - 2*self.shape.ordine

                if not config.RUNTIME_DIM:

                    self.realSendCoordinates[index] = self.shape.ordine
                    self.realSendDim[index] = self.father.finalSize - 2*self.shape.ordine

                    self.realComputationCoordinates[index]= self.shape.ordine
                    self.realComputationDim[index] = self.father.finalSize - 2*self.shape.ordine
