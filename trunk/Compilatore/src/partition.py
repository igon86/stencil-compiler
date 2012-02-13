# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.07$"

import numpy as np

from section import *

class Partition(object):

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
                    #print self
                    element[index] = Section(copy.deepcopy(coordinate),self.size,self)
                    #print "stampo cosa ho fatto: " +str(index)+" " + str(coordinate)
                    #print self
                coordinate.pop()
            return False
        else:
            return True

    def __init__(self,shape):

        self.shape = shape

        self.ordine = shape.ordine

        self.dim = shape.dim

        #computes size
        self.size = 5*self.ordine + 1

        #creates array of sections
        dimensioni=[]
        for i in range(self.dim):
            dimensioni.append(3)
        #print dimensioni
        #the dim-dimensional matrix of sections is created empty
        self.sezioni = np.empty(dimensioni,dtype=Section)

        #every section in the matrix is initialized
        self.recursiveInit(self.sezioni,0,[])


    #def __getitem__(self,index):
     #   return self.sezioni[index]

    def __str__(self):
        return "sono una partizione\n" +str(self.sezioni)

    def getCandidates(self, p):
        """ Retrieve all SectionPoints which are contained in partition

            self -- partition which presumably contain multiple instances of point p
            p    -- point that has to be searched

            out  -- a list of SectionPoints which has same global coordinates as point p

        """

        out = []
        #qui potrei fare un iteratore
        for section in self.sezioni.flat:
            for point in section.points.flat:
                if p.isSimilar(point):
                    out.append(point)
            for point in section.opoints.flat:
                if p.isSimilar(point):
                    out.append(point)
        return out

if __name__ == "__main__":
    print "No debug for partition"
