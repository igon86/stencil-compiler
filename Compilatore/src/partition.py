import util
import generatore
# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.07$"

import numpy as np

from section import *
import config

from communicationList import *

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
                    if config.SHIFT:
                        print "SHIFT SECTION "+str(coordinate)
                        element[index] = SectionShift(copy.deepcopy(coordinate),self)
                    else:
                        print "NAIVE SECTION"+str(coordinate)
                        element[index] = Section(copy.deepcopy(coordinate),self)
                    #print "stampo cosa ho fatto: " +str(index)+" " + str(coordinate)
                    #print self
                coordinate.pop()
            return False
        else:
            return True

    def __init__(self,shape,finalSize,id):

        # if finalSize is less than size then an error is raised,
        # in order to debug the tree mechanism WITHOUT ESPANSION
        # finalSize should have the same value of self.size
        self.id= id
        self.shape = shape
        print "sono una partizione e mi e arrivato: ",self.shape
        self.ordine = shape.ordine
        print "Un lato e lungo",finalSize

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

        print "COSTRUISCO LA LISTA DELLA COMUNICAZIONE"
        self.communicationList = CommList()
        print self        
        goodSections = len(filter(lambda x:x.isGood,self.sezioni.flat))
        while len(self.communicationList) < goodSections:
            for s in self.sezioni.flat:
                if s.isGood:
                    self.communicationList.addSection(s)
        print str(self.communicationList)
        # I acquire the number of steps that this partition requires
        self.numberOfSteps = len(self.communicationList.commList)
                             


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
        return "sono una partizione\n" +str(self.sezioni) +\
        "questa e la lista delle comunicazioni"+str(self.communicationList)

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

        out += "\tint local"
        for i in range(self.dim):
            out += ("["+str(self.finalSize)+"]")
        out +=";\n\n"
        
        for s in self.sezioni.flat:
            out += s.generaInitC()
        return out

    def generaFillSections(self):
        out = ""
        #stampa di debug della matrice local
        out += '#if DEBUG\n'
        for i in range(self.dim):
            out += ("for (i"+str(i)+"=0;i"+str(i)+"<"+str(self.finalSize)+";i"+str(i)+"++){\n")
        out += 'fprintf(localfp,"%d\\t",local'
        for i in range(self.dim):
            out += ("[i"+str(i)+"]")
        out += ");\n"
        for i in range(self.dim):
            out += ("}\n")
        out += '#endif\n'
        for s in self.sezioni.flat:
            out += s.generaFillSection()
        return out

    def generaCondensa(self):
        out = ""
        for s in self.sezioni.flat:
            out += s.generaCondensa()
        return out

    def generaSend(self,subscript,index):
        ''' Generates outgoing MPI_Send operations

            self    - partition which communication pattern is generated
            index   - string containing the subscript to be added to the section id (depending on the step)

        '''
        out = ""
        for section in self.communicationList[index]:
            out += section.generaSend(subscript)
        return out

    def generaReceive(self,index):
        ''' Generates incoming MPI_Recv operations

            self    - partition which communication pattern is generated
            index   - string containing the postfix to be added to the section id (depending on the step)

        '''
        out = ""
        for section in self.communicationList[index]:
            out += section.generaReceive()
        return out

    def generaCalcolo(self):
        ''' Funzione che genera l'aggiornamento della matrice in MATLAB
            
        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaCalcolo()
        return out

    def generaCalcoloInterno(self,sourceId,targetId,start=None,end=None):
        out = ""
        localSectionTag = self.getLocalSectionTag()
            
        localSection = self[localSectionTag]        
        out += localSection.generaDebugPrint(sourceId)
        out+=localSection.generaCalcoloC(sourceId,targetId,start,end)
        out += localSection.generaDebugPrint(targetId)

        return out

    def generaCalcoloEsterno(self,sourceId,targetId):
        out = ""
        localSectionTag = self.getLocalSectionTag()

        for s in self.sezioni.flat:
            if s.tag != localSectionTag:
                out += s.generaDebugPrint(sourceId)
                out+=s.generaCalcoloC(sourceId,targetId)
                out += s.generaDebugPrint(targetId)
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
