#ifndef __TABLE_HACHAGE__
#define __TABLE_HACHAGE__
#include "Chaine.h"
#include "Reseau.h"
#include <math.h>


typedef struct noeudh{
    int clef;
    Noeud *n;
    struct noeudh *suiv;
}NoeudH;

typedef struct table_Hachage{ // Q 4.1
    int nE;
    int M;
    NoeudH **T;
}Table_Hachage;

// CRÉATION
NoeudH *creer_NoeudH(int M, Noeud *n);
Table_Hachage *creer_Table_Hachage(int M);

// AJOUT
void ajout_Noeud_Table_Hachage(Table_Hachage *H, double x, double y); // ajout en Tête de la liste a l'indice du tableau correspondant

// RECHERCHE
Noeud *rechercheCreeNoeudHachage(Reseau *R, Table_Hachage *H, double x, double y); // Q 4.4

// RECONSTITUION
Reseau *reconstitueReseauHachage(Chaines *C, int M); // Q 4.5

// AUTRE
int fonctionClef(double x, double y); // Q 4.2
int fonctionHachage(int clef, int m); // Q 4.3
void draw_TH(Table_Hachage *TH);

#endif
