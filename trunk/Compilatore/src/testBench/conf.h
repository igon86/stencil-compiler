#ifndef __CONF_H
#define __CONF_H

#include <mpi.h>
#include "/Users/andrealottarini/NetBeansProjects/Compilatore/src/headers/macro3d.h"



#define STAMPA(A) if(my_rank==RANK_TEST) printf(A);
#define STAMPA2(A,B) if(my_rank==RANK_TEST) printf(A,B);

#define EMETTITORE 0
#define COLLETTORE 0
#define INPUT_MATRIX "data"
#define OUTPUT_MATRIX "matrix_post"
#define TAG 0
#define TEMPI "./shapetempi"
#define RANK_TEST 0

#define p 1
#define M 4096
#define lato 16
#define dim 3
#define s 16
#define ppd 1
#define local_section 13
#define ordine 2
#define localsize 4096
#define dim_sezione 12
#define num_sezioni 27

#endif
