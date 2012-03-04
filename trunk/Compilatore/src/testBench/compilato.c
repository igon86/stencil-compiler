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
	int i2;

	int local[20][20][20];

	int s011_0[2][24][24];
	int s011_1[2][24][24];
	int o011[2][24][24];
	sezioni[4].buffer = (int*) s011_0;
	int s101_0[20][2][24];
	int s101_1[20][2][24];
	int o101[20][2][24];
	sezioni[10].buffer = (int*) s101_0;
	int s110_0[20][20][2];
	int s110_1[20][20][2];
	int o110[20][20][2];
	sezioni[12].buffer = (int*) s110_0;
	int s111_0[16][16][16];
	int s111_1[16][16][16];
	int o111[16][16][16];
	sezioni[13].buffer = (int*) s111_0;
	int s112_0[20][20][2];
	int s112_1[20][20][2];
	int o112[20][20][2];
	sezioni[14].buffer = (int*) s112_0;
	int s121_0[20][2][24];
	int s121_1[20][2][24];
	int o121[20][2][24];
	sezioni[16].buffer = (int*) s121_0;
	int s211_0[2][24][24];
	int s211_1[2][24][24];
	int o211[2][24][24];
	sezioni[22].buffer = (int*) s211_0;
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
for (i0 = 0 ; i0 <=2;i0++){
for (i1 = 2 ; i1 <=20;i1++){
for (i2 = 2 ; i2 <=20;i2++){
s011_0[i0][i1][i2]= local[i0+0][i1-2][i2-2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=2;i1++){
for (i2 = 2 ; i2 <=20;i2++){
s101_0[i0][i1][i2]= local[i0+0][i1+0][i2-2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=20;i1++){
for (i2 = 0 ; i2 <=2;i2++){
s110_0[i0][i1][i2]= local[i0+0][i1+0][i2+0];
}
}
}
for (i0 = 0 ; i0 <=16;i0++){
for (i1 = 0 ; i1 <=16;i1++){
for (i2 = 0 ; i2 <=16;i2++){
s111_0[i0][i1][i2]= local[i0+0][i1+0][i2+0];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=20;i1++){
for (i2 = 0 ; i2 <=2;i2++){
s112_0[i0][i1][i2]= local[i0+0][i1+0][i2+18];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=2;i1++){
for (i2 = 2 ; i2 <=20;i2++){
s121_0[i0][i1][i2]= local[i0+0][i1+18][i2-2];
}
}
}
for (i0 = 0 ; i0 <=2;i0++){
for (i1 = 2 ; i1 <=20;i1++){
for (i2 = 2 ; i2 <=20;i2++){
s211_0[i0][i1][i2]= local[i0+18][i1-2][i2-2];
}
}
}
for ( i = 0 ; i < 1;i++){
SEND(s101_0,960,MPI_INT,sezioni[10].rank,16,MPI_COMM_WORLD);
SEND(s110_0,800,MPI_INT,sezioni[12].rank,14,MPI_COMM_WORLD);
for (i0 = 0 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=13;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_1[i0][i1][i2] = MACRO( s111_0[i0+0][i1+2][i2+0],s111_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_1[i0][i1][i2] = MACRO( s111_0[i0+0][i1+2][i2+0],s112_0[i0+2][i1+4][i2-15]);
		}
	}
	for (i1 = 14 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_1[i0][i1][i2] = MACRO( s121_0[i0+2][i1-14][i2+4],s121_0[i0+2][i1-14][i2+14]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_1[i0][i1][i2] = MACRO( s121_0[i0+2][i1-14][i2+4],s112_0[i0+2][i1+4][i2-15]);
		}
	}
}
RECEIVE(o112,800,MPI_INT,sezioni[14].rank,14,MPI_COMM_WORLD,&status);
RECEIVE(o121,960,MPI_INT,sezioni[16].rank,16,MPI_COMM_WORLD,&status);
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 2 ; i1 <=17;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s011_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+0][i2-2],s110_0[i0+0][i1+0][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s011_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+0][i2-2],s011_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s011_1[i0][i1][i2] = MACRO( s011_0[i0+0][i1+2][i2+0],s011_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s011_1[i0][i1][i2] = MACRO( s011_0[i0+0][i1+2][i2+0],s112_0[i0+0][i1+0][i2-19]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s011_1[i0][i1][i2] = MACRO( s121_0[i0+0][i1-18][i2+0],s121_0[i0+0][i1-18][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s011_1[i0][i1][i2] = MACRO( s121_0[i0+0][i1-18][i2+0],s112_0[i0+0][i1+0][i2-19]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s101_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2-2],s110_0[i0+0][i1+2][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s101_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2-2],s011_0[i0+0][i1+4][i2+1]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s101_1[i0][i1][i2] = MACRO( s011_0[i0+0][i1+4][i2+0],s011_0[i0+0][i1+4][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_1[i0][i1][i2] = MACRO( s011_0[i0+0][i1+4][i2+0],s112_0[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 2 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s101_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2-2],s110_0[i0+0][i1+2][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s101_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2-2],s111_0[i0-2][i1+0][i2-3]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s101_1[i0][i1][i2] = MACRO( s111_0[i0-2][i1+0][i2-4],s111_0[i0-2][i1+0][i2-3]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_1[i0][i1][i2] = MACRO( s111_0[i0-2][i1+0][i2-4],s112_0[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 18 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s101_1[i0][i1][i2] = MACRO( s211_0[i0-18][i1+4][i2+0],s211_0[i0-18][i1+4][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_1[i0][i1][i2] = MACRO( s211_0[i0-18][i1+4][i2+0],s112_0[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s110_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2+0],s110_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2+0],s011_0[i0+0][i1+4][i2+3]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s121_0[i0+0][i1-16][i2+2],s121_0[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 2 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s110_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2+0],s110_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s110_0[i0+0][i1+2][i2+0],s111_0[i0-2][i1+0][i2-1]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s121_0[i0+0][i1-16][i2+2],s121_0[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 18 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s211_0[i0-18][i1+4][i2+2],s211_0[i0-18][i1+4][i2+3]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( s121_0[i0+0][i1-16][i2+2],s121_0[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_1[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 0 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=13;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_1[i0][i1][i2] = MACRO( s111_0[i0+0][i1+2][i2+0],s111_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_1[i0][i1][i2] = MACRO( s111_0[i0+0][i1+2][i2+0],s112_0[i0+2][i1+4][i2-15]);
		}
	}
	for (i1 = 14 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_1[i0][i1][i2] = MACRO( s121_0[i0+2][i1-14][i2+4],s121_0[i0+2][i1-14][i2+14]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_1[i0][i1][i2] = MACRO( s121_0[i0+2][i1-14][i2+4],s112_0[i0+2][i1+4][i2-15]);
		}
	}
}
for (i0 = 0 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s112_1[i0][i1][i2] = MACRO( s112_0[i0+0][i1+2][i2+0],s112_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s112_1[i0][i1][i2] = MACRO( s112_0[i0+0][i1+2][i2+0],o112[i0+0][i1+2][i2-1]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s112_1[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+20],o121[i0+0][i1-18][i2+21]);
		}
	}
}
for (i0 = 0 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=19;i2++){
			s121_1[i0][i1][i2] = MACRO( o121[i0+0][i1+0][i2+0],o121[i0+0][i1+0][i2+1]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 2 ; i1 <=17;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s211_1[i0][i1][i2] = MACRO( s211_0[i0+0][i1+2][i2+0],s211_0[i0+0][i1+2][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s211_1[i0][i1][i2] = MACRO( s211_0[i0+0][i1+2][i2+0],s112_0[i0+18][i1+0][i2-19]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s211_1[i0][i1][i2] = MACRO( s121_0[i0+18][i1-18][i2+0],s121_0[i0+18][i1-18][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s211_1[i0][i1][i2] = MACRO( s121_0[i0+18][i1-18][i2+0],s112_0[i0+18][i1+0][i2-19]);
		}
	}
}
SEND(s101_1,960,MPI_INT,sezioni[10].rank,16,MPI_COMM_WORLD);
SEND(s110_1,800,MPI_INT,sezioni[12].rank,14,MPI_COMM_WORLD);
for (i0 = 0 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=13;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_0[i0][i1][i2] = MACRO( s111_1[i0+0][i1+2][i2+0],s111_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_0[i0][i1][i2] = MACRO( s111_1[i0+0][i1+2][i2+0],s112_1[i0+2][i1+4][i2-15]);
		}
	}
	for (i1 = 14 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_0[i0][i1][i2] = MACRO( s121_1[i0+2][i1-14][i2+4],s121_1[i0+2][i1-14][i2+14]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_0[i0][i1][i2] = MACRO( s121_1[i0+2][i1-14][i2+4],s112_1[i0+2][i1+4][i2-15]);
		}
	}
}
RECEIVE(o112,800,MPI_INT,sezioni[14].rank,14,MPI_COMM_WORLD,&status);
RECEIVE(o121,960,MPI_INT,sezioni[16].rank,16,MPI_COMM_WORLD,&status);
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 2 ; i1 <=17;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s011_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+0][i2-2],s110_1[i0+0][i1+0][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s011_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+0][i2-2],s011_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s011_0[i0][i1][i2] = MACRO( s011_1[i0+0][i1+2][i2+0],s011_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s011_0[i0][i1][i2] = MACRO( s011_1[i0+0][i1+2][i2+0],s112_1[i0+0][i1+0][i2-19]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s011_0[i0][i1][i2] = MACRO( s121_1[i0+0][i1-18][i2+0],s121_1[i0+0][i1-18][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s011_0[i0][i1][i2] = MACRO( s121_1[i0+0][i1-18][i2+0],s112_1[i0+0][i1+0][i2-19]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s101_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2-2],s110_1[i0+0][i1+2][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s101_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2-2],s011_1[i0+0][i1+4][i2+1]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s101_0[i0][i1][i2] = MACRO( s011_1[i0+0][i1+4][i2+0],s011_1[i0+0][i1+4][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_0[i0][i1][i2] = MACRO( s011_1[i0+0][i1+4][i2+0],s112_1[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 2 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=2;i2++){
			s101_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2-2],s110_1[i0+0][i1+2][i2-1]);
		}
		for (i2 = 3 ; i2 <=3;i2++){
			s101_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2-2],s111_1[i0-2][i1+0][i2-3]);
		}
		for (i2 = 4 ; i2 <=18;i2++){
			s101_0[i0][i1][i2] = MACRO( s111_1[i0-2][i1+0][i2-4],s111_1[i0-2][i1+0][i2-3]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_0[i0][i1][i2] = MACRO( s111_1[i0-2][i1+0][i2-4],s112_1[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 18 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s101_0[i0][i1][i2] = MACRO( s211_1[i0-18][i1+4][i2+0],s211_1[i0-18][i1+4][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s101_0[i0][i1][i2] = MACRO( s211_1[i0-18][i1+4][i2+0],s112_1[i0+0][i1+2][i2-19]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s110_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2+0],s110_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2+0],s011_1[i0+0][i1+4][i2+3]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s121_1[i0+0][i1-16][i2+2],s121_1[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 2 ; i0 <=17;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s110_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2+0],s110_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s110_1[i0+0][i1+2][i2+0],s111_1[i0-2][i1+0][i2-1]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s121_1[i0+0][i1-16][i2+2],s121_1[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 18 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s211_1[i0-18][i1+4][i2+2],s211_1[i0-18][i1+4][i2+3]);
		}
	}
	for (i1 = 16 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( s121_1[i0+0][i1-16][i2+2],s121_1[i0+0][i1-16][i2+3]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s110_0[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+2],o121[i0+0][i1-18][i2+3]);
		}
	}
}
for (i0 = 0 ; i0 <=15;i0++){
	for (i1 = 0 ; i1 <=13;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_0[i0][i1][i2] = MACRO( s111_1[i0+0][i1+2][i2+0],s111_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_0[i0][i1][i2] = MACRO( s111_1[i0+0][i1+2][i2+0],s112_1[i0+2][i1+4][i2-15]);
		}
	}
	for (i1 = 14 ; i1 <=15;i1++){
		for (i2 = 0 ; i2 <=14;i2++){
			s111_0[i0][i1][i2] = MACRO( s121_1[i0+2][i1-14][i2+4],s121_1[i0+2][i1-14][i2+14]);
		}
		for (i2 = 15 ; i2 <=15;i2++){
			s111_0[i0][i1][i2] = MACRO( s121_1[i0+2][i1-14][i2+4],s112_1[i0+2][i1+4][i2-15]);
		}
	}
}
for (i0 = 0 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=17;i1++){
		for (i2 = 0 ; i2 <=0;i2++){
			s112_0[i0][i1][i2] = MACRO( s112_1[i0+0][i1+2][i2+0],s112_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 1 ; i2 <=1;i2++){
			s112_0[i0][i1][i2] = MACRO( s112_1[i0+0][i1+2][i2+0],o112[i0+0][i1+2][i2-1]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 0 ; i2 <=1;i2++){
			s112_0[i0][i1][i2] = MACRO( o121[i0+0][i1-18][i2+20],o121[i0+0][i1-18][i2+21]);
		}
	}
}
for (i0 = 0 ; i0 <=19;i0++){
	for (i1 = 0 ; i1 <=1;i1++){
		for (i2 = 2 ; i2 <=19;i2++){
			s121_0[i0][i1][i2] = MACRO( o121[i0+0][i1+0][i2+0],o121[i0+0][i1+0][i2+1]);
		}
	}
}
for (i0 = 0 ; i0 <=1;i0++){
	for (i1 = 2 ; i1 <=17;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s211_0[i0][i1][i2] = MACRO( s211_1[i0+0][i1+2][i2+0],s211_1[i0+0][i1+2][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s211_0[i0][i1][i2] = MACRO( s211_1[i0+0][i1+2][i2+0],s112_1[i0+18][i1+0][i2-19]);
		}
	}
	for (i1 = 18 ; i1 <=19;i1++){
		for (i2 = 2 ; i2 <=18;i2++){
			s211_0[i0][i1][i2] = MACRO( s121_1[i0+18][i1-18][i2+0],s121_1[i0+18][i1-18][i2+1]);
		}
		for (i2 = 19 ; i2 <=19;i2++){
			s211_0[i0][i1][i2] = MACRO( s121_1[i0+18][i1-18][i2+0],s112_1[i0+18][i1+0][i2-19]);
		}
	}
}
}
STAMPA("calcolo terminato\n")
for (i0 = 0 ; i0 <=2;i0++){
for (i1 = 2 ; i1 <=20;i1++){
for (i2 = 2 ; i2 <=20;i2++){
local[i0+0][i1-2][i2-2]=s011_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=2;i1++){
for (i2 = 2 ; i2 <=20;i2++){
local[i0+0][i1+0][i2-2]=s101_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=20;i1++){
for (i2 = 0 ; i2 <=2;i2++){
local[i0+0][i1+0][i2+0]=s110_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=16;i0++){
for (i1 = 0 ; i1 <=16;i1++){
for (i2 = 0 ; i2 <=16;i2++){
local[i0+0][i1+0][i2+0]=s111_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=20;i1++){
for (i2 = 0 ; i2 <=2;i2++){
local[i0+0][i1+0][i2+18]=s112_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=20;i0++){
for (i1 = 0 ; i1 <=2;i1++){
for (i2 = 2 ; i2 <=20;i2++){
local[i0+0][i1+18][i2-2]=s121_0[i0][i1][i2];
}
}
}
for (i0 = 0 ; i0 <=2;i0++){
for (i1 = 2 ; i1 <=20;i1++){
for (i2 = 2 ; i2 <=20;i2++){
local[i0+18][i1-2][i2-2]=s211_0[i0][i1][i2];
}
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