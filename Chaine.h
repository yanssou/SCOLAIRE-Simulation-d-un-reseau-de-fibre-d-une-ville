#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include <stdio.h>


/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;


/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;


/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;


/* Fonctions de gestions des structures */

//Allocation des structures 

CellPoint* alloue_CellPoint(double x, double y);

CellChaine* alloue_CellChaine( CellPoint* points, int num );

Chaines*  alloue_Chaines(int gamma, int nbChaines, CellChaine* chaines);


//Liberation des structures

void liberer_CellPoint(CellPoint* point);

void liberer_CellChaine(CellChaine* c);

void liberer_Chaines(Chaines* c);


//Insertion de structures 

CellPoint*  inserer_CellPoint(CellPoint* point, double x, double y);

CellChaine* inserer_CellChaine(CellChaine* c, CellPoint* points, int num);


//Exercice 1

CellPoint* lire_points(FILE* f, int nbP);

Chaines* lectureChaine(FILE *f);

void ecrireChaines(Chaines *c, FILE *f);

void afficheChainesSVG(Chaines *c, char* nomInstance);

double longueurTotale(Chaines *c);

double longueurChaine(CellChaine* c);

int comptePointsTotal(Chaines *c);


#endif	
