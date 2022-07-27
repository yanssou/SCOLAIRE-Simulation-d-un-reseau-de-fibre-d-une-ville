#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"
#define PRINT(s) printf("%s \n", s);


//Création des structures du réseau

Reseau* creerReseau() {

	Reseau*r = (Reseau*)malloc(sizeof(Reseau));
	if (r == NULL) {
		printf("Erreur allocation Reseau \n");
		exit(1);
	}

	r->nbNoeuds = 0;
	r->gamma = 0;
	r->noeuds = NULL;
	r->commodites = NULL;

	return r;
}


Noeud* creerNoeud(int num, double x, double y) {

	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n == NULL) {
		printf("Erreur d'allocation Noeud \n");
		exit(1);
	}

	n->num = num;
	n->x = x;
	n->y = y;
	n->voisins = NULL;

	return n;
}


CellNoeud* creerCellNoeud(Noeud* n) {

	CellNoeud* cn = (CellNoeud*)malloc(sizeof(CellNoeud));

	if (cn == NULL) {
		printf("Erreur allocation CellNoeud \n");
		exit(2);
	}

	cn->nd = n;
	cn->suiv = NULL;

	return cn;
}


CellCommodite* creerCellCommodite(Noeud* nd, Noeud* nf) {

	CellCommodite* ccom = (CellCommodite*)malloc(sizeof(CellCommodite));

	if (nd == NULL || nf == NULL) {
		printf("Erreur noeuds \n");
		exit(3);
	}

	ccom->extrA = nd;
	ccom->extrB = nf;
	ccom->suiv = NULL;

	return ccom;
}


//Ajout de structures

void ajout_NoeudNoeud(Noeud *n1, Noeud *n2) {                     //fait office d'ajout au voisinage en tête
 
	if (n2 == NULL) 
		return;
	if (n1 == NULL) 
		n1 = n2;

	CellNoeud *stock = n1->voisins;
	n1->voisins = creerCellNoeud(n2);
	n1->voisins->suiv = stock;
}


void* ajout_NoeudReseau(Reseau *R, Noeud *n) {                    //ajout de CellNoeud crée à partir d'un noeud en tête des noeuds du réseau
  
	if (n == NULL) 
		return NULL;

        CellNoeud *cn = creerCellNoeud(n);
        CellNoeud *stock = R->noeuds;
   	cn->suiv = stock;
   	R->noeuds = cn;
	R->nbNoeuds++;                                            //mise à jour du compteur

    	return cn;
}


void ajout_CellNoeudCellNoeud(CellNoeud *cn, CellNoeud *cn1) {    //ajout de CellNoeud à CellNoeud en queue
 
        if (cn == NULL) {
            cn = cn1;
            return;
        }

        if (cn1 == NULL) 
            return;

        while (cn->suiv) {
		cn = cn->suiv;
	}

    	cn->suiv = cn1;
}


void ajout_NoeudCellNoeud(CellNoeud **cn, Noeud *n) {             //ajout d'un noeud à CellNoeud
  
	if (n == NULL) 
		return;

        if (*cn == NULL) {
        	*cn = creerCellNoeud(n);
        	return;
        }

        CellNoeud *c = creerCellNoeud(n);
   	c->suiv = *cn;
   	*cn = c;
}


CellCommodite *ajout_CellCommodite_EnTete( CellCommodite *ccom, CellCommodite *c) {

        if (c == NULL) 
		return ccom;                                     //on recupere la "Nouvelle" commodité en résultat de fonction                     
    	
	if (ccom == NULL) 
		return c;
    	
	c->suiv = ccom;                                          //si la commodité à ajouter n'est pas nulle, son champ suivant est la commodité de base
    
	return c;
}


//Libération des structures 

void libererNoeud(Noeud* n) {

  	if (n) {
    		libererCellNoeud(n->voisins);
    		free(n);
  	}
}


void libererCellNoeud(CellNoeud* cellN) {

	while (cellN) {
    		libererNoeud(cellN->nd);
    		CellNoeud *tmp = cellN;
    		cellN = cellN->suiv;
    		free(tmp);
  	}
}


void libererCellCommodite(CellCommodite* cellCom) {

	while(cellCom) {
    		CellCommodite *tmp = cellCom;
    		cellCom = cellCom->suiv;
    		free(tmp);
  	}
}


void libererReseau(Reseau* R) {
	
	libererCellNoeud(R->noeuds);
	libererCellCommodite(R->commodites);
	free(R);
}


//Comparaisons de structures

int recherche_CellList(CellNoeud *cn, Noeud *n) {                //permet de recherche un noeud dans une CellNoeud
 
        if (cn == NULL) 
		return 0;

    	if (n == NULL) {
        	PRINT("Problème");
        	exit(-3);
   	}

    	while (cn) {
        	if (egalite_Noeud(cn->nd, n) == 1) 
			return 1;

        	cn = cn->suiv;
    	}

    	return 0;
}


int egalite_Noeud( Noeud *n1, Noeud *n2) {                        //test l'égalité de deux noeuds
 
        if (n1->num == n2->num && n1->x == n2->x && n1->y == n2->y)
		return 1;

    	return 0;
}


int egalite_Noeud_Coord( Noeud *n1, double x, double y) {        //test l'égalité entre les coordonées d'un noeud et des coordonées 

        if (n1->x == x && n1->y == y)
		return 1;

    return 0;
}
