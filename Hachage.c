#include <stdlib.h>
#include <stdio.h>
#include "Hachage.h"
#include "Reseau.h"
#define PRINT(s) printf("%s\n",s);
#define SEPARE printf("----------------------\n")


// CRÉATION

NoeudH *creer_NoeudH(int M, Noeud *n){
    NoeudH *nh = (NoeudH *)malloc(sizeof(NoeudH));
    if( nh == NULL ){
        fprintf(stderr,"Erreur allocation NoeudH.");
        exit(61);
    }
    nh->clef = fonctionHachage(fonctionClef(n->x, n->y), M);
    nh->n = n;
    nh->suiv = NULL;
    return nh;
}

Table_Hachage *creer_Table_Hachage(int M){
    Table_Hachage *th = (Table_Hachage*)malloc(sizeof(Table_Hachage));
    if( th == NULL ){
        fprintf(stderr,"Erreur allocation table hachage\n");
        exit(-50);
    }
    th->nE = 0;
    th->M = M;
    th->T = (NoeudH **)malloc(M*sizeof(NoeudH *));
    for( int i = 0; i < M; i++){
        th->T[i] = NULL;
    }
    return th;
}

// AJOUT

void ajout_Noeud_Table_Hachage(Table_Hachage *H, double x, double y){
    int k = fonctionHachage(fonctionClef(x, y), H->M); // on récupere la clé
    if( k < 0 || k >= H->M ){
        printf("Problème clé.\n");
        exit(60);
    }
    H->nE++;
    Noeud *n = creerNoeud(H->nE, x, y); // On crée le noeud correspondant
    NoeudH *nh = creer_NoeudH(H->M, n); // On crée son NoeudH
    NoeudH *np = H->T[k]; // On se place à l'indice correspondant du tableau
    if( np == NULL || np->n == NULL ){  // on traite le cas où le tableau d'indice k est encore NULL;
        H->T[k] = nh;
        return;
    }
    NoeudH *stock = np;
    H->T[k] = nh; // on le place en tête
    nh->suiv = stock;
}

// RECHERCHE

Noeud *rechercheCreeNoeudHachage(Reseau *R, Table_Hachage *H, double x, double y){ // Q 4.4
    if( R == NULL ){
        printf("Le réseau est vide ou inéxistant.\n");
        return NULL;
    }

    if( H == NULL ){
        printf("La table de hachage est vide.\n");
        return NULL;
    }
    int k = fonctionHachage(fonctionClef(x,y), H->M );
    NoeudH *np = H->T[k];
    if( np == NULL || np->n == NULL ){  // on traite le cas où le tableau d'indice k est encore NULL;
        ajout_Noeud_Table_Hachage(H, x, y); // L'ajout du noeud se fait en tête
        ajout_NoeudReseau(R, H->T[k]->n); // ajout du noeud en tête des noeuds du reseau
        return H->T[k]->n; // L'accès est direct en complexité constante 1
    }
    while( np != NULL ){ // on parcours la liste chainé contenue dans l'indice k du tableau de la table de hachage
        if( egalite_Noeud_Coord(np->n, x, y) == 1 ){ // Si on trouve le noeud correspondant en le retourne
            return np->n;
        }
        np = np->suiv;
    }

    //si on est arrivé a ce niveau c'est que l'on a pas trouvé l'élément
    ajout_Noeud_Table_Hachage(H, x, y); // ajout du noeud en tête de la chaine contenue dans le tableau à l'indice k
    ajout_NoeudReseau(R, H->T[k]->n); // ajout au reseau
    return H->T[k]->n; // on retourne le noeud ajouté 
}

// RECONSTITUION

Reseau *reconstitueReseauHachage(Chaines *C, int M){ // 4.5
    if( M < 0 ){
        printf("Problème taille M.\n");
        exit(70);
    }
    if( C == NULL ){
        printf("La chaine est vide.\n");
        return NULL;
    }
    Reseau *R = creerReseau();
    R->gamma = C->gamma;
    Table_Hachage *TH = creer_Table_Hachage(M);
    CellChaine *cc = C->chaines;
    Noeud *deb ;
    int i;
    Noeud *suiv;
    while( cc ){
        CellPoint *cp = cc->points;
        i = 0;
        deb = NULL;
        suiv = NULL;
        while( cp ){

            Noeud *tmp = rechercheCreeNoeudHachage(R, TH, cp->x, cp->y);
            if( i == 0 ) deb = tmp; // si i est à 0, premier point de la chaine donc une commodité 
            if( cp->suiv == NULL ){ // si son élement suivant (point suiv) est NULL alors il s'agit d'une commodité      
                CellCommodite *com = creerCellCommodite(deb, tmp); // on a déja l'autre extrémité de la commodité donc on crée cette commodité avec ces deux extrémités
                R->commodites = ajout_CellCommodite_EnTete(R->commodites, com ); // on l'ajoute au commodité de R
                break;  // On passe à la chaine suivante
            }
            suiv = rechercheCreeNoeudHachage(R, TH, cp->suiv->x, cp->suiv->y); // si on est arrivé là alors le point suivant existe on lui crée son Noeud 
            if( recherche_CellList(tmp->voisins, suiv) != 1 ){
                ajout_NoeudNoeud(tmp, suiv); // on l'ajoute comme noeud voisin du noeud actuel si il n'y est pas déja présent
            }
            if( recherche_CellList(suiv->voisins, tmp) != 1 ){
                ajout_NoeudNoeud(suiv, tmp);   // on ajoute le noeud actuel comme neoud voisin du suivant ( il fait office de noeud précédent ) s'il n'y est pas déja présent
            }
            i++; // on incrémente le compteur de points de la chaine
            cp = cp->suiv; // on passe au point suivant
        }
        cc = cc->suiv;
    }
    return R;
}

// AUTRE

int fonctionClef(double x, double y){ // Q 4.2
	return y+ (x + y)*(x + y + 1)/2;
}

int fonctionHachage(int clef, int m){ // Q 4.3
	double a = (sqrt(5)-1)/2;
	return floor(m*(clef*a-floor(clef*a)));
}



