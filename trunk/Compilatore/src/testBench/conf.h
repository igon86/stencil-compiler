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

#define p 8
#define M 64000
#define lato 40
#define dim 3
#define s 20
#define ppd 2
#define local_section 13
#define ordine 2
#define localsize 8000
#define dim_sezione 16
#define num_sezioni 27

#endif
