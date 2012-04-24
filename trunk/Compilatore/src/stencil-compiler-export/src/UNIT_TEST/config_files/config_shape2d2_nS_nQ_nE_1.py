# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$4-mar-2012 18.28.37$"

SHIFT               = False
QT                  = False
DOMAIN_EDGE_SIZE    = 16
ITERATIONS          = 2
PARALLELISM_DEGREE  = 1
OUTPUT_FILENAME     = "./testBench/compilato.c"
STEP_MODEL_OUTPUT   = "./stepModel"
MAGIC_PARAMETER     = 7
MAGIC_THRESHOLD_FOR_OFFSET  = 4

#questo e il path al file dalla shape
SHAPE_FILENAME      = "./shapes/shape2d2"

# questo file contiene la #define di MACRO
HEADER_FUNZIONE     = "../headers/macro2d1.h"


#questa cartella contiene il supporto a runtime del compilatore e i dati per la computazione
TESTBENCH_DIR       = "./testBench/"

#in questa cartella sono salvati diversi chunk di header C che il compilatore andra a inserire nel file compilato
HEADERS_DIR         = "./headers/"

# questo file contiene la matrice risulato per la computazione specificata in questo config
RISULTATO           = "../UNIT_TEST/matrices/2d2_16"


DATATYPE = "int"
OPEN_MP = True
GENERATE_CALC = True
GENERATE_COMM = True
