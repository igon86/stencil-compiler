
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
                    element[index] = SectionPoint(copy.deepcopy(coordinate), util.addList(coordinate , self.oCoordinates),self,True)
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
                    element[index] = SectionPoint(copy.deepcopy(coordinate),util.addList(coordinate , self.startingCoordinates),self,False)
                    #print "stampo cosa ho fatto: " +str(index)+" " + str(coordinate)
                    #print self
                coordinate.pop()
            return False
        else:
            return True

    def __init__(self,tag,father):
        #coordinate nello spazio delle sezioni
        self.tag = tag

        #partition which owns this section
        self.father  = father

        # shape della computazione
        self.shape = father.shape

        self.startingCoordinates = []
        self.dim = []
        self.oCoordinates = []
        self.realCoordinates = []
        self.orealCoordinates = []
        self.odim = []
        self.realDim = []
        self.orealDim = []
        self.isLocal = True
        # FIX there is no big differences among these parameters
        # they will be difference with the shift method
        # in general I need to be more general than this
        # this piece of code sucks :(
        for item in tag:
            if item == 0:
                self.isLocal = False
                
                self.startingCoordinates.append(0)
                self.oCoordinates.append(- self.shape.ordine)
                self.realCoordinates.append(0)
                self.orealCoordinates.append(- self.shape.ordine)

                self.dim.append(self.shape.ordine)
                self.odim.append(self.shape.ordine)
                self.realDim.append(self.shape.ordine)
                self.orealDim.append(self.shape.ordine)

            elif item == 1:
                self.startingCoordinates.append(0)
                self.oCoordinates.append(0)
                self.realCoordinates.append(0)
                self.orealCoordinates.append(0)

                self.dim.append(self.father.size)
                self.odim.append(self.father.size)
                self.realDim.append(self.father.finalSize)
                self.orealDim.append(self.father.finalSize)
                
            elif item == 2:
                self.isLocal = False
                
                self.startingCoordinates.append(self.father.size - self.shape.ordine)
                self.oCoordinates.append(self.father.size)
                self.realCoordinates.append(self.father.finalSize - self.shape.ordine)
                self.orealCoordinates.append(self.father.finalSize)

                self.dim.append(self.shape.ordine)
                self.odim.append(self.shape.ordine)
                self.realDim.append(self.shape.ordine)
                self.orealDim.append(self.shape.ordine)

        #central section is a special case
        if self.isLocal:
            for index in range( len(self.dim) ):
                self.startingCoordinates[index] = self.shape.ordine
                self.realCoordinates[index] = self.shape.ordine

                self.dim[index] = self.father.size - 2*self.shape.ordine
                self.realDim[index] = self.father.finalSize - 2*self.shape.ordine
                
                

        # internal points of the section are initialized
        self.points = np.empty(self.dim,dtype=Point)
        self.recursiveInit(self.points,0,[])

        # external points of the section are initialized
        if self.isLocal:
            # FIX
            self.opoints = np.empty(1,dtype=Point)
        else:
            self.opoints = np.empty(self.odim,dtype=Point)
            self.orecursiveInit(self.opoints,0,[])
    

    def buildTree(self):
        self.root = Node()
        #iterate over the INTERNAL points of the section
        for point in self.points.flat:
            #print point
            #print "\nSection ", self.tag, "has point ", point, "who needs points: "
            
            offsets = []
            #iterate over the points of the shape
            for shift in self.shape:
                # I compute the point needed,
                # coordinates has no useful info
                # gcoordinates contain the gcoord of the point needed
                toBeFound = point + shift
                #this is a list of SectionPoints - this should become a method of partition
                possiblePoints = self.father.getCandidates(toBeFound)
                #print toBeFound, "which can be found here: "
                #for p in possiblePoints:
                #    print p
                #now we have to choose the winner among the list of points
                goodBoy = reduce(chooseWinner,possiblePoints)
                #print "ha vinto", goodBoy

                # compute the offset which has only coordinates meaningful
                offset = point.getOffset(goodBoy)
                # reference of the section is wrong so I FIX IT
                #offset.father = point.father
                #print "con offset", offset
                #OCCHIO
                offsets.append(offset)
            #print "ADDO IL NODO"
            #FALSO
            self.root.addChild(point,offsets)

        print self.root
        self.root.childs = reduce(util.collapseTree, self.root.childs)
        print self.root
        if self.father.finalSize > self.father.size:
            self.root.expandTree(self.shape.ordine,self.father.finalSize - self.father.size)

    def generaId(self):
        out = ""
        for i in self.tag:
            out +=str(i)
        return out

    def generaInit(self):

        partition = self.father
        out = ""
        
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

    def generaInitC(self):
        partition = self.father
        out = ""
        # in matlab I do not have negative index
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

    def generaCalcolo(self):
        out = ""
        for c in self.root.childs:
            # the string of the section id is the only information
            # not contained in the tree (the tree does not have back pointers)
            out += c.generaNode(self.generaId())
        return out

    def generaClose(self):
        out = ""

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
        print out
        return out


    def __contains__(self,item):
        if item in self.points or item in self.opoints:
            return True
        else:
            return False

    def __str__(self):
        return " sono la Section: " +str(self.tag) + \
    "\n ostart" + str(self.oCoordinates) +" odim"+str(self.odim)+"p"+str(self.opoints) + \
    "\n start" + str(self.startingCoordinates) +" dim"+str(self.dim)+"p"+str(self.points)

    def __repr__(self):
        return self.__str__()

if __name__ == "__main__":
    print "Hello World"
