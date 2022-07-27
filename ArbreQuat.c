#include <stdlib.h>
#include <stdio.h>
#include "ArbreQuat.h"
#include "Reseau.h"

// question 5.1 

void chaineCoordMinMax(Chaines* C, double* xmin, double*ymin, double* xmax, double* ymax){
  CellChaine* Cc = C->chaines;
  while(Cc){
    CellPoint* Cp = Cc->points;
    while(Cp){
      if(Cp->x<*xmin){
        *xmin = Cp->x;
      }
      else if(Cp->x>*xmax){
        *xmax = Cp->x;
      }
      if(Cp->y<*ymin){
        *ymin = Cp->y;
      }
      else if(Cp->y>*ymax){
        *ymax = Cp->y;
      }
      Cp=Cp->suiv;
    }
    Cc=Cc->suiv;
  }
}

// question 5.2

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY)
{ 
    ArbreQuat *aq = (ArbreQuat*)malloc(sizeof(ArbreQuat));
    if( aq == NULL){
        fprintf(stderr,"Erreur allocation de l'ArbreQuat.\n");
        exit(80);
    }
    aq->xc = xc,
    aq->yc = yc;
    aq->coteX = coteX;
    aq->coteY = coteY;
    aq->noeud = NULL;
    aq->so = NULL;
    aq->se = NULL;
    aq->no = NULL;
    aq->ne = NULL;

    return aq;
}

// question 5.3

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat*parent){
  if((*a)==NULL){
    if((n->x < parent->xc)&&(n->y < parent->yc)){ //no
      *a = creerArbreQuat(parent->xc/2,parent->yc/2,parent->coteX/2,parent->coteY/2);
      parent->no = (*a);

    }else if((n->x < parent->xc)&&(n->y >= parent->yc)){ //so
      *a = creerArbreQuat(parent->xc/2,parent->yc/2+parent->yc,parent->coteX/2,parent->coteY/2);
      parent->so = (*a);

    }else if((n->x >= parent->xc)&&(n->y >= parent->yc)){ //se
      *a = creerArbreQuat(parent->xc/2+parent->xc,parent->yc/2+parent->yc,parent->coteX/2,parent->coteY/2);
      parent->se = (*a);
    }else{ //ne
      *a = creerArbreQuat(parent->xc/2+parent->xc,parent->yc/2,parent->coteX/2,parent->coteY/2);
      parent->ne = (*a);
    }
    (*a)->noeud = n;
    return;
  }
  else if((*a)->noeud){
    Noeud* nd = (*a)->noeud;
    (*a)->noeud = NULL;
    insererNoeudArbre(nd,a,*a);
    insererNoeudArbre(n,a,*a); 
    return;
  }
  else{
    if((n->x < (*a)->xc)&&(n->y < (*a)->yc)){ //no
      insererNoeudArbre(n,&(*a)->no,*a);
    }else if((n->x < (*a)->xc)&&(n->y >= (*a)->yc)){ //so
      insererNoeudArbre(n,&(*a)->so,*a);
    }else if((n->x >= (*a)->xc)&&(n->y >= (*a)->yc)){ //se
      insererNoeudArbre(n,&(*a)->se,*a);
    }else{ //ne
      insererNoeudArbre(n,&(*a)->ne,*a);
    }
  }
}

// question 5.4

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y){
  if((*a)==NULL){
    Noeud* n = malloc(sizeof(Noeud));
    n->x=x;
    n->y=y;
    n->num = R->nbNoeuds+1;
    n->voisins = NULL;
    R->nbNoeuds++;
    CellNoeud* Cn = malloc(sizeof(CellNoeud));
    Cn->suiv = R->noeuds;
    R->noeuds = Cn;
    Cn->nd = n;
    insererNoeudArbre(n,a,parent);
    return n;
  }
  else if((*a)->noeud){
    if(((*a)->noeud->x==x)&&((*a)->noeud->y==y)){
      return (*a)->noeud;
    }
    else{
      Noeud* n = malloc(sizeof(Noeud));
      n->x=x;
      n->y=y;
      n->num = R->nbNoeuds+1;
      n->voisins = NULL;
      R->nbNoeuds++;
      CellNoeud* Cn = malloc(sizeof(CellNoeud));
      Cn->suiv = R->noeuds;
      R->noeuds = Cn;
      Cn->nd = n;
      insererNoeudArbre(n,a,*a);
      return n;
    }
  }
  else{
    if((x < (*a)->xc)&&(y < (*a)->yc)){ //no
      return rechercheCreeNoeudArbre(R,&(*a)->no,*a,x,y);
    }else if((x < (*a)->xc)&&(y >= (*a)->yc)){ //so
      return rechercheCreeNoeudArbre(R,&(*a)->so,*a,x,y);
    }else if((x >= (*a)->xc)&&(y >= (*a)->yc)){ //se
      return rechercheCreeNoeudArbre(R,&(*a)->se,*a,x,y);
    }else{ //ne
      return rechercheCreeNoeudArbre(R,&(*a)->ne,*a,x,y);
    }
  }
}

