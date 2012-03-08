

__author__="andrealottarini"
__date__ ="$21-feb-2012 14.37.48$"

from partition import *
from shape import *
import section
import copy
import math


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
        
        p = Partition(shape,self.partitionSize,"UNICA")

        # there is only one partition in the naive method
        self.partitions = []
        self.partitions.append( p )
        self.partitions.append( None )
        self.iterazioni = iterazioni
        self.parallelism = parallelismDegree


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
            out += ("#define ordine "+str(self.shape.ordine)+"\n")
            out += ("#define localsize "+str(self.dimPartizione)+"\n")
            out += ("#define dim_sezione "+str(self.partitionSize - 2*self.shape.ordine)+"\n")
            out += ("#define num_sezioni "+str(len(self.partitions[0]))+"\n")
            out += ("\n#endif\n")
            fout.write(out)        


    def generaCodiceC(self):
        self.generaConf()
        
        partizione = self.partitions[0]
        out = ""
        with open("./headers/inizio") as f:
            out += f.read()

        out += partizione.generaInitC()
        
        with open("./headers/MPI_startup") as f:
            out += f.read()


        out += partizione.generaFillSections()
        # start generating iterations
        if self.iterazioni % len(self.partitions):
            raise ValueError("Number of iterations is not divisible by the number of iterations of the step model")

        iter = self.iterazioni / len(self.partitions)

        out += ("for ( i = 0 ; i < "+str(iter)+";i++){\n" )

        for index,p in enumerate(self.partitions):
            print "GENRATING PARTITION",index,"CONTAINING",p.numberOfSteps,"STEPS"

            source = index
            target = (index+1) % len(self.partitions)

            #this indicates which part of the local section has been generated
            p.generated = 0
            
            # the legnth of the edgeof the local section is computed
            # FIX this should become an attriute of stepmodel
            p.localSectionEdge =  p.finalSize - 2*self.shape.ordine

            for step in range(p.numberOfSteps):
                # I firstly compute which interval of the local section should be updated in this partition step
                intervalLength = int(math.ceil((p.localSectionEdge-p.generated)/(p.numberOfSteps-step)))
                print "this interval has length",intervalLength
                start = p.generated
                end = int(start + intervalLength - 1)
                print "this interval goes from ",start," to ",end
                out += p.generaSend(str(source),step)
                out += p.generaCalcoloInterno(str(source),str(target),start,end)
                out += p.generaReceive(step)
                p.generated +=intervalLength

            out += p.generaCalcoloEsterno(str(source),str(target))
            
        out += "}\n"

        out +='STAMPA("calcolo terminato\\n")\n'

        out += partizione.generaCondensa()

        with open("./headers/fine") as f:
            out += f.read()

        return out


    def getPartition(self):
        return self.partitions[0]

    def __str__(self):
          return str(self.partitions[0])


if __name__ == "__main__":
    print "Not yet supported"
