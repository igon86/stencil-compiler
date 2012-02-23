

__author__="andrealottarini"
__date__ ="$21-feb-2012 14.37.48$"

from partition import *
from shape import *
import copy

class StepModel(object):

    def __init__(self,shape,finalDimension,iterazioni):
        ''' This particular init implements
            the naive method

        '''
        if type(shape).__name__ is not 'Shape':
            raise TypeError('Step Model requires a shape object to be initialized')

        self.partitions = []
        # there is only one partition in the naive method
        p = Partition(shape,finalDimension)
        self.partitions.append( p )
        self.partitions.append( None )
        self.iterazioni = iterazioni


    def generaAlberi(self):
        # I pick the first pa
        for s in self.partitions[0].sezioni.flat:
            s.buildTree()
        # the partition is copied
        self.partitions[1] = copy.copy(self.partitions[0])


    def generaConf(self):
        ''' Questo metodo genera il file conf.h
            Il file conf.h contiene un sacco di informazioni piu o meno inutili
            sulla computazione da eseguire sotto forma di define

        '''
        with open("./testBench/conf2.h",w) as f:
            pass

        


    def generaCodiceC(self):
        partizione = self.partitions[0]
        out = ""
        with open("./headers/inizio") as f:
            out += f.read()

        out += partizione.generaInitC()
        
        with open("./headers/MPI_startup") as f:
            out += f.read()

        if self.iterazioni % len(self.partitions):
            raise ValueError("Number of iterations is not divisible by the number of iterations of the step model")

        iter = self.iterazioni / len(self.partitions)

        out += ("for ( i = 0 ; i < "+str(iter)+";i++){\n" )

        for index,p in enumerate(self.partitions):
            print "FANCULO",index

            source = index
            target = (index+1) % len(self.partitions)

            out += p.generaSend(str(source)) 
            out += p.generaCalcoloInterno(str(source),str(target)) 
            out += p.generaReceive() 
            out += p.generaCalcoloEsterno(str(source),str(target)) 
            
        out += "}\n"

        with open("./headers/fine") as f:
            out += f.read()

        return out


    def getPartition(self):
        return self.partitions[0]

    def __str__(self):

        return str(self.partitions[0])


if __name__ == "__main__":
    print "Hello World"
