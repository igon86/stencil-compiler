#ifndef __CONF_H
#define __CONF_H

#include <mpi.h>

#include "funzione.h"

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
#define M 144
#define lato 12
#define dim 2
#define s 12
#define ppd 1
#define local_section 4
#define ordine 2
#define localsize 144
#define dim_sezione 8
#define num_sezioni 9

#endif
