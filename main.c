#include <stdlib.h>
#include <stdio.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include "SVGwriter.h"
#include <math.h>
#include <time.h>
#define PRINT(s) printf("%s\n", s);
#define ESPACE printf("-----------------------------\n");
#define NB_ESSAIS 10

double reconstitueR_Liste(Chaines* C, Reseau** R){
        clock_t temps_initial;
        clock_t temps_final;
        double temps_cpu;
        temps_initial = clock();
        *R = reconstitueReseauListe(C);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        return temps_cpu;
}

double reconstitueR_Hachage(Chaines* C, int M){
        clock_t temps_initial;
        clock_t temps_final;
        double temps_cpu;
        temps_initial = clock();
        Reseau *R = reconstitueReseauHachage(C,M);
        temps_final = clock();
        libererReseau(R);
        temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        return temps_cpu;
}

double reconstitueR_ArbreQuat(Chaines* C){
        clock_t temps_initial;
        clock_t temps_final;
        double temps_cpu;
        Reseau* R = creerReseau();
        temps_initial = clock();
        R = reconstitueReseauArbre(C);
        temps_final = clock();
      //  libererReseau(R);
        temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        return temps_cpu;
}


// Burma 



int main(){

    //EXERCICE 6

    srand(time(NULL));
    double temps_cpu1;
	double temps_cpu2;
	double temps_cpu3;

    //----------------------------------------------------------------Q 6.1----------------------------------------------------------------

	FILE *f1 = fopen("00014_burma.cha","r+");
	FILE *f2 = fopen("05000_USA-road-d-NY.cha","r+");
	FILE *f3 = fopen("07397_pla.cha","r+");
    if( f1 == NULL || f2 == NULL || f3 == NULL ){
        fprintf(stderr,"Erreur ouverture fichier 1.\n");
        exit(02);
    }

    Chaines* C1 = lectureChaine(f1);
	Chaines* C2 = lectureChaine(f2);
	Chaines* C3 = lectureChaine(f3);

	fclose(f1);
    fclose(f2);
	fclose(f3);

    int M;

    FILE* data1;
    FILE* data2;
    FILE* data3;
	
    

	/*-----------------LISTES--------------*/

    data1 = fopen("data_time_liste.txt","w+");

    Reseau* R1 = creerReseau();


    fprintf(data1, "-----------------BURMA--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu1 = reconstitueR_Liste(C1, &R1);
        fprintf(data1, "%d %f\n",i,temps_cpu1 );
    }

    fprintf(data1, "-----------------USA_ROAD--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu1 = reconstitueR_Liste(C2, &R1);
        fprintf(data1, "%d %f\n",i,temps_cpu1 );
    }

    fprintf(data1, "-----------------PLA--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu1 = reconstitueR_Liste(C3, &R1);
        fprintf(data1, "%d %f\n",i,temps_cpu1 );
    }

    fclose(data1);

    /*-----------------HACHAGE--------------*/

    data2 = fopen("data_time_hachage.txt", "w+");

    fprintf(data2, "-----------------BURMA--------------\n" );

    M = comptePointsTotal(C1);

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu2 = reconstitueR_Hachage(C1,M);
        fprintf(data2, "%d %f\n",i,temps_cpu2 );
    }

    fprintf(data2, "-----------------USA_ROAD--------------\n" );

    M = comptePointsTotal(C2);

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu2 = reconstitueR_Hachage(C2,M*9);
        fprintf(data2, "%d %f\n",i, temps_cpu2 );
    }

    fprintf(data2, "-----------------PLA--------------\n" );

    M = comptePointsTotal(C3);

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu2 = reconstitueR_Hachage(C3,M);
        fprintf(data2, "%d %f\n",i,temps_cpu2 );
    }

    fclose(data2);

    /*-----------------ARBRE_QUAT--------------*/

    data3 = fopen("data_time_arbre.txt", "w+");

    Reseau* R2 = creerReseau();

    fprintf(data3, "-----------------BURMA--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu3 = reconstitueR_ArbreQuat(C1);
        fprintf(data3, "%d %f\n",i,temps_cpu3 );
    }

    fprintf(data3, "-----------------USA_ROAD--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu3 = reconstitueR_ArbreQuat(C2);
        fprintf(data3, "%d %f\n",i,temps_cpu3 );
    }

    fprintf(data3, "-----------------PLA--------------\n" );

    for(int i = 0; i < NB_ESSAIS; i++){
        temps_cpu3 = reconstitueR_ArbreQuat(C3);
        fprintf(data3, "%d %.20f\n",i,temps_cpu3 );
    }


    fclose(data3);


        // ----------------------------------------------------------------Q 6.3----------------------------------------------------------------

/*
    Chaines *CH;
    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;
    int pas = 500;


    data1 = fopen("data_time_liste.txt","wb");
    FILE *data2_4 = fopen("data_time_hach_4.txt","wb");
    FILE *data2_2 = fopen("data_time_hach_2.txt","wb");
    data2 = fopen("data_time_hach.txt","wb");
    data3 = fopen("data_time_arbre.txt","wb");


    if( data1 == NULL || data2 == NULL || data3 == NULL ){
        fprintf(stderr,"Erreur ouverture fichier écriture 3.\n");
        exit(01);
    }

    int nb_p;

    for( int nb = 500; nb < 5001; nb += pas ){
        CH = generationAleatoire(nb, nbPointsChaine, xmax, ymax);
        nb_p = comptePointsTotal(CH);
        M = CH->nbChaines;

        temps_cpu3 = reconstitueR_ArbreQuat(CH);
        fprintf(data3,"%d %f\n", nb_p, temps_cpu3);

        temps_cpu1 = reconstitueR_Liste(CH, &R);
        fprintf(data1,"%d %f\n", nb_p, temps_cpu1);

        temps_cpu2 = reconstitueR_Hachage(CH, M/4);
        fprintf(data2_4,"%d %f\n", nb * nbPointsChaine, temps_cpu2);
        temps_cpu2 = reconstitueR_Hachage(CH, M/2);
        fprintf(data2_2,"%d %f\n", nb * nbPointsChaine, temps_cpu2);
        temps_cpu2 = reconstitueR_Hachage(CH, M);
        fprintf(data2,"%d %f\n", nb * nbPointsChaine, temps_cpu2);

        desallouerChaines(CH);
        desallouerReseau(R);
    }
    fclose(data1);
    fclose(data2);
    fclose(data3);
*/




    return 0;
}