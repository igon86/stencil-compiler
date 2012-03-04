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

	int local[20][20];

	int s01_0[1][22];
	int s01_1[1][22];
	int o01[1][22];
	sezioni[1].buffer = (int*) s01_0;
	int s10_0[20][1];
	int s10_1[20][1];
	int o10[20][1];
	sezioni[3].buffer = (int*) s10_0;
	int s11_0[18][18];
	int s11_1[18][18];
	int o11[18][18];
	sezioni[4].buffer = (int*) s11_0;
	int s12_0[20][1];
	int s12_1[20][1];
	int o12[20][1];
	sezioni[5].buffer = (int*) s12_0;
	int s21_0[1][22];
	int s21_1[1][22];
	int o21[1][22];
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
for (i0 = 0 ; i0 <=1;i0++){
for (i1 = 1 ; i1 <=20;i1++){
s01_0[i0][i1]= local[i0+0][i1-1];
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=1;i1++){
s10_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <=18;i0++){
for (i1 = 0 ; i1 <=18;i1++){
s11_0[i0][i1]= local[i0+0][i1+0];
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=1;i1++){
s12_0[i0][i1]= local[i0+0][i1+19];
}
}
for (i0 = 0 ; i0 <=1;i0++){
for (i1 = 1 ; i1 <=20;i1++){
s21_0[i0][i1]= local[i0+19][i1-1];
}
}
for ( i = 0 ; i < 1;i++){
SEND(s01_0,22,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s10_0,20,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_0,20,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s21_0,22,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=16;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 17 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
RECEIVE(o01,22,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o10,20,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,20,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o21,22,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s10_0[i0+1][i1+0],o01[i0+0][i1+0],o10[i0+0][i1+0]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s11_0[i0+0][i1-1],o01[i0+0][i1+0],s10_0[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=17;i1++){
		s01_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s11_0[i0+0][i1-1],o01[i0+0][i1+0],s01_0[i0+0][i1-1]);
	}
	for (i1 = 18 ; i1 <=18;i1++){
		s01_1[i0][i1] = MACRO( s12_0[i0+0][i1-18],s11_0[i0+0][i1-1],o01[i0+0][i1+0],s01_0[i0+0][i1-1]);
	}
	for (i1 = 19 ; i1 <=19;i1++){
		s01_1[i0][i1] = MACRO( o12[i0+0][i1-19],s12_0[i0+1][i1-19],o01[i0+0][i1+0],s01_0[i0+0][i1-1]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s01_0[i0+0][i1+1],s10_0[i0+1][i1+0],o01[i0+0][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 1 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s11_0[i0-1][i1+0],s10_0[i0+1][i1+0],s10_0[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 18 ; i0 <=18;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s11_0[i0-1][i1+0],s21_0[i0-18][i1+0],s10_0[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 19 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_1[i0][i1] = MACRO( s21_0[i0-19][i1+1],o21[i0-19][i1+0],s10_0[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s11_0[i0+1][i1+0],s01_0[i0+0][i1+1],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=16;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s11_0[i0+1][i1+0],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 17 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s10_0[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_1[i0][i1] = MACRO( s11_0[i0+0][i1+1],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_1[i0][i1] = MACRO( s12_0[i0+1][i1-17],s21_0[i0-17][i1+1],s11_0[i0-1][i1+0],s11_0[i0+0][i1-1]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],s12_0[i0+1][i1+0],o01[i0+0][i1+19],s01_0[i0+0][i1+18]);
	}
}
for (i0 = 1 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],s12_0[i0+1][i1+0],s12_0[i0-1][i1+0],s11_0[i0-1][i1+17]);
	}
}
for (i0 = 18 ; i0 <=18;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],s21_0[i0-18][i1+19],s12_0[i0-1][i1+0],s11_0[i0-1][i1+17]);
	}
}
for (i0 = 19 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_1[i0][i1] = MACRO( o12[i0+0][i1+0],o21[i0-19][i1+19],s12_0[i0-1][i1+0],s21_0[i0-19][i1+18]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_1[i0][i1] = MACRO( s21_0[i0+0][i1+1],o21[i0+0][i1+0],s10_0[i0+18][i1+0],o10[i0+19][i1+0]);
	}
	for (i1 = 1 ; i1 <=18;i1++){
		s21_1[i0][i1] = MACRO( s21_0[i0+0][i1+1],o21[i0+0][i1+0],s11_0[i0+17][i1-1],s21_0[i0+0][i1-1]);
	}
	for (i1 = 19 ; i1 <=19;i1++){
		s21_1[i0][i1] = MACRO( o12[i0+19][i1-19],o21[i0+0][i1+0],s12_0[i0+18][i1-19],s21_0[i0+0][i1-1]);
	}
}
SEND(s01_1,22,MPI_INT,sezioni[1].rank,7,MPI_COMM_WORLD);
SEND(s10_1,20,MPI_INT,sezioni[3].rank,5,MPI_COMM_WORLD);
SEND(s12_1,20,MPI_INT,sezioni[5].rank,3,MPI_COMM_WORLD);
SEND(s21_1,22,MPI_INT,sezioni[7].rank,1,MPI_COMM_WORLD);
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=16;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 17 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
RECEIVE(o01,22,MPI_INT,sezioni[1].rank,1,MPI_COMM_WORLD,&status);
RECEIVE(o10,20,MPI_INT,sezioni[3].rank,3,MPI_COMM_WORLD,&status);
RECEIVE(o12,20,MPI_INT,sezioni[5].rank,5,MPI_COMM_WORLD,&status);
RECEIVE(o21,22,MPI_INT,sezioni[7].rank,7,MPI_COMM_WORLD,&status);
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s10_1[i0+1][i1+0],o01[i0+0][i1+0],o10[i0+0][i1+0]);
	}
	for (i1 = 1 ; i1 <=1;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s11_1[i0+0][i1-1],o01[i0+0][i1+0],s10_1[i0+0][i1-1]);
	}
	for (i1 = 2 ; i1 <=17;i1++){
		s01_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s11_1[i0+0][i1-1],o01[i0+0][i1+0],s01_1[i0+0][i1-1]);
	}
	for (i1 = 18 ; i1 <=18;i1++){
		s01_0[i0][i1] = MACRO( s12_1[i0+0][i1-18],s11_1[i0+0][i1-1],o01[i0+0][i1+0],s01_1[i0+0][i1-1]);
	}
	for (i1 = 19 ; i1 <=19;i1++){
		s01_0[i0][i1] = MACRO( o12[i0+0][i1-19],s12_1[i0+1][i1-19],o01[i0+0][i1+0],s01_1[i0+0][i1-1]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s01_1[i0+0][i1+1],s10_1[i0+1][i1+0],o01[i0+0][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 1 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s11_1[i0-1][i1+0],s10_1[i0+1][i1+0],s10_1[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 18 ; i0 <=18;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s11_1[i0-1][i1+0],s21_1[i0-18][i1+0],s10_1[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 19 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s10_0[i0][i1] = MACRO( s21_1[i0-19][i1+1],o21[i0-19][i1+0],s10_1[i0-1][i1+0],o10[i0+0][i1+0]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s11_1[i0+1][i1+0],s01_1[i0+0][i1+1],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 1 ; i0 <=16;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s11_1[i0+1][i1+0],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 17 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s10_1[i0+1][i1+0]);
	}
	for (i1 = 1 ; i1 <=16;i1++){
		s11_0[i0][i1] = MACRO( s11_1[i0+0][i1+1],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
	for (i1 = 17 ; i1 <=17;i1++){
		s11_0[i0][i1] = MACRO( s12_1[i0+1][i1-17],s21_1[i0-17][i1+1],s11_1[i0-1][i1+0],s11_1[i0+0][i1-1]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],s12_1[i0+1][i1+0],o01[i0+0][i1+19],s01_1[i0+0][i1+18]);
	}
}
for (i0 = 1 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],s12_1[i0+1][i1+0],s12_1[i0-1][i1+0],s11_1[i0-1][i1+17]);
	}
}
for (i0 = 18 ; i0 <=18;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],s21_1[i0-18][i1+19],s12_1[i0-1][i1+0],s11_1[i0-1][i1+17]);
	}
}
for (i0 = 19 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s12_0[i0][i1] = MACRO( o12[i0+0][i1+0],o21[i0-19][i1+19],s12_1[i0-1][i1+0],s21_1[i0-19][i1+18]);
	}
}
for (i0 = 0 ; i0 <=0;i0++){
	for (i1 = 0 ; i1 <=0;i1++){
		s21_0[i0][i1] = MACRO( s21_1[i0+0][i1+1],o21[i0+0][i1+0],s10_1[i0+18][i1+0],o10[i0+19][i1+0]);
	}
	for (i1 = 1 ; i1 <=18;i1++){
		s21_0[i0][i1] = MACRO( s21_1[i0+0][i1+1],o21[i0+0][i1+0],s11_1[i0+17][i1-1],s21_1[i0+0][i1-1]);
	}
	for (i1 = 19 ; i1 <=19;i1++){
		s21_0[i0][i1] = MACRO( o12[i0+19][i1-19],o21[i0+0][i1+0],s12_1[i0+18][i1-19],s21_1[i0+0][i1-1]);
	}
}
}
STAMPA("calcolo terminato\n")
for (i0 = 0 ; i0 <=1;i0++){
for (i1 = 1 ; i1 <=20;i1++){
local[i0+0][i1-1]=s01_0[i0][i1];
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=1;i1++){
local[i0+0][i1+0]=s10_0[i0][i1];
}
}
for (i0 = 0 ; i0 <=18;i0++){
for (i1 = 0 ; i1 <=18;i1++){
local[i0+0][i1+0]=s11_0[i0][i1];
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=1;i1++){
local[i0+0][i1+19]=s12_0[i0][i1];
}
}
for (i0 = 0 ; i0 <=1;i0++){
for (i1 = 1 ; i1 <=20;i1++){
local[i0+19][i1-1]=s21_0[i0][i1];
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