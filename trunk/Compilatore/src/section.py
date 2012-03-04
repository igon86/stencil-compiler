
__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.53$"

import numpy as np
import util

from point import *
from TreeNode import *

import gc

#def tagToCoordinates()

def chooseWinner(x,y):
    if (x.coolness() == y.coolness()):
        #this should  be changed
        return x
    elif (x.coolness() < y.coolness()):
        return y
    else:
        return x

def tagToIndex(tag):
    # from the less significant to the most significant
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
                    #print "sto per modificare", str(element[index])
                    element[index] = SectionPoint(copy.deepcopy(coordinate),util.addList(coordinate , self.sendCoordinates),self,False)
                    #print "stampo cosa ho fatto: " +str(index)+" " + str(coordinate)
                    #print self
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

                self.realSendCoordinates[index]
                self.realSendDim[index] = self.father.finalSize - 2*self.shape.ordine

                self.realComputationCoordinates[index]
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

        self.isLocal = True
        #FIX some section are entirely contained in other section
        #they are not good
        self.isGood = True
        # FIX there is no big differences among these parameters
        # they will be difference with the shift method
        # in general I need to be more general than this
        # this piece of code sucks :(
        self.initSize()

        # internal points of the section are initialized
        self.points = np.empty(self.computationDim,dtype=Point)
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
        print point
        for item0,item1 in zip(point.gcoordinates,self.computationCoordinates):
            print item0,item1
            if item0 < item1 :
                print "RITORNO FALSE"
                return False

        for item0,item1 in zip(point.gcoordinates,util.addList(self.computationCoordinates,self.computationDim)):
            print item0,item1
            if item0 > item1 :
                print "RITORNO FALSE"
                return False
         
        return True

    def buildTree(self):
        #a section which is not good would fail
        #alternatively I could modify the __iter__ of partition to ignore bad sections
        if self.isGood:
            self.root = Node()
            #iterate over the INTERNAL points of the section
            for point in filter( self.isNotShiftPoint,self.points.flat):
                #print point
                #print "\nSection ", self.tag, "has point ", point, "who needs points: "

                offsets = []
                #iterate over the points of the shape
                for shift in self.shape:
                    # I compute the point needed,
                    # coordinates has no useful info
                    # gcoordinates contain the gcoord of the point needed
                    toBeFound = point + shift
                    print toBeFound

                    #this is a list of SectionPoints
                    #ISSUE: this should become a method of partition (forse)
                    possiblePoints = self.father.getCandidates(toBeFound)

                    #now we have to choose the winner among the list of points
                    goodBoy = reduce(chooseWinner,possiblePoints)

                    if goodBoy.isOuter:
                        goodBoy.father.needsReceive = True
                        goodBoy.father.getOpposite().needsSend = True

                    # compute the offset
                    offset = point.getOffset(goodBoy)

                    offsets.append(offset)

                self.root.addChild(point,offsets)

            print "\nALBERO TRIVIAL\n",self.root
            #FIX: THIS IS INCREDIBLY UGLY
    #        ridotto = reduce(util.collapseTree, self.root.childs)
    #        if hasattr(ridotto,'__iter__'):
    #            self.root.childs = ridotto
    #        else:
    #            self.root.childs = [ridotto]
            self.root.reduceTree()

            print "\nALBERO RIDOTTO\n",self.root
            if self.father.finalSize > self.father.size:
                print "\n\nESPANSIONE ALBERO\n\n"
                self.root.expandTree(self.shape.ordine,self.father.finalSize - self.father.size)
                print "\nALBERO ESPANSO\n",self.root

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
            
            for index,dimension in enumerate(self.realComputationDim):
                out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <=" +str(self.realComputationDim[index])+";i"+str(index)+"++){\n")
                
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
                out += ("for (i"+str(index)+" = "+str(offset[index])+" ; i"+str(index)+" <=" +str(self.realComputationDim[index])+";i"+str(index)+"++){\n")

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

    def generaCalcoloC(self,sourceId,targetId):
        ''' This method generates the for loops in C relative to section self

            self        - section which invoke code generation
            sourceId    - string containing the postfix

            output  - string containing generated code
        '''
        out = ""
        if self.isGood:
            for c in self.root.childs:
                # the string of the section id is the only information
                # not contained in the tree (the tree does not have back pointers)
                out += c.generaNodeC(self.generaId(),sourceId,targetId)
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
            print start,end
            out += ("b(")
            count = 0
            merged = zip(start,end)
            for i in merged:
                print i
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

    def __str__(self):
        if self.isGood:
            return " sono la Section: " +str(self.tag) + \
            "\n ostart" + str(self.outsideCoordinates) +" odim"+str(self.outsideDim)+"p"+str(self.opoints) + \
            "\n start" + str(self.sendCoordinates) +" dim"+str(self.sendDim)+"p"+str(self.points)
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
            #nothing changes with respect of the naive case
            for index in range( len(self.sendDim) ):

                self.sendCoordinates[index] = self.shape.ordine
                self.sendDim[index] = self.father.size - 2*self.shape.ordine

                self.computationCoordinates[index] = self.shape.ordine
                self.computationDim[index] = self.father.size - 2*self.shape.ordine

                self.realSendCoordinates[index]
                self.realSendDim[index] = self.father.finalSize - 2*self.shape.ordine

                self.realComputationCoordinates[index]
                self.realComputationDim[index] = self.father.finalSize - 2*self.shape.ordine



if __name__ == "__main__":
    print "Hello World"
