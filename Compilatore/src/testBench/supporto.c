#include "algebric.h"
#include "supporto.h"
#include "macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCATTER_MATRIX "matrix_pre"


void stampaDebug(FILE* out,char* header,int* data){
	int i=0;
	
	fprintf(out,"%s : ",header);
	for (i=0;i<dim;i++){
		fprintf(out,"%d ",data[i]);
	}
	fprintf(out,"\n");
}

void condensa(sezione* sezioni,int* local){
	
	/* indici per i cicli */
	int j,k;
	int section_id;
	int offset_partizione;
	int dimensione;
	int differenze[dim];
	int pos[dim];
	
	for (j=0;j< localsize;j++){
		
		/*calcolo le coordinate */
		for(k=0; k< dim; k++){
			pos[k] =( j / (int) pow(s,k)) % s;
		}
		/* VADO A VEDERE IN CHE SEZIONE SI TROVA */
		section_id = 0;
		for(k=0;k<dim;k++){
			if(pos[k] >= ordine ){
				section_id = section_id + ((int) pow(3,k));
			}	
			if(pos[k] >= s - ordine ){
				section_id = section_id + ((int) pow(3,k));
			}
		}
		
		/* guardo le differenze con il vettore delle posizioni */
		for (k=0;k<dim;k++){
			differenze[k] = pos[k] - sezioni[section_id].starting_coordinates[k];
		}
		
		/* CALCOLO OFFSET INTERNO */
		
		offset_partizione = 0;
		dimensione = 1;
		for(k=0;k<dim;k++){
			offset_partizione = offset_partizione + differenze[k]*dimensione;
			/* guardo lo spazio dimensionale a ogni passo dato che la sezione non e` quadrata */
			if(section_id == local_section){
				dimensione = dimensione * dim_sezione;
			}
			else{
				if(sezioni[section_id].tag[k] != 0){
					dimensione = dimensione * ordine;
				}
				else{
					dimensione = dimensione * s;
				}	
			}
		}
		/* ASSEGNAMENTO */
		
		local[j] = sezioni[section_id].buffer[offset_partizione];
		
	}/* Loop on j elementi */
	
}

void fill_sections(sezione* sezioni,int* local){
	
	int i,j,k;
	int my_rank;
	
	/* array di supporto */
	int tag[dim];
	int pos[dim];
	
	for (i = 0; i < num_sezioni; i++) {
		
		/* i buffer delle varie sezioni sono gia dichiarati nello stack 
		del codice generato 
		
		sezioni[i].buffer = malloc(sizeof(int) * sezioni[i].Dim);
		*/
		
		if (i != local_section){
			for (j = 0; j < localsize; j++) {
				/* ottengo le coordinate del punto nella partizione e riempio i tag */
				
				/* compilo i tag delle'elemento */
				offset2tag(dim,s,ordine,j,tag);
				
				/* confronto dei tag */
				for (k = 0; k < dim; k++) {
					
					if (sezioni[i].tag[k] != 0
						&& sezioni[i].tag[k] != tag[k]) {
						break;
					}
					/* leggermente incasinato ma va bene */
					if (k == dim - 1) {
						/* ho verificato tutti i tag, aggiungo local[j] a sezione[i] */
						sezioni[i].buffer[sezioni[i].fill_index++] = local[j];
					}
				}
				
			}
		}
		else{
			for (j = 0; j < localsize; j++) {
				/** controllo in tutte le dimensioni di stare nei margini */
				for (k = 0; k < dim; k++) {
					pos[k] = (j / (int) pow(s, k)) % s;
					if (pos[k] < ordine || pos[k] > s - ordine - 1) {
						break;
					}
					if (k == dim - 1) {
						sezioni[i].buffer[sezioni[i].fill_index++] =
						local[j];
					}
				}
			}
			
		}
		
	}			/* LOOP on SEZIONI */
	
}	/* FILL_SECTIONS */

