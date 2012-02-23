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
#define localsize 400
#define num_sezioni 9
#define p 4
#define M 1600
#define lato 40
#define dim 2
#define s 20
#define ppd 2
#define local_section 4
#define ordine 2
#define dim_sezione 16
#define ITER 2
#define RANK_TEST 0

#endif