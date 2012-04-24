#include "algebric.h"
#include "supporto.h"
#include "macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCATTER_MATRIX "matrix_pre"

int partition_edge_size;
int localsize;                  /* Number of elements in a partition       */
int local_section_edge_size;    /* lenght of the edge of the local section */

extern int p;
extern int domain_edge_size;
extern int iterations;
extern FILE* localfp;

static int ppd;
static int domainsize;

int extension;               /* Difference between domain_edge_size and compile-time size*/


int max(int a,int b){
    if (a<b) return b; else return a;
}

int min(int a, int b){
    if (a<b) return a; else return b;
}

void check_init_parameters(){
    /* checks that the parallelism degree is correct */
    if (p <= 0){
        fprintf(stderr,"Parallelism Degree should be positive\n");
        exit(EXIT_FAILURE);
    }
    /* check that the domain edge size is correct */
    if (domain_edge_size <=0 ){
        fprintf(stderr,"Domain Edge Size should be positive\n");
        exit(EXIT_FAILURE);
    }
    /* check that the number of iterations is correct*/
    if (iterations %2 != 0 && iterations <= 0){
        fprintf(stderr,"Number of iterations should be positive and even\n");
        exit(EXIT_FAILURE);
    }

    /*determine the ppd parameter (number of partition per spatial dimension)*/
    ppd = pow((double) p, (double) (1 / (double) dim));
    if (floor(ppd) != ppd) {
        fprintf(stderr,"Number of spatial dimensions and parallelism degree do not agree\n");
	exit(EXIT_FAILURE);
    }
    /*determine the size of the partition*/
    partition_edge_size = domain_edge_size / ppd;
    if (floor(partition_edge_size) != partition_edge_size) {
        fprintf(stderr,"Size of the domain is not divisible by the given parallelism degree\n");
	exit(EXIT_FAILURE);
    }
    extension = partition_edge_size - compile_time_size;
    ec_neg(extension,"Size of the domain is not divisible by the given parallelism degree\n");

    localsize = pow(partition_edge_size,dim);
    domainsize = pow(domain_edge_size,dim);

    local_section_edge_size = partition_edge_size - 2*ordine;

#if DEBUG
    fprintf(localfp,"PPD is: %d\nPartition edge size is: %d\nExtension is: %d\nLocalsize is: %d\nDomainSize is: %d\n\n",ppd,partition_edge_size,extension,localsize,domainsize);

#endif
    
}

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
		
		/*	INIZIALIZZAZIONE TAG
			ogni sezione ha associato un tag - simile a quello assegnato dal compilatore
		 */
		sezioni[i].tag = malloc(sizeof(int) * dim);
		for (j = 0; j < dim; j++) {
			sezioni[i].tag[j] = (i / (int) pow(3, j)) % 3 - 1;
		}
		
		sezioni[i].rank = my_rank;
		
		/*	INIZIALIZZAZIONE RANK
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

		/*	INIZIALIZZAZIONE TAG PROCESSO ADIACENTE 
			a questo punto si calcola con quale sezione esterna ogni sezione interna dovrà comunicare
		 */
		sezioni[i].send_tag = 0;
		for (k = 0; k < dim; k++) {
			sezioni[i].send_tag += (-sezioni[i].tag[k] + 1) * ((int) pow(3, k));
		}		
		
	}			/* LOOP on SEZIONI */
	
	
}

void scatter(DATATYPE* local,DATATYPE* matrix){
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
	for(i=0; i< domainsize; i++){
		/* leggo il prossimo elemento */
		fscanf(input,FORMAT,&temp);
		matrix[i]=temp;
		
		/* creazione delle coordinate*/
		result = offset2partition(dim,domain_edge_size,partition_edge_size,i);
		
		/* assegnamento*/
		*(partitions[result.part_index]+result.part_offset) = temp;
		
	}/* LOOP i*/
#ifdef DEBUG	
	printf("RIEMPITE LE PARTIZIONI\n");		

        /* the whole domain matrix is written on the file specified by SCATTER_MATRIX*/
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

        /* elimino le partizioni */
	for(i = 0; i < p; i++ ){
		free(partitions[i]);
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
	
	for (i=0;i<domainsize;i++){
		
		/* guardo la partizione e l'offset del punto i */
		result = offset2partition(dim,domain_edge_size,partition_edge_size,i);
		
		matrix[i] = *(partitions[result.part_index]+result.part_offset);
		
	}

        /* elimino le partizioni */
	for(i = 0; i < p; i++ ){
		free(partitions[i]);
	}
	
}

static void writeMatrix_1(FILE * matrix, DATATYPE *data)
{
    /* indici */
    int i, j;
	
    for (i = 0; i < domainsize; i++) {
		
		/* questo loop e` necessario per stampare il numero corretto di spazi */
		for (j = 0; j < dim; j++) {
			
			if (i % (int) pow(domain_edge_size, dim - j) == 0 && i != 0) {
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
