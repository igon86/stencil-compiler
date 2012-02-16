
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



        #da queste devo ricavare le coordinate iniziali della sezione nella partizione
        # questo va modificato per fare il metodo di shift
        self.startingCoordinates = []
        self.dim = []
        self.oCoordinates = []
        self.odim = []
        self.realDim = []
        self.orealDim = []
        self.isLocal = True
        #NOTICE there is no big differences among these parameters
        # they will be difference with the shift method
        # in general I need to be more general than this
        # this piece of code sucks :(
        for item in tag:
            if item == 0:
                self.isLocal = False
                
                self.startingCoordinates.append(0)
                self.oCoordinates.append(- self.shape.ordine)

                self.dim.append(self.shape.ordine)
                self.odim.append(self.shape.ordine)
                self.realDim.append(self.shape.ordine)
                self.orealDim.append(self.shape.ordine)

            elif item == 1:
                self.startingCoordinates.append(0)
                self.oCoordinates.append(0)

                self.dim.append(self.father.size)
                self.odim.append(self.father.size)
                self.realDim.append(self.father.finalSize)
                self.orealDim.append(self.father.finalSize)
                
            elif item == 2:
                self.isLocal = False
                
                self.startingCoordinates.append(self.father.size - self.shape.ordine)
                self.oCoordinates.append(self.father.size)

                self.dim.append(self.shape.ordine)
                self.odim.append(self.shape.ordine)
                self.realDim.append(self.shape.ordine)
                self.orealDim.append(self.shape.ordine)

        #caso speciale della sezione centrale
        if self.isLocal:
            for index in range( len(self.dim) ):
                self.dim[index] = self.father.size - 2*self.shape.ordine
                self.startingCoordinates[index] = self.shape.ordine

        #ora mi creo l'array di punti della sezione
        self.points = np.empty(self.dim,dtype=Point)

        #inizializzo i punti
        self.recursiveInit(self.points,0,[])

    #ora mi creo l'array di punti esterni della sezione
        if self.isLocal:
            self.opoints = np.empty(1,dtype=Point)
        else:
            self.opoints = np.empty(self.odim,dtype=Point)
            self.orecursiveInit(self.opoints,0,[])
    

    def buildTree(self,finalDimension):
        self.root = Node()
        #iterate over the inner points of the section
        for point in self.points.flat:
            #print point
            #iterate over the points of the shape
            offsets = []
            #print "\nSection ", self.tag, "has point ", point, "who needs points: "
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
            self.root.expandTree(self.shape.ordine,finalDimension - self.father.size)

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
