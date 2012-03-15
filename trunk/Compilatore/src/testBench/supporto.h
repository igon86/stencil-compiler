/** 
\file sezione.h
\author	Andrea Lottarini
\brief Funzionalita di partizionamento e sectioning per il worker

 */

#ifndef __SUPPORTO_H
#define __SUPPORTO_H

#include <stdio.h>

#include "conf.h"
#include "macro.h"

#define SEND(a,b,c,d,e,f) \
fprintf(localfp,"faccio una send a %d di dimensione %d con tag %d :\n",d,b,e); \
fflush(localfp); \
MPI_Send(a,b,c,d,e,f)

#define RECEIVE(a,b,c,d,e,f,g) \
fprintf(localfp,"faccio una receive da %d con tag %d\n",d,e); \
fflush(localfp); \
MPI_Recv(a,b,c,d,e,f,g)

typedef struct {

	/* coordinate della sezione */
	int* tag;
	/* dimensione del buffer */
	int Dim;
	/* rank del processo con cui comunico */
	int rank;
	/* dimensioni */
	int* Dimensioni;
	/* buffer della sezione*/
	DATATYPE* buffer;
	
	/* tag del messaggio in uscita */
	int send_tag;

} sezione;

void init_sections(sezione* sezioni,int my_rank);

void scatter(DATATYPE* local);

void gather(DATATYPE* local,DATATYPE* matrix);

void printSections(FILE* localfp,sezione* sezioni);

void writeMatrix(char* file_out, DATATYPE* data);
 
#endif
