#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Hachage.h"


//Allocation des structures 

CellPoint* alloue_CellPoint(double x, double y) {

    CellPoint *point = (CellPoint *)malloc(sizeof(CellPoint));
    point->x = x ;
    point->y = y ;
    point->suiv = NULL;

    return point;
} 


CellChaine* alloue_CellChaine(CellPoint* points, int num) {

    CellChaine *c = (CellChaine *)malloc(sizeof(CellChaine));
    c->points = points;
    c->numero = num;
    c->suiv = NULL;

    return c;
}


Chaines* alloue_Chaines(int gamma, int nbChaines, CellChaine* chaines) {

        Chaines* c = (Chaines *)malloc(sizeof(Chaines));
        c->gamma = gamma;
        c->nbChaines = nbChaines;
        c->chaines = chaines;

        return c;
}


TableHachage* creerTableH(int taille) {

	TableHachage* H = (TableHachage*)malloc(taille*sizeof(TableHachage));         
  	H->taille = taille;
    	H->nE = 0;
    
	for (int i = 0; i < H->taille; i++) {
		H->N[i] = (CellNoeud*)malloc(sizeof(CellNoeud));
	}

	return H;
}


//Affichage des structures

void afficherTH(TableHachage* H) {

	printf("nbEelements : %d \n taille : %d \n", H->nE, H->taille);

	for (int i = 0; i < H->taille; i++) {
		CellNoeud* courCN = H->N[i];
		printf("\n case : %d \t", i);
		while (courCN) {
			printf("%d : \t", courCN->nd->num);
			courCN = courCN->suiv; 
		}
	}
}


void afficherListe(CellNoeud* liste) {

	CellNoeud* copieL = liste;
	while (copieL) {
		printf("Noeud : %d, x : %f, y : %f \n", liste->nd->num, liste->nd->x, liste->nd->y);	
		copieL = copieL->suiv;
	}	
}


//Liberation des structures

void liberer_CellPoint(CellPoint* point) {

	if (point != NULL) {
        	free(point);
    	}
}


void liberer_CellChaine(CellChaine* c) {

	if (c != NULL) {

        	CellPoint *tmp ;
        	while (c->points != NULL) {
            		tmp = c->points;
            		c->points = c->points->suiv;
            		liberer_CellPoint(tmp);
        	}

        	liberer_CellChaine(c->suiv);
        	free (c);
    }
}


void liberer_Chaines(Chaines* c) {

	if (c != NULL) {
		liberer_CellChaine(c->chaines);
            	free(c);  
    }
}


void libererTableH(TableHachage* H) {
    
	for (int i = 0; i < H->taille; i++) {
		CellNoeud* copie = H->N[i];
		while (copie) {
			Noeud* tmp = copie->suiv->nd;
			free(copie);
			copie->nd = tmp;
		}
	}

	free(H);
}


//Insertion d'elements dans la liste (on inserera les éléments en début de liste car c'est plus pratique a réaliser)

CellPoint*  inserer_CellPoint(CellPoint* point, double x, double y) {

	CellPoint* new_p = alloue_CellPoint(x, y);

    new_p->suiv = point;
    point = new_p;
    
    return new_p;
}


CellChaine* inserer_CellChaine(CellChaine* c, CellPoint* points, int num) {

	CellChaine* new_c = alloue_CellChaine(points, num);

    	new_c->suiv=c;

    	return new_c;
    
}
