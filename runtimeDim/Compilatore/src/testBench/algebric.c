#include "algebric.h"

#include <math.h>

void offset2coordinates(int dim,int lato, int punto, int * pos){
	
	int j;
	
	for(j=0;j<dim;j++){
		pos[j] = (punto / (int) pow(lato,j)) % lato;
	}
}

void offset2coordinates_1(int dim,int* lati,int punto,int* pos){
	int k;
	int dimensione[dim + 1];
	dimensione[0] = 1;
		
	for (k = 0; k < dim; k++) {
		dimensione[k + 1] = dimensione[k] * lati[k];
		pos[k] = (punto % dimensione[k+1]) / dimensione[k];
	}
}

part_id offset2partition(int dim,int lato, int s,int punto){
	
	part_id ret;
	int part_index;
	int part_offset;
	int ppd;
	int j;
	
	int pos[dim];
	int part[dim];
	int offset[dim];
	
	/* creazione delle coordinate*/
	for(j=0;j<dim;j++){
		pos[j] = (punto / (int) pow(lato,j)) % lato;
		
		/* indice della partizione*/
		part[j] = pos[j]/s;
		/* offset all'interno della partizione*/
		offset[j] = pos[j]%s;
	}
	
	part_index = part_offset = 0;
	ppd = lato/s;
	
	/* metto insieme gli indici dimensionali per ottenere l'indice della partizione
	 e il suo offset */
	for(j=0;j<dim;j++){
		part_index = part_index + pow(ppd,j)*part[j];
		part_offset = part_offset + pow(s,j)*offset[j];
	}
	
	ret.part_index = part_index;
	ret.part_offset = part_offset;
	
	return ret;
}

void offset2tag(int dim,int lato,int ordine,int punto,int* tag){
	
	int k;
	int pos[dim];
	
	offset2coordinates(dim, lato, punto, pos);
	
	for(k=0;k<dim;k++){
		
		if(pos[k] < ordine){
			tag[k] = -1;
		}
		else{
			if(pos[k] > lato -ordine-1){
				tag[k] = +1;
			}
			else{
				tag[k] = 0;
			}
		}
		
	}/* LOOP k */	
}

static int tag2s_id(int dim,int* tag){
	int s_id;
	int k;
	
	s_id=0;
	for (k=0;k<dim;k++){
		s_id += (tag[k]+1)*3;
	}
	
	return s_id;
}

int p_coordinates2s_id(int dim,int s,int ordine,int* pos){
	int section_id;
	int k;
	
	for (k = 0; k < dim; k++) {
		if (pos[k] >= ordine) {
			section_id = section_id + ((int) pow(3, k));
		}
		if (pos[k] >= s - ordine) {
			section_id = section_id + ((int) pow(3, k));
		}
	}
	
	return section_id;
}

void s_id2tag(int dim,int section_id,int* tag){
	int k;
	
	for(k=0;k<dim;k++){
		tag[k] = section_id%3 -1;
	}
}

/* nammerda */
part_id p_offset2section(int dim,int s,int ordine,int punto){
	int pos[dim];
	int tag[dim];
	int starting_coordinates[dim];
	int section_id;
	int k;
	
	/* guardo le coordinate nella partizione */
	offset2coordinates(dim,s,punto,pos);
	
	/* guardo in quale sezione cascano */
	section_id = p_coordinates2s_id(dim,s,ordine,pos);
	
	/* di cui calcolo le starting coordinates */
	s_id2tag(dim,section_id,tag);
	
}

int coordinates2offset(int dim, int* pos,int lato,int starting_point){
	int k;
	int offset_partizione = starting_point;
	
	for (k = 0; k < dim; k++) {
		offset_partizione =
		offset_partizione + pos[k] * ((int) pow(lato, k));
	}
	return offset_partizione; 
}

int coordinates2offset_s(int dim, int* pos,int* lato){
	int offset_sezione;
	int k;
	
	offset_sezione = pos[0];
	
	for (k = 1; k < dim; k++) {
		offset_sezione =
		offset_sezione + pos[k] * ((int) pow(lato[k-1], k));
	}
	return offset_sezione;
}


