__author__ = "andrealottarini"
__date__ = "$30-gen-2012 19.53.00$"

import sys

from point import *
from section import *
from partition import *
from point import *
from shape import *

import gc

if __name__ == "__main__":

    if gc.isenabled():
        print "garbage collection!!"
    #shape file is opened and read
    f = open("/Users/andrealottarini/Desktop/TIROCINIO/YesWeSten/PYTHON/shape", "r")
    shape_file = f.read()

    # a shape object is created from the shape_file content
    shape = Shape(shape_file)

    print "this is the shape object", shape

    #now a partition is created
    print "\n\n\n\n\n\n\n"
    partition = Partition(shape)

    print partition

    print "\n\n\n\n\n"
    #partition.sezioni.flat[0].buildTree()
    for s in partition.sezioni.flat:
        s.buildTree()