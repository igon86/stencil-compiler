#include "algebric.h"
#include "supporto.h"
#include "macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCATTER_MATRIX "matrix_pre"

void init_sections(sezione* sezioni,int my_rank){
	
	/* indici */
	int i,j,k;
	
	/* queste variabili sono utilizzate per determinare i rank dei processi adiacenti */
	int inizio;
	int modulo;
	int coordinata;
	int primo;
	
	
	for (i = 0; i < num_sezioni; i++) {

		sezioni[i].Dimensioni = malloc(sizeof(int)*dim);
		
		/*		INIZIALIZZAZIONE TAG
			ogni sezione ha associato un tag - simile a quello assegnato dal compilatore
		 */
		sezioni[i].tag = malloc(sizeof(int) * dim);
		for (j = 0; j < dim; j++) {
			sezioni[i].tag[j] = (i / (int) pow(3, j)) % 3 - 1;
		}
		
		sezioni[i].rank = my_rank;
		
		/*		INIZIALIZZAZIONE RANK
			per ogni sezione si determina il rank del processo con cui si andrà a comunicare
			questa fase è la più importante
		 */
		for (k = 0; k < dim; k++) {
			inizio = sezioni[i].rank;
			modulo = (int) pow(ppd, k + 1);
			coordinata = inizio / modulo;
			primo = sezioni[i].tag[k] * ((int) pow(ppd, k));
			sezioni[i].rank =
			(sezioni[i].rank + primo + modulo) % modulo +
			coordinata * modulo;
			
		}

		/*		INIZIALIZZAZIONE TAG PROCESSO ADIACENTE 
			a questo punto si calcola con quale sezione esterna ogni sezione interna dovrà comunicare
		 */
		sezioni[i].send_tag = 0;
		for (k = 0; k < dim; k++) {
			sezioni[i].send_tag += (-sezioni[i].tag[k] + 1) * ((int) pow(3, k));
		}		
		
	}			/* LOOP on SEZIONI */
	
	
}

void scatter(DATATYPE* local){
	/* puntatore file dei dati */
	FILE* input;
	/* puntatore alla matrice che verra scatterizzata */
	FILE* out;
	/* array di partizioni */
	DATATYPE* partitions[p];
	/* variabile temporanea per la la lettura del file */
	DATATYPE temp;
	/* indici per i cicli for */
	int i,j;
	/* indice di partizione e offset interno */
	int part_index,part_offset;
	/* array per le coordinate */
	part_id result;
	/* matrice su cui scrivo i dati letti da data */
	DATATYPE matrix[M];
	
	/* apertura del file dei dati */
	input = fopen(INPUT_MATRIX,"r");
	
	ec_meno1( input, "Problema nell'apertura del file dei dati\n" );
	ec_null( input, "Problema nell'apertura del file dei dati\n" );
	
#ifdef DEBUG	
	printf("SCATTER: \n");
#endif	
	/* inizializzazione partizioni */
	for(i = 0; i < p; i++ ){
		partitions[i] = malloc(sizeof(DATATYPE)* localsize);
	}
#ifdef DEBUG	
	printf("PARTIZIONI INIZIALIZZATE\n");
#endif		
	for(i=0; i< M; i++){
		/* leggo il prossimo elemento */
		fscanf(input,FORMAT,&temp);
		matrix[i]=temp;
		
		/* creazione delle coordinate*/
		result = offset2partition(dim,lato,s,i);
		
		/* assegnamento*/
		*(partitions[result.part_index]+result.part_offset) = temp;
		
	}/* LOOP i*/
#ifdef DEBUG	
	printf("RIEMPITE LE PARTIZIONI\n");		

	writeMatrix(SCATTER_MATRIX,matrix);
		
	printf("SCRITTA LA MATRICE SU FILE\n");
#endif		
	/* copio gli elementi nella mia partizione locale */
	for (i=0; i < localsize; i++){
		local[i] = *(partitions[0]+i);
	}
	
	/*invio le partizioni agli altri*/
	for (i=1; i < p; i++){
		if( MPI_Send(partitions[i],localsize, MPI_DATATYPE, i, TAG, MPI_COMM_WORLD) != MPI_SUCCESS ){
			fprintf(stderr,"Fallita la MPI_Send verso %d\n",i);
		}
	}
	
#if DEBUG
	printf("SCATTER TERMINATA\n");
#endif
	
}

void gather(DATATYPE* local,DATATYPE* matrix){
	/* mi carico i dati locali in partizioni separate in cui ricevere*/
	DATATYPE* partitions[p];
	
	part_id result;
	
	/* indici */
	int i,j;
	
	/* array per le coordinate */
	int pos[dim];
	int part[dim];
	int offset[dim];
	
	/* inizializzazione partizioni */
	for(i = 0; i < p; i++ ){
		partitions[i] = malloc(sizeof(DATATYPE)*localsize);
	}
	
	/*RECUPERO DATI*/
	for (i=1; i < p ;i++){
		MPI_Recv(partitions[i],localsize, MPI_DATATYPE, i, TAG, MPI_COMM_WORLD, NULL);
	}
	
	/* COPIO I LOCALI IN PARTITIONS */
	for (i=0;i<localsize;i++){
		*(partitions[0]+i) = local[i];
	}
	
	for (i=0;i<M;i++){
		
		/* guardo la partizione e l'offset del punto i */
		result = offset2partition(dim,lato,s,i);
		
		matrix[i] = *(partitions[result.part_index]+result.part_offset);
		
	}
	
}

static void writeMatrix_1(FILE * matrix, DATATYPE *data)
{
    /* indici */
    int i, j;
	
    for (i = 0; i < M; i++) {
		
		/* questo loop e` necessario per stampare il numero corretto di spazi */
		for (j = 0; j < dim; j++) {
			
			if (i % (int) pow(lato, dim - j) == 0 && i != 0) {
				fprintf(matrix, "\n");
			}
			
		}	/* LOOP j */
		
		fprintf(matrix,FORMAT, data[i]);
		
    }	/* LOOP i */
	
	fprintf(matrix,"\n");
	
}

void writeMatrix(char *file_out, DATATYPE *data)
{
    /* puntatore al file su cui effettuare la scrittura */
    FILE *matrix;
	
    ec_meno1((int) (matrix = fopen(file_out, "w")),
			 "Problema nell'apertura del file di output");
	
	
    writeMatrix_1(matrix, data);
	
    fclose(matrix);
	
}

void printSections(FILE* localfp,sezione* sezioni)
{
	int i,j;
	fprintf(localfp,"*******************************\n");
	for(i=0;i<num_sezioni;i++){
		fprintf(localfp,"Sezione %d:\nDimensione %d \n",i,sezioni[i].Dim);
		
		for(j=0;j<sezioni[i].Dim;j++){
			fprintf(localfp,FORMAT,sezioni[i].buffer[j]);
		}
		fprintf(localfp,"\n");
	}
}
