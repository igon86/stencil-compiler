

__author__="andrealottarini"
__date__ ="$6-mar-2012 16.20.45$"

from partition import *
from shape import *
import section
import copy
import math
from stepmodel import *


class StepModelQT(StepModel):

    def __init__(self,shape,finalDimension,iterazioni,parallelismDegree):
        ''' This particular init implements
            the naive method

        '''
        if type(shape).__name__ is not 'Shape':
            raise TypeError('Step Model requires a shape object to be initialized')

        # ORA FACCIO UN BEL PO DI TEST E MI SALVO UN SACCO DI INFORMAZIONI
        # CHE FINISCONO NEL CONF.H
        # niente leaka sotto a parte il lato di una partizione e la shape
        # DEVO METTERE DEI CAZZO DI NOMI SIGNIFICATIVI
        self.shape = shape

        self.ppd = math.pow(float(parallelismDegree),(float(1)/float(self.shape.dim)))
        if math.floor(self.ppd) != self.ppd:
            print "Partizioni per Dimensione",self.ppd
            raise ValueError("Parallelism degree "+str(parallelismDegree)+" is not compatible with the number of dimension "+str(self.shape.dim))
        self.ppd = int(self.ppd)
        # this is the size of the edge of the entire domain
        self.lato = finalDimension

        if math.floor(finalDimension / self.ppd) != (finalDimension / self.ppd):
            raise ValueError("The edge of the domain has size: "+str(finalDimension)+" which is not divisible by "+str(self.ppd))

        self.partitionSize = int(finalDimension / self.ppd)
        print "PartitionSize",self.partitionSize
        self.M = finalDimension**self.shape.dim

        self.dimPartizione = self.partitionSize**self.shape.dim

        # there is only one partition in the naive method
        self.partitions = []
        self.partitions.append( Partition(shape.getNegativeShape(),self.partitionSize,"prima") )
        self.partitions.append( Partition(shape.getPositiveShape(),self.partitionSize,"seconda") )
        self.iterazioni = iterazioni
        self.parallelism = parallelismDegree


    def generaAlberi(self):
        # I pick the first partition
        for s in self.partitions[0].sezioni.flat:
            s.buildTree()
            s.buildCommTree()
        for s in self.partitions[1].sezioni.flat:
            s.buildTree()
            s.buildCommTree()
        

    def generaConf(self):
        ''' Questo metodo genera il file conf.h
            Il file conf.h contiene un sacco di informazioni piu o meno inutili
            sulla computazione da eseguire sotto forma di define

        '''
        with open("./testBench/conf.h","w") as fout:
            out = ""
            with open("./headers/conf.h") as fin:

                out += fin.read()

            out += ("#define p "+str(self.parallelism)+"\n")
            out += ("#define M "+str(self.M)+"\n")
            out += ("#define lato "+str(self.lato)+"\n")
            out += ("#define dim "+str(self.shape.dim)+"\n")
            out += ("#define s "+str(self.partitionSize)+"\n")
            out += ("#define ppd "+str(self.ppd)+"\n")
            # ottenere l'indice della local section e una cosa tremenda
            out += ("#define local_section "+str(section.tagToIndex(self.partitions[0].getLocalSectionTag()))+"\n")
            out += ("#define ordine "+str(self.partitions[0].shape.ordine)+"\n")
            out += ("#define localsize "+str(self.dimPartizione)+"\n")
            out += ("#define dim_sezione "+str(self.partitionSize - 2*self.partitions[0].shape.ordine)+"\n")
            out += ("#define num_sezioni "+str(len(self.partitions[0]))+"\n")
            out += ("\n#endif\n")
            fout.write(out)


if __name__ == "__main__":
    print "Hello World"
