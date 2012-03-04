import partition
__author__ = "andrealottarini"
__date__ = "$30-gen-2012 19.53.00$"

import sys

from point import *
from section import *
from partition import *
from point import *
from shape import *
from generatore import *
from stepmodel import *

if __name__ == "__main__":

    #questi sono parametri messi come magic numbers!!!
    dim = 40
    iterazioni = 2
    gradoDiParallelismo = 8
    filename = "/Users/andrealottarini/Desktop/TIROCINIO/YesWeSten/PYTHON/shape3d"
    compilato = "./testBench/compilato.c"

    QT = False
    Shift = True
    
    #shape file is opened and read
    f = open(filename, "r")
    shape_file = f.read()

    # a shape object is created from the shape_file content
    shape = Shape(shape_file)

    print "this is the shape object\n", shape

    #now a partition is created
    print "\n\n\n\n\n\n\n"
    if QT:
        stepModel = StepModelQT(shape,dim,iterazioni,gradoDiParallelismo)
    else:
        stepModel = StepModel(shape,dim,iterazioni,gradoDiParallelismo)

    print stepModel
    print "\n\n\n\n\n"

    stepModel.generaAlberi()

    with open(compilato,"w") as f:
#        f.write("function b = compilato(a)\n\n")
#
#    # THIS IS VERY VERY UGLY
#    for index,item in enumerate(partition.sezioni.flat):
#        g = Generatore(item)
#        g.generaInit(compilato)
#
#    for index,item in enumerate(partition.sezioni.flat):
#        g = Generatore(item)
#        g.generaCodice(compilato)
#
#    for index,item in enumerate(partition.sezioni.flat):
#        g = Generatore(item)
#        g.generaClose(compilato)

        f.write(stepModel.generaCodiceC())


    #partition.createMatlabScript()
    