// question 5.5

Reseau* reconstitueReseauArbre(Chaines* C){
  //Fonction qui reconstruit le réseau R à partir de la liste des chaînes C et en utilisant l'arbre quaternaire
  //On crée le reseau
  Reseau* reseau=(Reseau*)malloc(sizeof(Reseau));
  if(reseau==NULL){
    fprintf(stderr, "Erreur d'allocation du Reseau\n");
    return NULL;
  }
  reseau->nbNoeuds=0;
  reseau->gamma=C->gamma;
  reseau->noeuds=NULL;
  reseau->commodites=NULL;
  //On trouve les coordonnées minimales et maximales de la chaine
  double coteXMin;
  double coteYMin;
  double coteXMax;
  double coteYMax;
  chaineCoordMinMax(C,&coteXMin,&coteYMin,&coteXMax,&coteYMax);
  //Création de l'arbre quaternaire avec les coordonnées XMax et YMax
  ArbreQuat* abr=creerArbreQuat(coteXMin+(coteXMax-coteXMin)/2,coteYMin+(coteYMax-coteYMin)/2, coteXMax*2, coteYMax*2);
  CellChaine* cellchaine = C->chaines;
  //compteur de points totales
  int cpt=0;
  while (cellchaine){
   CellPoint* cellpoint=cellchaine->points;
   Noeud* temp=rechercheCreeNoeudArbre(reseau,&abr,abr,cellpoint->x, cellpoint->y);
   Noeud* comA=temp;
   cellpoint=cellpoint->suiv;
   cpt++;
   while (cellpoint){
      Noeud* n1=rechercheCreeNoeudArbre(reseau,&abr,abr,cellpoint->x, cellpoint->y);
      CellNoeud* temp1=(CellNoeud*)malloc(sizeof(CellNoeud));
      CellNoeud* temp2=(CellNoeud*)malloc(sizeof(CellNoeud));
      if(temp1==NULL || temp2==NULL){
        fprintf(stderr, "Erreur d'allocation en cours de reconstitution\n");
        return NULL;
      }
      temp1->nd=n1;
      temp2->nd=temp;
      CellNoeud* v1=n1->voisins;
        int g=0;
        while(v1){
             if(v1->nd->x==temp->x && v1->nd->y==temp->y){
              g=1;
          }
          v1=v1->suiv;
        }
        //On gère le cas des voisins
        if(g==0){
          temp2->suiv=n1->voisins;
          n1->voisins=temp2;
          temp1->suiv=temp->voisins;
          temp->voisins=temp1;
        }
      temp=n1;
      cpt++;
      cellpoint=cellpoint->suiv;
  }
  Noeud* comB=temp;
  CellCommodite* commod=(CellCommodite*)malloc(sizeof(CellCommodite));
  if(commod==NULL){
    fprintf(stderr, "Erreur d'allocation de la CellCommodite\n");
    return NULL;
  }
  //Gestion des deux extremités d'une commoditée
  commod->extrA=comA;
  commod->extrB=comB;
  //Gestion de la liaison des commoditées avec le réseau
  commod->suiv=reseau->commodites;
  reseau->commodites=commod;
  cellchaine = cellchaine->suiv;
  }
  return reseau;
}

void libererArbreQuat(ArbreQuat* A){
  if(A==NULL){
    return;
  }
  if(A->so){
    libererArbreQuat(A->so);
  }
  if(A->se){
    libererArbreQuat(A->se);
  }
  if(A->no){
    libererArbreQuat(A->no);
  }
  if(A->ne){ 
    libererArbreQuat(A->ne);
  }
  free(A);
}