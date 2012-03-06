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
from stepmodelqt import *

import config

if __name__ == "__main__":
    
    #shape file is opened and read
    f = open(config.SHAPE_FILENAME, "r")
    shape_file_content = f.read()

    # a shape object is created from the shape_file content
    shape = Shape(shape_file_content)

    print "this is the shape object\n", shape

    #now a partition is created
    print "\n\n\n\n\n\n\n"
    if config.QT:
        print "STEP MODEL QT"
        stepModel = StepModelQT(shape,config.DOMAIN_EDGE_SIZE,config.ITERATIONS,config.PARALLELISM_DEGREE)
    else:
        print "STEP MODEL NAIVE"
        stepModel = StepModel(shape,config.DOMAIN_EDGE_SIZE,config.ITERATIONS,config.PARALLELISM_DEGREE)

    with open(config.STEP_MODEL_OUTPUT,'w') as f:
        f.write(str(stepModel))
    print "\n\n\n\n\n"

    stepModel.generaAlberi()

    with open(config.OUTPUT_FILENAME,"w") as f:

        f.write(stepModel.generaCodiceC())

    