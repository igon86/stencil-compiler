#ifndef __ALGEBRIC_H
#define __ALGEBRIC_H

#if DEBUG
	#include <stdio.h>
#endif

typedef struct {
	
	/* id unico della partizione dello spazio */
	int part_index;
	/* offset nella partizione */
	int part_offset;
	
} part_id;

/**
 Trova le coordinate di punto nello spazio della partizione (Z{lato})^dim
 
 \param		dim		spazio dimensionale attuale
 \param		lato	dimensione del lato dello spazio
 \param		punto	offset del punto
 \param		pos		coordinate (OUTPUT)
 
 \retval coordinate dell'offset nello spazio
 */
void offset2coordinates(int dim,int lato, int punto, int * pos);

/**
 Trova le coordinate di punto nello spazio della sezione (Z{lato[]})^dim
 
 \param		dim		spazio dimensionale attuale
 \param		lato	dimensioni del lati dello spazio
 \param		punto	offset del punto
 \param		pos		coordinate (OUTPUT)
 
 \retval coordinate dell'offset nello spazio
 */
void offset2coordinates_1(int dim,int* lati,int punto,int* pos);

/**
 Effettua il mapping tra due spazi cubici (lati tutti uguali) con il secondo spazio sottoinsieme del primo
 
 \param		dim		spazio dimensionale attuale
 \param		lato	dimensione del lato dello spazio iniziale
 \param		s		dimensione del lato nello spazio finale
 \param		punto	offset del punto
 
 \retval coordinate nello spazio finale del punto iniziale
 */
part_id offset2partition(int dim,int lato, int s,int punto);

/**
 Trova le coordinate (tag) della sezione relativa a un punto definito
 nello spazio della partizione
 
 \param		dim		spazio dimensionale attuale
 \param		lato	dimensione del lato dello spazio iniziale
 \param		ordine	threshold per la suddivisione dello spazio
 \param		punto	offset del punto
 \param		tag		coordinate (OUTPUT)
 
 \retval coordinate sotto forma di tag della sezione a cui
 appartiene il punto
 */
void offset2tag(int dim,int lato,int ordine,int punto,int* tag);

/**
 Effettua il mapping tra uno spazio e una sua suddivisione regolare (sezione)
 
 \param		dim		spazio dimensionale attuale
 \param		lato	dimensione del lato dello spazio iniziale
 \param		ordine	threshold per la suddivisione dello spazio
 \param		punto	offset del punto
 
 
 \retval coordinate nello spazio finale del punto iniziale
part_id offset2section(int dim,int lato, int ordine,int punto);{
	
	int tag[dim];
	
	offset2tag(dim,lato,ordine,punto,tag);
	
	
	
}
*POTREBBE NON SERVIRMI -> BOIA SE MI SERVE*/

/**
 Mappa le coordinate (pos) interne a una sezione come offset nella partizione
 
 \param		dim		spazio dimensionale attuale
 \param		pos		coordinate del punto nella sezione
 \param		lato	lato della partizione
 \param		starting_point	offset iniziale della sezione esaminata
 
 \retval offset del punto nello spazio della partizione
 */
int coordinates2offset(int dim, int* pos,int lato,int starting_point);

/**
 Mappa le coordinate (pos) interne a una sezione come offset nella sezione stessa
  
 \param		dim		spazio dimensionale attuale
 \param		pos		coordinate del punto nella sezione
 \param		lato	lati della sezione
 
 \retval offset del punto nello spazio della sezione
 */
int coordinates2offset_s(int dim, int* pos,int* lato);

#endif
