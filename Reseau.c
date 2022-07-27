#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "SVGwriter.h"
#define PRINT(s) printf("%s \n", s);


/* Exercice 2 */

//2.1

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) {

	if (R == NULL) {	                                         //cas où le réseau est null, on le créer nous même
		R = creerReseau();
		ajout_NoeudReseau(R, creerNoeud(R->nbNoeuds, x, y));
		return R->noeuds->nd;
	}

	if (R->noeuds == NULL) {		                         //cas où le reseau ne contient aucun noeuds, on ajoute le noeud aux noeuds du réseau
		ajout_NoeudReseau(R, creerNoeud(R->nbNoeuds, x, y));
		return R->noeuds->nd;
	}

	CellNoeud* cn = R->noeuds;
	while (cn) {		                                         //parcours des noeuds du réseau
		Noeud* n = cn->nd;

		if (n->x == x && n->y == y) {	                         //si le noeud actuel correspond aux coordonnées
			return n;	                                 //on le renvoie
		}

		cn = cn->suiv;						 
	}

	                                                                 //si aucun noeud correspondant aux coordonnées n'a ete trouvé
	int num = R->nbNoeuds;

	Noeud* nres = creerNoeud(num, x, y);	                         //on crée le noeud
	ajout_NoeudReseau(R, nres);	                                 //on l'ajoute au réseau

	return nres;	                                                 
 	 
}


//2.2

Reseau* reconstitueReseauListe(Chaines *C) {

	if (C == NULL || C->chaines == NULL)
		return NULL;

	Reseau* R = creerReseau();
	R->gamma = C->gamma;
	CellChaine* cc = C->chaines;	                  //on stock dans une variable pour parcourir ensuite
	Noeud* deb;	                                  //noeud qu'on utilisera en tant qu'extremité de commodité
	int i = 0;					  
	Noeud* suiv;					  //le noeud cree à partir des coordonnées du point suivant sera stocké ici s'il existe

	while (cc) {
		deb = NULL;		                  //on réinitialise le noeud de départ à chaque nouveau tour de boucle afin de construire la commodité
		i = 0;			                  //de même pour i
		CellPoint* cp = cc->points;
		suiv = NULL;				  //on réinitialise le noeud crée à partir du point suivant

		while(cp) {
			Noeud* tmp = rechercheCreeNoeudListe(R, cp->x, cp->y);		           //on cherche le noeud lié au point actuel de la chaine dans les noeuds du réseau et il est crée et ajouté en cas d'absence
			if (i == 0)
				deb = tmp; 		                                           //car si i = 0, on est sur une commodité
			
			if (cp->suiv == NULL) {
				CellCommodite* com = creerCellCommodite(deb, tmp); 		   //comme on a déjà les extremités, on crée une commodité
				R->commodites = ajout_CellCommodite_EnTete(R->commodites, com);    //on l'ajoute aux commodités du réseau
				break;                                                             //on veut directement passer à la chaine suivante sans continuer
			}

			suiv = rechercheCreeNoeudListe(R, cp->suiv->x, cp->suiv->y); 		   //le point suivant existe, on lui crée donc son noeud

			if (recherche_CellList(tmp->voisins, suiv) != 1)
				ajout_NoeudNoeud(tmp, suiv);		                           //on l'ajoute comme noeud voisin du noeud actuel s'il n'y est pas déjà

			if (recherche_CellList(suiv->voisins, tmp) != 1)
				ajout_NoeudNoeud(suiv, tmp);		                           //ajout du noeud actuel comme voisin du suivant s'il n'y est pas déjà

			i++;
			cp = cp->suiv;
		}

		cc = cc->suiv;
	}
	
	return R;
}


/* Exercice 3 */

//3.1

int nbCommodites(Reseau *R) {

   CellCommodite *courC = R->commodites;

    int res = 0;
    while (courC) {                                                 //on parcourt la liste des commodités et on compte les éléments
        res++;
        courC = courC->suiv;
    }

    return res;
}


int nbLiaisons(Reseau *R) {

    CellNoeud *courN,*courv;

    int res = 0;
    courN = R->noeuds;
    while (courN) {
            courv = courN->nd->voisins;                              //on parcourt la liste des voisins du noeud courant du réseau 
            while (courv != NULL) {
                    if (courv->nd->num < courN->nd->num) 
                            res++;                                   //on compte une liaison si elle n'a pas déjà été rencontrée dans la liste des voisins du voisin courant 
                    courv = courv->suiv;
            }

            courN = courN->suiv;
    }

    return res;
}


//3.2

void ecrireReseau(Reseau *R, FILE *f) {

    CellNoeud * copieN = R->noeuds;
    CellNoeud * copieN2 = R->noeuds;                                                                  //on a besoin de deux pointeurs car deux parcourts de listes non simultanés
    CellCommodite * copieC = R->commodites;
    
    fprintf(f, "NbNoeuds: %d \n NbLiaisons: %d \n NbComodites: %d \n Gamma: %d \n", R->nbNoeuds, nbLiaisons(R), nbCommodites(R), R->gamma);

    fprintf(f, "\n");

    while (copieN) {                                                                                      
        fprintf(f, "v \t %d \t %.6f \t %.6f \n", copieN->nd->num, copieN->nd->x, copieN->nd->y);      //on affiche les coordonées du noeud courant dans la liste des noeuds du réseau
        copieN = copieN->suiv;
    }

    fprintf(f, "\n");

    CellNoeud *courv;
    while (copieN2) {
        courv = copieN2->nd->voisins;
        while (courv) {
            if (courv->nd->num < copieN2->nd->num)
                fprintf(f, "l \t %d \t %d \n", courv->nd->num, copieN2->nd->num);                     //on affiche la liaison entre le noeud courant et son voisin si elle n'a pas déjà été rencontrée
            courv = courv->suiv;
        }
        copieN2 = copieN2->suiv;
    }

    fprintf(f, "\n");

    while (copieC) {
        fprintf(f, "k \t %d \t %d \n", copieC->extrA->num, copieC->extrB->num);                       //on affiche simplement les couple de noeuds commodités de la liste 
        copieC = copieC->suiv;
    }

}


//3.3

void afficheReseauSVG(Reseau *R, char* nomInstance) {

    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;

    courN = R->noeuds;
    while (courN != NULL) {
        if (maxx < courN->nd->x) maxx = courN->nd->x;
        if (maxy < courN->nd->y) maxy = courN->nd->y;
        if (minx > courN->nd->x) minx = courN->nd->x;
        if (miny > courN->nd->y) miny = courN->nd->y;
        courN = courN->suiv;
    }

    SVGinit(&svg, nomInstance, 500, 500);

    courN = R->noeuds;
    while (courN != NULL) {
        SVGpoint(&svg, 500*(courN->nd->x-minx)/(maxx-minx), 500*(courN->nd->y-miny)/(maxy-miny));
        courv = courN->nd->voisins;
        while (courv != NULL) {
            if (courv->nd->num < courN->nd->num)
                SVGline(&svg, 500*(courv->nd->x-minx)/(maxx-minx), 500*(courv->nd->y-miny)/(maxy-miny), 500*(courN->nd->x-minx)/(maxx-minx), 500*(courN->nd->y-miny)/(maxy-miny));
            courv = courv->suiv;
        }

        courN = courN->suiv;
    }

    SVGfinalize(&svg);
}
