

__author__="andrealottarini"
__date__ ="$6-mar-2012 16.20.45$"

from partition import *
from shape import *
import section
import copy
import math
from stepmodel import *

import time

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
        print "Il lato della partizione deve essere lungo almeno",self.partitionSize
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
        for p in self.partitions:
            for s in p.sezioni.flat:
                time1 = time.time()
                s.buildTree()
                time2 = time.time()
                tempo = time2-time1
                if tempo > 1:
                    print "TIME ALBERO CALCOLO SEZIONE",s.tag,":",tempo
                time1 = time.time()
                s.buildCommTree()
                time2 = time.time()
                tempo = time2-time1
                if tempo > 1:
                    print "TIME ALBERO COMUNICAZIONE SEZIONE",s.tag,":",tempo
        

    def __str__(self):
        return str(self.partitions[0]) + str(self.partitions[1])


if __name__ == "__main__":
    print "Hello World"
