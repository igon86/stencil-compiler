import pdb
# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.07$"

import numpy as np

from section import *
import config

import pdb

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

    def __init__(self,shape,id):

        # if finalSize is less than size then an error is raised,
        # in order to debug the tree mechanism WITHOUT ESPANSION
        # finalSize should have the same value of self.size
        self.shape = shape
        print "sono una partizione e mi e arrivato: ",self.shape
        self.ordine = shape.ordine
        
        #the id serves to distinguish the different partitions in a step model
        self.id = id

        # NOTA: il numero di dimensioni: cioe bidimensionale. tridimensionale etc
        # viene ricavato dal file di shape
        self.dim = shape.dim


        #computes size
        self.size = config.MAGIC_PARAMETER*self.ordine + 1
        print "Therefore my size for compilation purposes will be",self.size
        
#        if finalSize < self.size:
#            raise ValueError("Final Dimension"+str(finalSize)+" smaller than compiler partition size"+str(self.size))
#        elif finalSize == self.size:
#            print "TREE WILL NOT BE EXPANDED"
#        self.finalSize = finalSize

        #creates array of sections
        dimensioni=[]
        for i in range(self.dim):
            dimensioni.append(3)
        #print dimensioni
        #the dim-dimensional matrix of sections is created empty
        self.sezioni = np.empty(dimensioni,dtype=Section)

        #every section in the matrix is initialized
        self.recursiveInit(self.sezioni,0,[])

        self.communicationList = CommList()

        print "\n\nHELLO EVERYONE IM THE PARTITION\n\n"
        
        print self

        print "\n\n\nCOSTRUISCO LA LISTA DELLA COMUNICAZIONE\n\n\n"
        
        
        
        goodSections = len(filter(lambda x:x.isGood,self.sezioni.flat))
        while len(self.communicationList) < goodSections:
            for s in self.sezioni.flat:
                if s.isGood:
                    self.communicationList.addSection(s)
                    print self.communicationList
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
        for section in filter(lambda x:x.isGood,self.sezioni.flat):
            if section.isInner(p):
                point = section.getPoint(p)
                if point is not None and section.isNotShiftPoint(point):
                    out.append(point)
#                for point in section.points.flat:
#                    # a point in the send section might be a shift point
#                    # a shift point should never be used for communication or as a memcpy source
#                    if p.isSimilar(point) and section.isNotShiftPoint(point):
#                        out.append(point)
#                        break

                        
            if section.isOuter(p):
                point = section.getPoint(p)
                if point is not None:
                    out.append(point)
#                for point in section.opoints.flat:
#                    if p.isSimilar(point):
#                        out.append(point)
#                        break
        return out

    def generaInitC(self):
        ''' This method generates all the C code relative to variables '''
        
        out = "\n/*     Variabili generate dal compilatore  */\n\n"

        # indexes of for loops
        for i in range(self.dim):
            out += ("\tint i"+str(i)+";\n")
        out +="\n"

        #allocation of data matrix (EMITTER ONLY)
        out += "\tif (my_rank == EMETTITORE){\n\t\tmatrix = malloc(sizeof("+config.DATATYPE+")*pow(domain_edge_size,dim));\n\t}\n"

        #allocation of partition matrices
        out += ("\t"+config.DATATYPE+ " (* local)")
        for index in range(self.dim):
            if index > 0:
                out += ("[partition_edge_size]")
        out += " = malloc(sizeof("+     config.DATATYPE +")"
        for index in range(self.dim):
            out += "*partition_edge_size"
        out += ");\n"

        #generation of section buffers of the
        for s in self.sezioni.flat:
            out += s.generaInitC()
        return out

    def generaLocalDebugPrint(self):
        out = ""
        #stampa di debug della matrice local
        out += '#if DEBUG\nfprintf(localfp,"PARTITION: \\n\\n");\n'
        for i in range(self.dim):
            out += ("for (i"+str(i)+"=0;i"+str(i)+"<partition_edge_size;i"+str(i)+"++){\n")
        out += 'fprintf(localfp,FORMAT,local'
        for i in range(self.dim):
            out += ("[i"+str(i)+"]")
        out += ");\n"
        for i in range(self.dim):
            if i >0:
                out += 'fprintf(localfp,"\\n");\n'
            out += ("}\n")

        out += '#endif\n'
        return out

    def generaFillSections(self):
        ''' This method generates the C code relative to the partitioning of data
            from scatter matrix (local) to section buffers

        '''
        out = ""
        #stampa di debug della matrice local
        out += self.generaLocalDebugPrint()

        #partizionamento dei dati
        for s in self.sezioni.flat:
            out += s.generaFillSection()
        return out

    def generaCondensa(self):
        ''' This method generates the C code for retrieving the final partition data
            from section buffers

        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaCondensa()

        #stampa di debug della matrice local
        out += self.generaLocalDebugPrint()
        
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

    def generaSectionPrints(self):
        ''' this method generates the code to print the content of every section
            in partition self

        '''
        out = ""
        for s in self.sezioni.flat:
            out += s.generaDebugPrint(str(self.id))

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
        if config.OPEN_MP:
            out += '#pragma omp parallel sections private('
            for i in range(self.dim):
                if i > 0:
                    out +=","
                out += "i"+str(i)
            out += ")\n{\n"
            for s in self.sezioni.flat:
                if s.tag != localSectionTag:
                    out+=s.generaCalcoloC(sourceId,targetId)
                    

            if config.OPEN_MP:
                out += '\n}\n'
        else:            
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
