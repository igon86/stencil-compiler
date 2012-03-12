
__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.53$"

import numpy as np
import util

from point import *
from TreeNode import *


def chooseWinner(x,y):
    ''' This function is a reduce function which just return the coolest point
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
    ''' map a n-dimensional tag of a section into an index in a one dimensional domain

    '''
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
                    element[index] = SectionPoint(copy.deepcopy(coordinate), util.addList(coordinate , self.outsideCoordinates),self,True)
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
        out = 1
        for i in self.realSendDim:
            out *= i

        return out

    def getOdim(self):
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
        #the offset between computation and send coordinates is stored
        # it will be used in tree expansion
        self.offset = []
        for item1,item2 in zip(self.computationCoordinates,self.sendCoordinates):
            self.offset.append(item1-item2)

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
                        possiblePoints = self.father.getCandidates(toBeFound)

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
        
                self.root.reduceTree()
                
                f.write("\nALBERO RIDOTTO\n"+str(self.root))
                if self.father.finalSize > self.father.size:
                    f.write("\nESPANSIONE ALBERO\n")
                    self.root.expandTree(self.shape.ordine,self.father.finalSize - self.father.size)
                    f.write("\nALBERO ESPANSO\n"+str(self.root))

    def buildCommTree(self):
        ''' This method should be invoked on shift sections in order to computer the dependencies
            in a similar manner to what done with the comp tree.
            MUST be invoked after the buildtree?

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
                if self.father.finalSize > self.father.size:
                        f.write("\nESPANSIONE ALBERO\n")
                        self.commTree.expandCommTree(self.shape.ordine,self.father.finalSize - self.father.size,self.father.size)
                        f.write("\nALBERO ESPANSO\n"+str(self.commTree))
            
    def generaId(self):
        out = ""
        for i in self.tag:
            out +=str(i)
        return out

    def generaInit(self):
        out = ""
        if self.isGood:
            partition = self.father


            # indexes start from 1
            staticOffset = []
            for i in range(partition.dim):
                staticOffset.append(partition.ordine+1)

            id = self.generaId()

            #internal section
            start = util.addList(staticOffset, self.realCoordinates)
            end = util.addList(start, self.realDim)
            print start,end

            out += "s"+str(id)+"=a("
            count = 0
            merged = zip(start,end)
            for i in merged:
                print i
                count +=1
                out += (str(i[0])+":"+str(i[1]-1))
                if count < len(merged):
                    out +=","
            out +=");\n"

            #external section
            ostart = util.addList(staticOffset, self.orealCoordinates)
            oend = util.addList(ostart, self.orealDim)
            print ostart,oend

            out += ("o"+str(id)+"=a(")
            count = 0
            merged = zip(ostart,oend)
            for i in merged:
                print i
                count +=1
                out +=(str(i[0])+":"+str(i[1]-1))
                if count < len(merged):
                    out +=(",")
            out +=");\n"

        return out

    def generaFillSection(self):
        out = ""
        if self.isGood or self.isLocal:
            #if the section has a shift then the offset will be non zero
            offset = []
            for item0,item1 in zip(self.realComputationCoordinates,self.realSendCoordinates):
                offset.append(item0-item1)

            print "la section",self.tag,"ha offset",offset
            
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
            #FIX non e detto che sono solo due
            for j in range(2):
                out += ("\tint s"+id+"_"+str(j)+self.generaBrackets())
                #for i in range(partition.dim):
                #    out += ("["+str(self.realDim[i])+"]")
                out+=";\n"

            #genero la o
            out += ("\tint o"+id)
            for i in range(partition.dim):
                out += ("["+str(self.realSendDim[i])+"]")
            out+=";\n"

            #genero quella riga strana
            out += ("\tsezioni["+str(tagToIndex(self.tag))+"].buffer = (int*) s"+id+"_0;\n")

        return out

    def generaSend(self,index):
        print "GeneraSend ",index
        out = ""
        if self.needsSend:
            for c in self.commTree.childs:
                out += c.generaMemCpy(self.generaId(), index)
            #FIX ASSERT che sia una sezione buona
            out += ("SEND(s"+self.generaId()+"_"+str(index)+","+str(self.getDim()))
            out += (",MPI_INT,sezioni["+str(tagToIndex(self.tag))+"].rank,")
            out += (str(tagToIndex(self.getOppositeTag()))+",MPI_COMM_WORLD")
            out += ");\n"
        return out

    def generaReceive(self):
        out = ""
        if self.needsReceive:
            out += ("RECEIVE(o"+self.generaId()+","+str(self.getDim()))
            out += (",MPI_INT,sezioni["+str(tagToIndex(self.tag))+"].rank,")
            out += (str(tagToIndex(self.tag))+",MPI_COMM_WORLD,&status")
            out += ");\n"
        return out

    def generaCalcolo(self):
        ''' This method generates the for loops in MATLAB relative to section self

            self    - section which invoke code generation

            output  - string containing generated code
        '''
        out = ""
        for c in self.root.childs:
            # the string of the section id is the only information
            # not contained in the tree (the tree does not have back pointers)
            out += c.generaNode(self.generaId())
        return out

    def generaCalcoloC(self,sourceId,targetId,start=None,end=None):
        ''' This method generates the for loops in C relative to section self

            self        - section which invoke code generation
            sourceId    - string containing the postfix of the section which are read targets
            targetId    - string containing the postfix of the section which are write targets

            output  - string containing generated code
        '''
        out = ""
        if self.isGood:
            for c in self.root.childs:
                # the string of the section id is the only information
                # not contained in the tree (the tree does not have back pointers)
                out += c.generaNodeC(self.generaId(),sourceId,targetId,start,end)
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


    def __contains__(self,item):
        if item in self.points or item in self.opoints:
            return True
        else:
            return False

    def generaDebugPrint(self,subscript):
        out = ""
        if self.isGood:
            out+= "#if DEBUG\n"
            out +='fprintf(localfp,"\\nSEZIONE '+str(self.tag)+'\\n")'+";\n"
            #for cycle
            for index,item in enumerate(self.realSendDim):
                out+="for (i"+str(index)+"=0;i"+str(index)+"<"+str(item)+";i"+str(index)+"++){\n"
            #fprintf
            out+= 'fprintf(localfp,"%d\\t",s'+self.generaId()+"_"+subscript
            #indexes
            for index in range(len(self.sendDim)):
                out+="[i" +str(index)+"]"
            out+=");\n"
            #newlines and closure
            for i in range(len(self.sendDim)):
                out +='fprintf(localfp,"'
                for j in range(i):
                    out+="\\n"
                out+='");\n'
                out+="}\n"
            out+="#endif\n"
        return out

    def __str__(self):
        if self.isGood:
            return " sono la Section: " +str(self.tag) + \
            "\n ostart" + str(self.realOutsideCoordinates) +" odim"+str(self.outsideDim)+"p"+str(self.opoints) + \
            "\n sendBuffer" + str(self.realSendCoordinates) +"dim"+str(self.sendDim) +"Computation Buffer "+str(self.realComputationCoordinates) +" dim"+str(self.computationDim)+"p"+str(self.points) +\
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

                self.realSendCoordinates[index] = self.shape.ordine
                self.realSendDim[index] = self.father.finalSize - 2*self.shape.ordine

                self.realComputationCoordinates[index]= self.shape.ordine
                self.realComputationDim[index] = self.father.finalSize - 2*self.shape.ordine



if __name__ == "__main__":
    print "Hello World"