void init_sections(sezione* sezioni,int my_rank){
	
	/* indici */
	int i,j,k;
	
	/* le pessime variabili utilizzate per determinare il rank del processo amico */
	int inizio;
	int modulo;
	int coordinata;
	int primo;
	
	
	for (i = 0; i < num_sezioni; i++) {

		
		/* fill_index a 0 */
		sezioni[i].fill_index = 0;
		/* starting_point a -1 */
		sezioni[i].starting_point = 0;
		/* allocazione dell'array di coordinate e Dimensioni */
		sezioni[i].starting_coordinates = malloc(sizeof(int) * dim);
		sezioni[i].Dimensioni = malloc(sizeof(int)*dim);
		
		/* inizializzazione tag  */
		sezioni[i].tag = malloc(sizeof(int) * dim);
		for (j = 0; j < dim; j++) {
			sezioni[i].tag[j] = (i / (int) pow(3, j)) % 3 - 1;
		}
		/* inizializzazione rank DIPENDE DAL GRADO DI PARALLELISMO*/
		//sezioni[i].rank = neighbour_rank(sezioni[i],ppd,dim,my_rank);
		
		//goto skip;
		
		sezioni[i].rank = my_rank;
		
		for (k = 0; k < dim; k++) {
			/* chissa se funziona */
			inizio = sezioni[i].rank;
			modulo = (int) pow(ppd, k + 1);
			coordinata = inizio / modulo;
			primo = sezioni[i].tag[k] * ((int) pow(ppd, k));
			/* con il primo pezzo guardo lo shift da applicare sulla coordinata k eppoi r
			 iaggiungo la posizione (inalterata) rispetto alle altre coordinate */
			sezioni[i].rank =
			(sezioni[i].rank + primo + modulo) % modulo +
			coordinata * modulo;
			
		}
	skip:
		
		sezioni[i].send_tag = 0;
		/* inizializzazione del send_tag */
		for (k = 0; k < dim; k++) {
			sezioni[i].send_tag += (-sezioni[i].tag[k] + 1) * ((int) pow(3, k));
		}

		
		/* inizializzazione starting_coordinates */
		for (k = 0; k < dim; k++) {
			if(i == local_section){
				sezioni[i].starting_coordinates[k] = ordine;
			}
			else{
				if(sezioni[i].tag[k] <= 0){
					sezioni[i].starting_coordinates[k] = 0;
				}
				else{
					sezioni[i].starting_coordinates[k] = s - ordine;
				}
			}
			
		}
		

		
		/* inizializzazione starting point */
		for (k = 0; k < dim; k++) {
			sezioni[i].starting_point += (sezioni[i].starting_coordinates[k] * (int) pow(s,k));
		}
		

		
		/* inizializzo Dimensioni */
		for (j = 0; j < dim; j++) {
			if (i == local_section){
				sezioni[i].Dimensioni[j] = dim_sezione;
			}
			else{
				if (sezioni[i].tag[j] != 0) {
					sezioni[i].Dimensioni[j] = ordine;
				} else {
					sezioni[i].Dimensioni[j] = s;
				}
			}
		}
		

		
		/* inizializzo dim */
		sezioni[i].Dim = 1; 
		for (j = 0; j < dim; j++) {
			sezioni[i].Dim *= sezioni[i].Dimensioni[j];
		}
		

		
		
	}			/* LOOP on SEZIONI */
	
	
}

void scatter(int* local){
	/* puntatore file dei dati */
	FILE* input;
	/* puntatore alla matrice che verra scatterizzata */
	FILE* out;
	/* array di partizioni */
	int* partitions[p];
	/* variabile temporanea per la la lettura del file */
	int temp;
	/* indici per i cicli for */
	int i,j;
	/* indice di partizione e offset interno */
	int part_index,part_offset;
	/* array per le coordinate */
	part_id result;
	/* matrice su cui scrivo i dati letti da data */
	int matrix[M];
	
	/* apertura del file dei dati */
	input = fopen(INPUT_MATRIX,"r");
	
	ec_meno1( input, "Problema nell'apertura del file dei dati\n" );
	ec_null( input, "Problema nell'apertura del file dei dati\n" );
	
#ifdef DEBUG	
	printf("SCATTER: \n");
#endif	
	/* inizializzazione partizioni */
	for(i = 0; i < p; i++ ){
		partitions[i] = malloc(sizeof(int)* localsize);
	}
#ifdef DEBUG	
	printf("PARTIZIONI INIZIALIZZATE\n");
#endif		
	for(i=0; i< M; i++){
		/* leggo il prossimo elemento */
		fscanf(input,"%d\t",&temp);
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
		if( MPI_Send(partitions[i],localsize, MPI_INT, i, TAG, MPI_COMM_WORLD) != MPI_SUCCESS ){
			fprintf(stderr,"Fallita la MPI_Send verso %d\n",i);
		}
	}
	
#if DEBUG
	printf("Elementi inviati\n");
#endif
	
}

void gather(int* local,int* matrix){
	/* mi carico i dati locali in partizioni separate in cui ricevere*/
	int* partitions[p];
	
	part_id result;
	
	/* indici */
	int i,j;
	
	/* array per le coordinate */
	int pos[dim];
	int part[dim];
	int offset[dim];
	
	/* inizializzazione partizioni */
	for(i = 0; i < p; i++ ){
		partitions[i] = malloc(sizeof(int)*localsize);
	}
	
	/*RECUPERO DATI*/
	for (i=1; i < p ;i++){
		MPI_Recv(partitions[i],localsize, MPI_INT, i, TAG, MPI_COMM_WORLD, NULL);
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

/* come cazzo fa ad avere lato e dim!!! */
static void writeMatrix_1(FILE * matrix, int *data)
{
    /* indici */
    int i, j;
	
    for (i = 0; i < M; i++) {
		
		/* questo loop e` necessario per stampare il numero corretto di spazi */
		for (j = 0; j < dim; j++) {
			
			if (i % (int) pow(lato, dim - j) == 0 && i != 0) {
				fprintf(matrix, "\n");
			}
			
		}			/* LOOP j */
		
		fprintf(matrix, "%d\t", data[i]);
		
    }				/* LOOP i */
	
	fprintf(matrix,"\n");
	
}

void writeMatrix(char *file_out, int *data)
{
    /* puntatore al file su cui effettuare la scrittura */
    FILE *matrix;
	
    ec_meno1((int) (matrix = fopen(file_out, "w")),
			 "Problema nell'apertura del file di output");
	
    //printf("FILE di USCITA APERTO\n");
	
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
			fprintf(localfp,"%d ",sezioni[i].buffer[j]);
		}
		fprintf(localfp,"\n");
	}
}

void leggi(int* matrix){
	/* puntatore file dei dati */
	FILE* input;
	/* indice del for */
	int i;
	int temp;
	
	/* apertura del file dei dati */
	ec_meno1((int) ( input = fopen(INPUT_MATRIX,"r") ), "Problema nell'apertura del file dei dati\n" );
	
	for(i=0; i< M; i++){
		/* leggo il prossimo elemento */
		fscanf(input,"%d\t",&temp);
		matrix[i]=temp;
		
	}/* LOOP i*/
}
