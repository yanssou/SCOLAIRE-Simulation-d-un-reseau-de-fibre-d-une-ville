#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"


/* EXERCICE 1 */

//1.1

CellPoint* lire_points(FILE* f, int nbP) {                      //on crée une fonction intermédiaire afin d'allèger et simplifier le code de lectureChaines
                                                                    //lire_points va permettre de lire le nombre de points présents sur une ligne
	CellPoint* c = NULL;
	double x, y;

	for(int i = 0; i < nbP; i++) {
        fscanf(f, " %lf %lf", &x, &y);

		c = inserer_CellPoint(c, x, y);
	}

	return c;
}


Chaines* lectureChaine(FILE* f) {

	char buffer[256];
	int nbChain;
	int gamma;
	int numChaine;
	int nbPoints;

	CellChaine* cellChain = NULL;
	Chaines* c = NULL;

	fgets(buffer, 256, f);
	if (sscanf(buffer, "NbChain: %d", &nbChain) != 1) {                     
		printf("Erreur lecture de la chaine \n");
		return NULL;
	}

	fgets(buffer, 256, f);
	if (sscanf(buffer, "Gamma: %d", &gamma) != 1) {                         
		printf("Erreur de lecture de gamma \n");
		return NULL;
	}
	
	int tmp = nbChain;

	while (fscanf(f, "%d %d", &numChaine, &nbPoints) != EOF){

		cellChain = inserer_CellChaine(cellChain, lire_points(f, nbPoints), numChaine);
		tmp--;
	}
	
	c = alloue_Chaines(gamma, nbChain, cellChain);

	return c;
}

//1.2


void ecrireChaines(Chaines *c, FILE *f){
    if(f==NULL){
        fprintf(stderr, "Erreur fichier");
        exit(-2);
    }

    int nb = c->nbChaines;
    int gamma = c->gamma;
    // écriture des deux informations nbChaine et gamme en en tête du fichier sur deux lignes
    fprintf(f, "NbChain : %d\n", nb);
    fprintf(f, "Gamma : %d\n", gamma);
    CellChaine *cc = c->chaines;

    while(cc){ // tant qu'il y a une chaine dans la liste de CellChaine parcourue
        int cpt = 0; //Pour trouver le nombre de points contenue dans la chaine courante
        fprintf(f, "%d ", cc->numero); // On inscrit le numéro de la chaine
        CellPoint *cp = cc->points;
        while(cp != NULL){ // tant qu'il y a un point dans la liste de CellPoint de la chaine courante
	    cpt++;
            cp = cp->suiv;
        }
        fprintf(f, "%d", cpt); // On inscrit le gamma de la chaine courante ( son nombre de points )
        cp = cc->points;
        while(cp && cpt != 1){ // on reparcourt la liste des points de la chaine courante jusqu'à l'avant dernier point
        fprintf(f, " %.2lf %.2lf", cp->x, cp->y); // on inscrit les differentes coordonnées des points parcourue par la chaine courante
        cpt--;
        cp = cp->suiv;
    }
    fprintf(f, " %.2lf %.2lf\n", cp->x, cp->y); // onscrit le dernier point
    cc = cc->suiv; // on passe à la chaine suivante
    }
}

//1.3

void afficheChainesSVG(Chaines *C, char* nomInstance) {

    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx, precy;
    SVGwriter svg;

    ccour = C->chaines;
    while (ccour != NULL) {
        pcour = ccour->points;
        while (pcour != NULL) {
            if (maxx < pcour->x) maxx = pcour->x;
            if (maxy < pcour->y) maxy = pcour->y;
            if (minx > pcour->x) minx = pcour->x;
            if (miny > pcour->y) miny = pcour->y;  
            pcour = pcour->suiv;
        }

    ccour = ccour->suiv;
    }

    SVGinit(&svg, nomInstance, 500, 500);

    ccour = C->chaines;
    while (ccour != NULL) {
        pcour = ccour->points;
        SVGlineRandColor(&svg);

        SVGpoint(&svg, 500*(pcour->x-minx)/(maxx-minx), 500*(pcour->y-miny)/(maxy-miny)); 
        precx = pcour->x;
        precy = pcour->y;  
        pcour = pcour->suiv;

        while (pcour != NULL) {
            SVGline(&svg, 500*(precx-minx)/(maxx-minx), 500*(precy-miny)/(maxy-miny), 500*(pcour->x-minx)/(maxx-minx), 500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg, 500*(pcour->x-minx)/(maxx-minx), 500*(pcour->y-miny)/(maxy-miny));
            precx = pcour->x;
            precy = pcour->y;    
            pcour = pcour->suiv;
        }

        ccour = ccour->suiv;
    }

    SVGfinalize(&svg);
}


//1.4

double longueurChaine(CellChaine* c) {

	double distance = 0.0;

	while (c) {
		while (c->points->suiv) {
			distance += sqrt( pow(((c->points->x)-(c->points->suiv->x)), 2) + pow(((c->points->y)-(c->points->suiv->y)), 2) );
			c->points = c->points->suiv;
		}	

		c=c->suiv;
	}

	return distance;

}


double longueurTotale(Chaines* c) {

	double distance = 0.0;

	while (c->chaines) {
    		distance += longueurChaine(c->chaines);
    		c->chaines = c->chaines->suiv;
  	}
    	
	return distance;
}


//1.5

int comptePointsTotal(Chaines* C) {

	int nbPoints = 0 ;

	if (C != NULL) {
		while (C->chaines) {
			while (C->chaines->points) {
				if (C->chaines->points) {
					nbPoints++;
				}

				C->chaines->points = C->chaines->points->suiv;
			}

			C->chaines=C->chaines->suiv;
		}
	}

	return nbPoints;
}
