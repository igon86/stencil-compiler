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

	int local[8][8];

	int s01_0[1][10];
	int s01_1[1][10];
	int o01[1][10];
	sezioni[1].buffer = (int*) s01_0;
	int s10_0[8][1];
	int s10_1[8][1];
	int o10[8][1];
	sezioni[3].buffer = (int*) s10_0;
	int s11_0[6][6];
	int s11_1[6][6];
	int o11[6][6];
	sezioni[4].buffer = (int*) s11_0;
	int s12_0[8][1];
	int s12_1[8][1];
	int o12[8][1];
	sezioni[5].buffer = (int*) s12_0;
	int s21_0[1][10];
	int s21_1[1][10];
	int o21[1][10];
	sezioni[7].buffer = (int*) s21_0;
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

	/* RIEMPIMENTO DELLE SEZIONI */
	//fill_sections(sezioni,local);

#if DEBUG
        //printSections(localfp,sezioni);
#endif

	/*CODICE GENERATO DAL COMPILATORE */
for (i0 = 0 ; i0 <1;i0++){
for (i1 = 1 ; i1 <8;i1++){
s01_0[i0][i1]= local[i0+0][i1-1];
}
}
for (i0 = 0 ; i0 <8;i0++){
for (i1 = 0 ; i1 <1;i1++){
s10_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <6;i0++){
for (i1 = 0 ; i1 <6;i1++){
s11_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <8;i0++){
for (i1 = 0 ; i1 <1;i1++){
s12_0[i0][i1]= local[i0+0][i1+7];
}
}
for (i0 = 0 ; i0 <1;i0++){
for (i1 = 1 ; i1 <8;i1++){
s21_0[i0][i1]= local[i0+7][i1-1];
}
}
for ( i = 0 ; i < 1;i++){
SEND(s01_0,10,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s10_0,8,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_0,8,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s21_0,10,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<6;i0++){
for (i1=0;i1<6;i1++){
fprintf(localfp,"%d\t",s11_0[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+2],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+2],s11_0[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-5],s11_0[i0+1][i1+0],s01_0[i0+0][i1+2],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=4;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-5],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 5 ; i0 <=5;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-5][i1+2],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-5][i1+2],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-5],s21_0[i0-5][i1+2],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<6;i0++){
for (i1=0;i1<6;i1++){
fprintf(localfp,"%d\t",s11_1[i0][i1]);
}
}
#endif
RECEIVE(o01,10,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o10,8,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,8,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o21,10,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s01_0[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 1 ; i1 <=1;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s10_0[i0+1][i1-1],o01[i0+0][i1+0],o10[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=2;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s11_0[i0+0][i1-2],o01[i0+0][i1+0],s10_0[i0+0][i1-2]);
	}
	for (i1 = 3 ; i1 <=6;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s11_0[i0+0][i1-2],o01[i0+0][i1+0],s01_0[i0+0][i1-1]);
	}
	for (i1 = 7 ; i1 <=7;i1++){
		s01_1[i0][i1] = MACRO( s12_0[i0+0][i1-7],s11_0[i0+0][i1-2],o01[i0+0][i1+0],s01_0[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s01_1[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s10_0[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s01_0[i0+0][i1+2],s10_0[i0+1][i1+0],o01[i0+0][i1+1],o10[i0+0][i1+0]);
	}
}
for (i0 = 1 ; i0 <=5;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s11_0[i0-1][i1+0],s10_0[i0+1][i1+0],s10_0[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 6 ; i0 <=6;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s11_0[i0-1][i1+0],s21_0[i0-6][i1+1],s10_0[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 7 ; i0 <=7;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s21_0[i0-7][i1+2],o21[i0-7][i1+1],s10_0[i0-1][i1+0],s21_0[i0-7][i1+0]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s10_1[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s12_0[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],s12_0[i0+1][i1+0],o01[i0+0][i1+8],s01_0[i0+0][i1+7]);
	}
}
for (i0 = 1 ; i0 <=6;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],s12_0[i0+1][i1+0],s12_0[i0-1][i1+0],s11_0[i0-1][i1+5]);
	}
}
for (i0 = 7 ; i0 <=7;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],o21[i0-7][i1+8],s12_0[i0-1][i1+0],s21_0[i0-7][i1+7]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s12_1[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s21_0[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 1 ; i1 <=1;i1++){
		s21_1[i0][i1] = MACRO( s21_0[i0+0][i1+1],o21[i0+0][i1+0],s10_0[i0+6][i1-1],s21_0[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=6;i1++){
		s21_1[i0][i1] = MACRO( s21_0[i0+0][i1+1],o21[i0+0][i1+0],s11_0[i0+5][i1-2],s21_0[i0+0][i1-1]);
	}
	for (i1 = 7 ; i1 <=7;i1++){
		s21_1[i0][i1] = MACRO( s12_0[i0+7][i1-7],o21[i0+0][i1+0],s11_0[i0+5][i1-2],s21_0[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s21_1[i0][i1]);
}
}
#endif
SEND(s01_1,10,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s10_1,8,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_1,8,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s21_1,10,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<6;i0++){
for (i1=0;i1<6;i1++){
fprintf(localfp,"%d\t",s11_1[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+2],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+2],s11_1[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-5],s11_1[i0+1][i1+0],s01_1[i0+0][i1+2],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=4;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-5],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 5 ; i0 <=5;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-5][i1+2],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=4;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-5][i1+2],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 5 ; i1 <=5;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-5],s21_1[i0-5][i1+2],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 1]\n");
for (i0=0;i0<6;i0++){
for (i1=0;i1<6;i1++){
fprintf(localfp,"%d\t",s11_0[i0][i1]);
}
}
#endif
RECEIVE(o01,10,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o10,8,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,8,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o21,10,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s01_1[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 1 ; i1 <=1;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s10_1[i0+1][i1-1],o01[i0+0][i1+0],o10[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=2;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s11_1[i0+0][i1-2],o01[i0+0][i1+0],s10_1[i0+0][i1-2]);
	}
	for (i1 = 3 ; i1 <=6;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s11_1[i0+0][i1-2],o01[i0+0][i1+0],s01_1[i0+0][i1-1]);
	}
	for (i1 = 7 ; i1 <=7;i1++){
		s01_0[i0][i1] = MACRO( s12_1[i0+0][i1-7],s11_1[i0+0][i1-2],o01[i0+0][i1+0],s01_1[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [0, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s01_0[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s10_1[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s01_1[i0+0][i1+2],s10_1[i0+1][i1+0],o01[i0+0][i1+1],o10[i0+0][i1+0]);
	}
}
for (i0 = 1 ; i0 <=5;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s11_1[i0-1][i1+0],s10_1[i0+1][i1+0],s10_1[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 6 ; i0 <=6;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s11_1[i0-1][i1+0],s21_1[i0-6][i1+1],s10_1[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 7 ; i0 <=7;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s21_1[i0-7][i1+2],o21[i0-7][i1+1],s10_1[i0-1][i1+0],s21_1[i0-7][i1+0]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 0]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s10_0[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s12_1[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],s12_1[i0+1][i1+0],o01[i0+0][i1+8],s01_1[i0+0][i1+7]);
	}
}
for (i0 = 1 ; i0 <=6;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],s12_1[i0+1][i1+0],s12_1[i0-1][i1+0],s11_1[i0-1][i1+5]);
	}
}
for (i0 = 7 ; i0 <=7;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],o21[i0-7][i1+8],s12_1[i0-1][i1+0],s21_1[i0-7][i1+7]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [1, 2]\n");
for (i0=0;i0<8;i0++){
for (i1=0;i1<1;i1++){
fprintf(localfp,"%d\t",s12_0[i0][i1]);
}
}
#endif
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s21_1[i0][i1]);
}
}
#endif
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 1 ; i1 <=1;i1++){
		s21_0[i0][i1] = MACRO( s21_1[i0+0][i1+1],o21[i0+0][i1+0],s10_1[i0+6][i1-1],s21_1[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=6;i1++){
		s21_0[i0][i1] = MACRO( s21_1[i0+0][i1+1],o21[i0+0][i1+0],s11_1[i0+5][i1-2],s21_1[i0+0][i1-1]);
	}
	for (i1 = 7 ; i1 <=7;i1++){
		s21_0[i0][i1] = MACRO( s12_1[i0+7][i1-7],o21[i0+0][i1+0],s11_1[i0+5][i1-2],s21_1[i0+0][i1-1]);
	}
}
#if DEBUG
fprintf(localfp,"\nSEZIONE [2, 1]\n");
for (i0=0;i0<1;i0++){
for (i1=0;i1<10;i1++){
fprintf(localfp,"%d\t",s21_0[i0][i1]);
}
}
#endif
}
STAMPA("calcolo terminato\n")
for (i0 = 0 ; i0 <1;i0++){
for (i1 = 1 ; i1 <8;i1++){
local[i0+0][i1-1]=s01_0[i0][i1];
}
}
for (i0 = 0 ; i0 <8;i0++){
for (i1 = 0 ; i1 <1;i1++){
local[i0+0][i1+0]=s10_0[i0][i1];
}
}
for (i0 = 0 ; i0 <6;i0++){
for (i1 = 0 ; i1 <6;i1++){
local[i0+0][i1+0]=s11_0[i0][i1];
}
}
for (i0 = 0 ; i0 <8;i0++){
for (i1 = 0 ; i1 <1;i1++){
local[i0+0][i1+7]=s12_0[i0][i1];
}
}
for (i0 = 0 ; i0 <1;i0++){
for (i1 = 1 ; i1 <8;i1++){
local[i0+7][i1-1]=s21_0[i0][i1];
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