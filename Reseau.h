#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"


typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */

typedef struct cellnoeud {
    Noeud *nd;                      /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;


/* Noeud du reseau */

struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};


/* Liste chainee de commodites */

typedef struct cellCommodite {
    Noeud *extrA, *extrB;          /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;    /* Cellule suivante dans la liste */
} CellCommodite;


/* Un reseau */

typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;


/* Fonctions de gestion d'un reseau */ 

//Exercice 1
Reseau* creerReseau();

Noeud* creerNoeud(int num, double x, double y);

CellNoeud* creerCellNoeud(Noeud* n);

CellCommodite* creerCellCommodite(Noeud* nd, Noeud* nf);

void libererNoeud(Noeud* n);

void libererCellNoeud(CellNoeud* cellN);

void libererCellCommodite(CellCommodite* cellCom);

void libererReseau(Reseau* R);

void ajout_NoeudNoeud(Noeud *n1, Noeud *n2);

void* ajout_NoeudReseau(Reseau *R, Noeud *n);

void ajout_CellNoeudCellNoeud(CellNoeud *cn, CellNoeud *cn1);

void ajout_NoeudCellNoeud(CellNoeud **cn, Noeud *n);

CellCommodite* ajout_CellCommodite_EnTete( CellCommodite *ccom, CellCommodite *c);

int recherche_CellList(CellNoeud *cn, Noeud *n);

int egalite_Noeud( Noeud *n1, Noeud *n2);

int egalite_Noeud_Coord( Noeud *n1, double x, double y);


//Exercice 2 

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);

Reseau* reconstitueReseauListe(Chaines *C);


//Exercice 3 

int nbCommodites(Reseau *R);

int nbLiaisons(Reseau *R);

void ecrireReseau(Reseau *R, FILE *f);

void afficheReseauSVG(Reseau *R, char* nomInstance);


#endif
