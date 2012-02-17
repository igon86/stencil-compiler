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

if __name__ == "__main__":

    #questi sono parametri messi come magic numbers!!!
    dim = 20
    filename = "/Users/andrealottarini/Desktop/TIROCINIO/YesWeSten/PYTHON/shape"
    compilato = "compilato.m"
    #shape file is opened and read
    f = open(filename, "r")
    shape_file = f.read()

    # a shape object is created from the shape_file content
    shape = Shape(shape_file)

    print "this is the shape object", shape

    #now a partition is created
    print "\n\n\n\n\n\n\n"
    partition = Partition(shape,dim)

    print partition

    print "\n\n\n\n\n"
    #partition.sezioni.flat[0].buildTree()
    for s in partition.sezioni.flat:
        s.buildTree(dim)

    with open(compilato,"w") as f:
        f.write("function b = compilato(a)\n\n")

    # THIS IS VERY VERY UGLY  
    for index,item in enumerate(partition.sezioni.flat):
        g = Generatore(item)
        g.generaInit(compilato)

    for index,item in enumerate(partition.sezioni.flat):
        g = Generatore(item)
        g.generaCodice(compilato)

    for index,item in enumerate(partition.sezioni.flat):
        g = Generatore(item)
        g.generaClose(compilato)


    #partition.createMatlabScript()
    