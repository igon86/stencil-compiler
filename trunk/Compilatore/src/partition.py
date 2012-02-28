import util
import generatore
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
                    element[index] = Section(copy.deepcopy(coordinate),self)
                    #print "stampo cosa ho fatto: " +str(index)+" " + str(coordinate)
                    #print self
                coordinate.pop()
            return False
        else:
            return True

    def __init__(self,shape,finalSize):

        # if finalSize is less than size then an error is raised,
        # in order to debug the tree mechanism WITHOUT ESPANSION
        # finalSize should have the same value of self.size

        self.shape = shape
        print "sono una partizione e mi e arrivato: ",self.shape
        self.ordine = shape.ordine

        # NOTA: il numero di dimensioni: cioe bidimensionale. tridimensionale etc
        # viene ricavato dal file di shape
        self.dim = shape.dim


        #computes size
        self.size = 5*self.ordine + 1

        if finalSize < self.size:
            raise ValueError("Final Dimension smaller than partition self.father.size")
        elif finalSize == self.size:
            print "TREE WILL NOT BE EXPANDED"
        self.finalSize = finalSize

        #creates array of sections
        dimensioni=[]
        for i in range(self.dim):
            dimensioni.append(3)
        #print dimensioni
        #the dim-dimensional matrix of sections is created empty
        self.sezioni = np.empty(dimensioni,dtype=Section)

        #every section in the matrix is initialized
        self.recursiveInit(self.sezioni,0,[])


    def __len__(self):
        return len(self.sezioni.flat)


    def __getitem__(self,index):
        if type(index).__name__=='int':
            return self.sezioni.flat[index]
        elif type(index).__name__=='list':
            if len(index) is self.dim:
                out = self.sezioni

                #array of section is walked recursively
                for item in index:
                    out = out[item]
                    
                return out
            else:
                raise ValueError("Length of index and number of dimension of the partition differ")
        else:
            raise TypeError("Index is neither int nor list of int: cannot perform __getItem__ operation")

    def __str__(self):
        return "sono una partizione\n" +str(self.sezioni)

    def getLocalSectionTag(self):        
        localSectionTag = []
        for i in range(self.dim):
            localSectionTag.append(1)
        return localSectionTag

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

    def generaInit(self):
        out = ""
        for s in self.sezioni.flat:
            out += s.generaInit()
        return out

    def generaInitC(self):
        out = ""
        for i in range(self.dim):
            out += ("\tint i"+str(i)+";\n")
        out +="\n"
        
        for s in self.sezioni.flat:
            out += s.generaInitC()
        return out

    def generaSend(self,index):
        ''' Generates outgoing MPI_Send operations

            self    - partition which communication pattern is generated
            index   - string containing the postfix to be added to the section id (depending on the step)

        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaSend(index)
        return out

    def generaReceive(self):
        ''' Generates incoming MPI_Recv operations

            self    - partition which communication pattern is generated
            index   - string containing the postfix to be added to the section id (depending on the step)

        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaReceive()
        return out

    def generaCalcolo(self):
        ''' Funzione che genera l'aggiornamento della matrice in MATLAB
            
        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaCalcolo()
        return out

    def generaCalcoloInterno(self,sourceId,targetId):
        out = ""
        localSectionTag = self.getLocalSectionTag()
        #for i in range(self.dim):
        #    localSectionTag.append(1)
            
        localSection = self[localSectionTag]
        out+=localSection.generaCalcoloC(sourceId,targetId)

        return out

    def generaCalcoloEsterno(self,sourceId,targetId):
        out = ""
        localSectionTag = []
        for i in range(self.dim):
            localSectionTag.append(1)

        for s in self.sezioni.flat:
            if s.tag is not localSectionTag:
                out+=s.generaCalcoloC(sourceId,targetId)

        return out

    def generaClose(self):
        out = ""
        for s in self.sezioni.flat:
            out += s.generaClose()
        return out

    def generaCodice(self):
        ''' Metodo che genera codice matlab, non ci sono comunicazioni.
            Testa solamnete la parte relativa alle sezioni e all'albero
            della computazione

        '''
        out = ""
        out += "function b = compilato(a)\n\n"
        out += self.generaInit()
        out += self.generaCalcolo()
        out += self.generaClose()
        return out




if __name__ == "__main__":
    print "No debug for partition"
