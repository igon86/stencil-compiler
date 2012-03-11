/* generato.c 
  * 
  *	Output del compilatore 
  */ 
 
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <sys/time.h>
 
 #include "conf.h" 
 #include "supporto.h" 
 
 #define LOTS_OF_CHAR 100
 #define   OUTPUT_MATRIX "./matrixpost"
 /******************************************************************* 
 					MAIN 
  *******************************************************************/ 
 
 main(int argc, char *argv[]) 
 { 
 	
 	int my_rank;					/* rank of process				*/ 
 	MPI_Status status;				/* return status for MPI_Recv	*/ 
 	
 	//int local[localsize];			/* dati locali del metodo		*/
 	
 	FILE*	in; 
 	FILE*	out; 
 	FILE*	tempi;
 	FILE* localfp; 
 	char filename[LOTS_OF_CHAR]; 
	
 	int matrix[M];
	
	sezione sezioni[num_sezioni];
	
	struct timeval tv1,tv2;
	int t1[p];
	int t2[p];
	int temp1;
	int temp2;

        int i;


	/* VARIABILI GENERATE DAL COMPILATORE */
	int i0;
	int i1;

	int local[16][16];

	int s00_0[2][2];
	int s00_1[2][2];
	int o00[2][2];
	sezioni[0].buffer = (int*) s00_0;
	int s01_0[2][16];
	int s01_1[2][16];
	int o01[2][16];
	sezioni[1].buffer = (int*) s01_0;
	int s02_0[2][2];
	int s02_1[2][2];
	int o02[2][2];
	sezioni[2].buffer = (int*) s02_0;
	int s10_0[16][2];
	int s10_1[16][2];
	int o10[16][2];
	sezioni[3].buffer = (int*) s10_0;
	int s11_0[12][12];
	int s11_1[12][12];
	int o11[12][12];
	sezioni[4].buffer = (int*) s11_0;
	int s12_0[16][2];
	int s12_1[16][2];
	int o12[16][2];
	sezioni[5].buffer = (int*) s12_0;
	int s20_0[2][2];
	int s20_1[2][2];
	int o20[2][2];
	sezioni[6].buffer = (int*) s20_0;
	int s21_0[2][16];
	int s21_1[2][16];
	int o21[2][16];
	sezioni[7].buffer = (int*) s21_0;
	int s22_0[2][2];
	int s22_1[2][2];
	int o22[2][2];
	sezioni[8].buffer = (int*) s22_0;
	/* Start up MPI */
	MPI_Init(&argc, &argv);

	/* Find out process rank  */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

#if DEBUG
        /* Apertura del file di log locale */
        sprintf(filename, "PROCESSO_%d", my_rank);
        localfp = fopen(filename, "w");
#endif

	/* SCATTER DEI DATI */
	if (my_rank == EMETTITORE) {

		scatter(local);

	}else {

		/* RECEIVE DELLE PARTIZIONI */
		MPI_Recv(local, localsize, MPI_INT, EMETTITORE, TAG, MPI_COMM_WORLD,&status);

	}

	/* INIZIALIZZAZIONE DELLE SEZIONI */
	init_sections(sezioni,my_rank);


	/*CODICE GENERATO DAL COMPILATORE */
#if DEBUG
for (i0=0;i0<16;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",local[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
s00_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <16;i1++){
s01_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
s02_0[i0][i1]= local[i0+0][i1+14];
}
}
for (i0 = 0 ; i0 <16;i0++){
for (i1 = 0 ; i1 <2;i1++){
s10_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <12;i0++){
for (i1 = 0 ; i1 <12;i1++){
s11_0[i0][i1]= local[i0+2][i1+2];
}
}
for (i0 = 0 ; i0 <16;i0++){
for (i1 = 0 ; i1 <2;i1++){
s12_0[i0][i1]= local[i0+0][i1+14];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
s20_0[i0][i1]= local[i0+14][i1+0];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <16;i1++){
s21_0[i0][i1]= local[i0+14][i1+0];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
s22_0[i0][i1]= local[i0+14][i1+14];
}
}
for ( i = 0 ; i < 1;i++){
SEND(s01_0,32,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s02_0,4,MPI_INT,sezioni[2].rank,6,MPI_COMM_WORLD);
SEND(s10_0,32,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_0,32,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s20_0,4,MPI_INT,sezioni[6].rank,2,MPI_COMM_WORLD);
SEND(s21_0,32,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<12;i0++){
for (i1=0;i1<12;i1++){
fprintf(localfp,"%d\t",s11_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s10_0[i0+4][i1+1],s11_0[i0+0][i1+2],s01_0[i0+1][i1+3]);
	}
	for (i1 = 1 ; i1 <=9;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s11_0[i0+0][i1+2],s01_0[i0+1][i1+3]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s12_0[i0+2][i1-10],s01_0[i0+1][i1+3]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s12_0[i0+2][i1-10],s12_0[i0+1][i1-11]);
	}
}
for (i0 = 1 ; i0 <=9;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s10_0[i0+4][i1+1],s11_0[i0+0][i1+2],s11_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=9;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s11_0[i0+0][i1+2],s11_0[i0-1][i1+1]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s12_0[i0+2][i1-10],s11_0[i0-1][i1+1]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+2][i1-1],s12_0[i0+2][i1-10],s12_0[i0+1][i1-11]);
	}
}
for (i0 = 10 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=9;i1++){
		s11_1[i0][i1] = MACRO( s21_0[i0-10][i1+1],s11_0[i0+0][i1+2],s11_0[i0-1][i1+1]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_1[i0][i1] = MACRO( s21_0[i0-10][i1+1],s12_0[i0+2][i1-10],s11_0[i0-1][i1+1]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_1[i0][i1] = MACRO( s21_0[i0-10][i1+1],s12_0[i0+2][i1-10],s12_0[i0+1][i1-11]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<12;i0++){
for (i1=0;i1<12;i1++){
fprintf(localfp,"%d\t",s11_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
RECEIVE(o01,32,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o02,4,MPI_INT,sezioni[2].rank,2,MPI_COMM_WORLD,&status);
RECEIVE(o10,32,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,32,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o20,4,MPI_INT,sezioni[6].rank,6,MPI_COMM_WORLD,&status);
RECEIVE(o21,32,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s00_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s00_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s00_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s00_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s00_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],s01_0[i0-1][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s00_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s01_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=2;i1++){
		s01_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 3 ; i1 <=11;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 12 ; i1 <=13;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],s12_0[i0+0][i1-12],o01[i0+1][i1+1]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],o12[i0+0][i1-14],o01[i0+1][i1+1]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s01_1[i0][i1] = MACRO( s12_0[i0+2][i1-15],o12[i0+0][i1-14],o02[i0+1][i1-15]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=2;i1++){
		s01_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],s01_0[i0-1][i1+1]);
	}
	for (i1 = 3 ; i1 <=11;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],s01_0[i0+0][i1+2],s01_0[i0-1][i1+1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],s12_0[i0+0][i1-12],s01_0[i0-1][i1+1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],s12_0[i0+0][i1-12],s12_0[i0-1][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s01_1[i0][i1] = MACRO( s11_0[i0+0][i1-3],o12[i0+0][i1-14],s12_0[i0-1][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s01_1[i0][i1] = MACRO( s12_0[i0+2][i1-15],o12[i0+0][i1-14],o12[i0-1][i1-15]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s01_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s02_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s02_1[i0][i1] = MACRO( s11_0[i0+0][i1+11],o12[i0+0][i1+0],o01[i0+1][i1+15]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s02_1[i0][i1] = MACRO( s12_0[i0+2][i1-1],o12[i0+0][i1+0],o02[i0+1][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s02_1[i0][i1] = MACRO( s11_0[i0+0][i1+11],o12[i0+0][i1+0],s12_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s02_1[i0][i1] = MACRO( s12_0[i0+2][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s02_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s10_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],o01[i0+1][i1+1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o10[i0+2][i1+1],s01_0[i0+0][i1+2],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s01_0[i0+0][i1+2],s01_0[i0-1][i1+1]);
	}
}
for (i0 = 2 ; i0 <=2;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o10[i0+2][i1+1],s11_0[i0-2][i1+0],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s11_0[i0-2][i1+0],s01_0[i0-1][i1+1]);
	}
}
for (i0 = 3 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o10[i0+2][i1+1],s11_0[i0-2][i1+0],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( s10_0[i0+2][i1-1],s11_0[i0-2][i1+0],s11_0[i0-3][i1-1]);
	}
}
for (i0 = 12 ; i0 <=13;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o10[i0+2][i1+1],s11_0[i0-2][i1+0],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( s21_0[i0-12][i1-1],s11_0[i0-2][i1+0],s11_0[i0-3][i1-1]);
	}
}
for (i0 = 14 ; i0 <=14;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o20[i0-14][i1+1],s21_0[i0-14][i1+2],s10_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( o21[i0-14][i1-1],s21_0[i0-14][i1+2],s11_0[i0-3][i1-1]);
	}
}
for (i0 = 15 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( o20[i0-14][i1+1],s21_0[i0-14][i1+2],s21_0[i0-15][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_1[i0][i1] = MACRO( o21[i0-14][i1-1],s21_0[i0-14][i1+2],s21_0[i0-15][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s10_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s12_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( s11_0[i0+0][i1+11],o12[i0+0][i1+0],o01[i0+1][i1+15]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_1[i0][i1] = MACRO( s12_0[i0+2][i1-1],o12[i0+0][i1+0],o02[i0+1][i1-1]);
	}
}
for (i0 = 1 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( s11_0[i0+0][i1+11],o12[i0+0][i1+0],s12_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_1[i0][i1] = MACRO( s12_0[i0+2][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 12 ; i0 <=13;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( s21_0[i0-12][i1+13],o12[i0+0][i1+0],s12_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_1[i0][i1] = MACRO( s22_0[i0-12][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 14 ; i0 <=14;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],s12_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_1[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 15 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],s22_0[i0-15][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_1[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s12_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s20_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s20_1[i0][i1] = MACRO( o20[i0+0][i1+1],s21_0[i0+0][i1+2],s10_0[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s20_1[i0][i1] = MACRO( o21[i0+0][i1-1],s21_0[i0+0][i1+2],s11_0[i0+11][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s20_1[i0][i1] = MACRO( o20[i0+0][i1+1],s21_0[i0+0][i1+2],s21_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s20_1[i0][i1] = MACRO( o21[i0+0][i1-1],s21_0[i0+0][i1+2],s21_0[i0-1][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s20_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s21_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_1[i0][i1] = MACRO( o20[i0+0][i1+1],s21_0[i0+0][i1+2],s10_0[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=11;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s21_0[i0+0][i1+2],s11_0[i0+11][i1-1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s22_0[i0+0][i1-12],s11_0[i0+11][i1-1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s22_0[i0+0][i1-12],s12_0[i0+13][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],s12_0[i0+13][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],o12[i0+13][i1-15]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_1[i0][i1] = MACRO( o20[i0+0][i1+1],s21_0[i0+0][i1+2],s21_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=11;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s21_0[i0+0][i1+2],s21_0[i0-1][i1+1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s22_0[i0+0][i1-12],s21_0[i0-1][i1+1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],s22_0[i0+0][i1-12],s22_0[i0-1][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],s22_0[i0-1][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s21_1[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],o12[i0+13][i1-15]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s21_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s22_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s22_1[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],s12_0[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s22_1[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],o12[i0+13][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s22_1[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],s22_0[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s22_1[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],o12[i0+13][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s22_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
SEND(s01_1,32,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s02_1,4,MPI_INT,sezioni[2].rank,6,MPI_COMM_WORLD);
SEND(s10_1,32,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_1,32,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s20_1,4,MPI_INT,sezioni[6].rank,2,MPI_COMM_WORLD);
SEND(s21_1,32,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<12;i0++){
for (i1=0;i1<12;i1++){
fprintf(localfp,"%d\t",s11_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s10_1[i0+4][i1+1],s11_1[i0+0][i1+2],s01_1[i0+1][i1+3]);
	}
	for (i1 = 1 ; i1 <=9;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s11_1[i0+0][i1+2],s01_1[i0+1][i1+3]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s12_1[i0+2][i1-10],s01_1[i0+1][i1+3]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s12_1[i0+2][i1-10],s12_1[i0+1][i1-11]);
	}
}
for (i0 = 1 ; i0 <=9;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s10_1[i0+4][i1+1],s11_1[i0+0][i1+2],s11_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=9;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s11_1[i0+0][i1+2],s11_1[i0-1][i1+1]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s12_1[i0+2][i1-10],s11_1[i0-1][i1+1]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+2][i1-1],s12_1[i0+2][i1-10],s12_1[i0+1][i1-11]);
	}
}
for (i0 = 10 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=9;i1++){
		s11_0[i0][i1] = MACRO( s21_1[i0-10][i1+1],s11_1[i0+0][i1+2],s11_1[i0-1][i1+1]);
	}
	for (i1 = 10 ; i1 <=10;i1++){
		s11_0[i0][i1] = MACRO( s21_1[i0-10][i1+1],s12_1[i0+2][i1-10],s11_1[i0-1][i1+1]);
	}
	for (i1 = 11 ; i1 <=11;i1++){
		s11_0[i0][i1] = MACRO( s21_1[i0-10][i1+1],s12_1[i0+2][i1-10],s12_1[i0+1][i1-11]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<12;i0++){
for (i1=0;i1<12;i1++){
fprintf(localfp,"%d\t",s11_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
RECEIVE(o01,32,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o02,4,MPI_INT,sezioni[2].rank,2,MPI_COMM_WORLD,&status);
RECEIVE(o10,32,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,32,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o20,4,MPI_INT,sezioni[6].rank,6,MPI_COMM_WORLD,&status);
RECEIVE(o21,32,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s00_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s00_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s00_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s00_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s00_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],s01_1[i0-1][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s00_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s01_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=2;i1++){
		s01_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 3 ; i1 <=11;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 12 ; i1 <=13;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],s12_1[i0+0][i1-12],o01[i0+1][i1+1]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],o12[i0+0][i1-14],o01[i0+1][i1+1]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s01_0[i0][i1] = MACRO( s12_1[i0+2][i1-15],o12[i0+0][i1-14],o02[i0+1][i1-15]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=2;i1++){
		s01_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],s01_1[i0-1][i1+1]);
	}
	for (i1 = 3 ; i1 <=11;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],s01_1[i0+0][i1+2],s01_1[i0-1][i1+1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],s12_1[i0+0][i1-12],s01_1[i0-1][i1+1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],s12_1[i0+0][i1-12],s12_1[i0-1][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s01_0[i0][i1] = MACRO( s11_1[i0+0][i1-3],o12[i0+0][i1-14],s12_1[i0-1][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s01_0[i0][i1] = MACRO( s12_1[i0+2][i1-15],o12[i0+0][i1-14],o12[i0-1][i1-15]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s01_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s02_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s02_0[i0][i1] = MACRO( s11_1[i0+0][i1+11],o12[i0+0][i1+0],o01[i0+1][i1+15]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s02_0[i0][i1] = MACRO( s12_1[i0+2][i1-1],o12[i0+0][i1+0],o02[i0+1][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s02_0[i0][i1] = MACRO( s11_1[i0+0][i1+11],o12[i0+0][i1+0],s12_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s02_0[i0][i1] = MACRO( s12_1[i0+2][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s02_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s10_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],o01[i0+1][i1+1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o10[i0+2][i1+1],s01_1[i0+0][i1+2],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s01_1[i0+0][i1+2],s01_1[i0-1][i1+1]);
	}
}
for (i0 = 2 ; i0 <=2;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o10[i0+2][i1+1],s11_1[i0-2][i1+0],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s11_1[i0-2][i1+0],s01_1[i0-1][i1+1]);
	}
}
for (i0 = 3 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o10[i0+2][i1+1],s11_1[i0-2][i1+0],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( s10_1[i0+2][i1-1],s11_1[i0-2][i1+0],s11_1[i0-3][i1-1]);
	}
}
for (i0 = 12 ; i0 <=13;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o10[i0+2][i1+1],s11_1[i0-2][i1+0],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( s21_1[i0-12][i1-1],s11_1[i0-2][i1+0],s11_1[i0-3][i1-1]);
	}
}
for (i0 = 14 ; i0 <=14;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o20[i0-14][i1+1],s21_1[i0-14][i1+2],s10_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( o21[i0-14][i1-1],s21_1[i0-14][i1+2],s11_1[i0-3][i1-1]);
	}
}
for (i0 = 15 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( o20[i0-14][i1+1],s21_1[i0-14][i1+2],s21_1[i0-15][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s10_0[i0][i1] = MACRO( o21[i0-14][i1-1],s21_1[i0-14][i1+2],s21_1[i0-15][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s10_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s12_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( s11_1[i0+0][i1+11],o12[i0+0][i1+0],o01[i0+1][i1+15]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_0[i0][i1] = MACRO( s12_1[i0+2][i1-1],o12[i0+0][i1+0],o02[i0+1][i1-1]);
	}
}
for (i0 = 1 ; i0 <=11;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( s11_1[i0+0][i1+11],o12[i0+0][i1+0],s12_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_0[i0][i1] = MACRO( s12_1[i0+2][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 12 ; i0 <=13;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( s21_1[i0-12][i1+13],o12[i0+0][i1+0],s12_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_0[i0][i1] = MACRO( s22_1[i0-12][i1-1],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 14 ; i0 <=14;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],s12_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_0[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
for (i0 = 15 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],s22_1[i0-15][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s12_0[i0][i1] = MACRO( o21[i0-14][i1+13],o12[i0+0][i1+0],o12[i0-1][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<16;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s12_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s20_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s20_0[i0][i1] = MACRO( o20[i0+0][i1+1],s21_1[i0+0][i1+2],s10_1[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s20_0[i0][i1] = MACRO( o21[i0+0][i1-1],s21_1[i0+0][i1+2],s11_1[i0+11][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s20_0[i0][i1] = MACRO( o20[i0+0][i1+1],s21_1[i0+0][i1+2],s21_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s20_0[i0][i1] = MACRO( o21[i0+0][i1-1],s21_1[i0+0][i1+2],s21_1[i0-1][i1+1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 0]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s20_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s21_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_0[i0][i1] = MACRO( o20[i0+0][i1+1],s21_1[i0+0][i1+2],s10_1[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=11;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s21_1[i0+0][i1+2],s11_1[i0+11][i1-1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s22_1[i0+0][i1-12],s11_1[i0+11][i1-1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s22_1[i0+0][i1-12],s12_1[i0+13][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],s12_1[i0+13][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],o12[i0+13][i1-15]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_0[i0][i1] = MACRO( o20[i0+0][i1+1],s21_1[i0+0][i1+2],s21_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=11;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s21_1[i0+0][i1+2],s21_1[i0-1][i1+1]);
	}
	for (i1 = 12 ; i1 <=12;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s22_1[i0+0][i1-12],s21_1[i0-1][i1+1]);
	}
	for (i1 = 13 ; i1 <=13;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],s22_1[i0+0][i1-12],s22_1[i0-1][i1-13]);
	}
	for (i1 = 14 ; i1 <=14;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],s22_1[i0-1][i1-13]);
	}
	for (i1 = 15 ; i1 <=15;i1++){
		s21_0[i0][i1] = MACRO( o21[i0+0][i1-1],o12[i0+14][i1-14],o12[i0+13][i1-15]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<16;i1++){
fprintf(localfp,"%d\t",s21_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s22_1[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s22_0[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],s12_1[i0+13][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s22_0[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],o12[i0+13][i1-1]);
	}
}
for (i0 = 1 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s22_0[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],s22_1[i0-1][i1+1]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s22_0[i0][i1] = MACRO( o21[i0+0][i1+13],o12[i0+14][i1+0],o12[i0+13][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 2]\n");
for (i0=0;i0<2;i0++){
for (i1=0;i1<2;i1++){
fprintf(localfp,"%d\t",s22_0[i0][i1]);
fprintf(localfp,"");
}
fprintf(localfp,"\n");
}
#endif
}
STAMPA("calcolo terminato\n")
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+0][i1+0]=s00_0[i0][i1];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <16;i1++){
local[i0+0][i1+0]=s01_0[i0][i1];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+0][i1+14]=s02_0[i0][i1];
}
}
for (i0 = 0 ; i0 <16;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+0][i1+0]=s10_0[i0][i1];
}
}
for (i0 = 0 ; i0 <12;i0++){
for (i1 = 0 ; i1 <12;i1++){
local[i0+2][i1+2]=s11_0[i0][i1];
}
}
for (i0 = 0 ; i0 <16;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+0][i1+14]=s12_0[i0][i1];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+14][i1+0]=s20_0[i0][i1];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <16;i1++){
local[i0+14][i1+0]=s21_0[i0][i1];
}
}
for (i0 = 0 ; i0 <2;i0++){
for (i1 = 0 ; i1 <2;i1++){
local[i0+14][i1+14]=s22_0[i0][i1];
}
}
        STAMPA("condensa terminata\n")

#if DEBUG
	 //printSections(localfp,sezioni);
#endif

	/* CONDENSA */
	//condensa(sezioni,local);

	/* GATHER DEI DATI */
	if (my_rank == COLLETTORE) {

		gather(local, matrix);

                /* stampa della matrice finale */
		writeMatrix(OUTPUT_MATRIX, matrix);

	} else {

		MPI_Send(local, localsize, MPI_INT, COLLETTORE, TAG,
				 MPI_COMM_WORLD);
	}
	MPI_Finalize();
}