

__author__="andrealottarini"
__date__ ="$21-feb-2012 14.37.48$"

from partition import *
from shape import *
import section
import copy
import math

import config
import os.path

class StepModel(object):

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
        

#        self.ppd = math.pow(float(parallelismDegree),(float(1)/float(self.shape.dim)))
#        if math.floor(self.ppd) != self.ppd:
#            print "Partizioni per Dimensione",self.ppd
#            raise ValueError("Parallelism degree "+str(parallelismDegree)+" is not compatible with the number of dimension "+str(self.shape.dim))
#        self.ppd = int(self.ppd)
#        # this is the size of the edge of the entire domain
#        self.lato = finalDimension
#
#        if math.floor(finalDimension / self.ppd) != (finalDimension / self.ppd):
#            raise ValueError("The edge of the domain has size: "+str(finalDimension)+" which is not divisible by "+str(self.ppd))
#
#        self.partitionSize = int(finalDimension / self.ppd)
#        print "Il lato della partizione sara lungo ",self.partitionSize
#        self.M = finalDimension**self.shape.dim
#
#        self.dimPartizione = self.partitionSize**self.shape.dim
#
#        self.parallelism = parallelismDegree
#        print "GRADO DI PARALLELISMO",self.parallelism
        
        p = Partition(shape,0)

        # there is only one partition in the naive method
        self.partitions = []
        self.partitions.append( p )
        self.partitions.append( None )        
        


    def generaAlberi(self):
        # I pick the first partition
        for s in self.partitions[0].sezioni.flat:
            s.buildTree()
            s.buildCommTree()
        # the partition is copied
        # FIX THIS, IT"S UGLY
        self.partitions[1] = copy.copy(self.partitions[0])


    def generaConf(self):
        ''' Questo metodo genera il file conf.h
            Il file conf.h contiene un sacco di informazioni piu o meno inutili
            sulla computazione da eseguire sotto forma di define

        '''        
        assert os.path.isdir(config.TESTBENCH_DIR)
        with open(config.TESTBENCH_DIR+"conf.h","w") as fout:            
            out = ""
            out += '#ifndef __CONF_H\n#define __CONF_H\n\n#include <mpi.h>\n'
            
            # include for OPENMP
            if config.OPEN_MP:
                out += '#include <omp.h>\n'

            # an include is added for the .h file containing the definition of the function
            out += '#include "'+config.HEADER_FUNZIONE +'"\n'
            
            # basic information is added from a minimal conf file
            with open(config.HEADERS_DIR+"conf.h") as fin:
                out += fin.read()

            # user defined data type
            out += ('#define DATATYPE ')+str(config.DATATYPE)+"\n"
            dict = {'int': '"%d\\t"\n','double': '"%lf\\t"\n','float': '"%f\\t"\n'}
            # a format string to output specified data type
            out += "#define FORMAT "+dict[config.DATATYPE]
            dict = {'int': 'MPI_INT\n','double': 'MPI_DOUBLE\n','float': 'MPI_FLOAT\n'}
            # corresponding MPI datatype
            out += "#define MPI_DATATYPE "+dict[config.DATATYPE]

            out += ("#define num_sezioni "+str(len(self.partitions[0]))+"\n")
            out += ("#define local_section "+str(section.tagToIndex(self.partitions[0].getLocalSectionTag()))+"\n")
            out += ("#define ordine "+str(self.partitions[0].shape.ordine)+"\n")
            out += ("#define dim "+str(self.shape.dim)+"\n")
            out += "#define compile_time_size "+str(self.partitions[0].size)+"\n"
#            out += ("#define p "+str(self.parallelism)+"\n")
#            out += ("#define M "+str(self.M)+"\n")
#            out += ("#define lato "+str(self.lato)+"\n")
            
#            out += ("#define s "+str(self.partitionSize)+"\n")
#            out += ("#define ppd "+str(self.ppd)+"\n")
            # ottenere l'indice della local section e una cosa tremenda
            
            
            #out += ("#define localsize "+str(self.dimPartizione)+"\n")
            #out += ("#define dim_sezione "+str(self.partitionSize - 2*self.partitions[0].shape.ordine)+"\n")
            
            out += ("\n#endif\n")
            fout.write(out)        


    def generaCodiceC(self):
        print "GENERAZIONE CODICE"
        self.generaConf()
        
        partizione = self.partitions[0]
        out = ""
        with open(config.HEADERS_DIR+"inizio") as f:
            out += f.read()

        out += partizione.generaInitC()

        with open(config.HEADERS_DIR+"MPI_startup") as f:
            out += f.read()

        out += partizione.generaFillSections()
        out += partizione.generaSectionPrints()
#        # start generating iterations
#        if self.iterazioni % len(self.partitions):
#            raise ValueError("Number of iterations is not divisible by the number of iterations of the step model")
#
#        iter = self.iterazioni / len(self.partitions)
#
#        out += ("for ( i = 0 ; i < "+str(iter)+";i++){\n" )
#
#        for index,p in enumerate(self.partitions):
#            print "GENRATING PARTITION",index,"CONTAINING",p.numberOfSteps,"STEPS"
#
#            source = index
#            target = (index+1) % len(self.partitions)
#
#            #this indicates which part of the local section has been generated
#            p.generated = 0
#
#            # the legnth of the edgeof the local section is computed
#            # FIX this should become an attriute of stepmodel
#            p.localSectionEdge =  p.finalSize - 2*self.shape.ordine
#
#            for step in range(p.numberOfSteps):
#                # I firstly compute which interval of the local section should be updated in this partition step
#                intervalLength = int(math.ceil((p.localSectionEdge-p.generated)/(p.numberOfSteps-step)))
#                print "this interval has length",intervalLength
#                start = p.generated
#                end = int(start + intervalLength - 1)
#                print "this interval goes from ",start," to ",end
#                out += p.generaSend(str(source),step)
#                out += p.generaCalcoloInterno(str(source),str(target),start,end)
#                out += p.generaReceive(step)
#                p.generated +=intervalLength
#
#            out += p.generaCalcoloEsterno(str(source),str(target))
#
#        out += "}\n"
#
#        out +='STAMPA("calcolo terminato\\n")\n'

        out += partizione.generaCondensa()

        with open(config.HEADERS_DIR+"fine") as f:
            out += f.read()

        return out


    def getPartition(self):
        return self.partitions[0]

    def __str__(self):
          return str(self.partitions[0])


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
        self.partitions.append( Partition(shape.getNegativeShape(),self.partitionSize,0) )
        self.partitions.append( Partition(shape.getPositiveShape(),self.partitionSize,1) )
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
    print "Not yet supported"
