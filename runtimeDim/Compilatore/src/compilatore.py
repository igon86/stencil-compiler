__author__ = "andrealottarini"
__date__ = "$30-gen-2012 19.53.00$"


from point import *
from section import *
from partition import *
from point import *
from shape import *
from stepmodel import *
from stepmodelqt import *

import config

import time

if __name__ == "__main__":
    
    #shape file is opened and read
    with open(config.SHAPE_FILENAME, "r") as f:
        shape_file_content = f.read()

    #raise TypeError

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

    with open('./stepModel','w') as f:
        f.write(str(stepModel))

    print "\n\n\n\n\n"

    time1=time.time()
    stepModel.generaAlberi()
    time2=time.time()

    print "TIME GENERATE TREES", time2-time1

    with open(config.OUTPUT_FILENAME,"w") as f:

        f.write(stepModel.generaCodiceC())
    
