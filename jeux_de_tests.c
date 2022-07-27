#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

int main(int argc, char const *argv[]) {

	/*if (argc != 2) {
		printf("Erreur, il faut mettre un nom de fichier en argument \n");
		exit(1);
	}*/


	/* EXERCICE 1 */

							        //test des fonctions mémoire pour les structures

/*	CellPoint* CP = alloue_CellPoint(12.0, 13.4);
	inserer_CellPoint(CP, 15.2, 16.5);
	liberer_CellPoint(CP);

	CellPoint* cp = alloue_CellPoint(12.5, 4.8);
	CellChaine* CH = alloue_CellChaine(cp, 4);
	inserer_CellChaine(CH, cp, 8);
	liberer_CellPoint(cp);
	liberer_CellChaine(CH);

	CellPoint* cp_bis = alloue_CellPoint(5.9, 9.7);
	CellChaine* ch = alloue_CellChaine(cp_bis, 8);
	Chaines* c = alloue_Chaines(2, 6, ch);
	liberer_CellPoint(cp_bis);
	liberer_CellChaine(ch);
	liberer_Chaines(c);
*/
							        //test des fonctions supplémentaires sur les chaînes

/*	FILE* f = fopen(argv[1], "r");
	Chaines* C = lectureChaine(f);

	double distance = longueurChaine(C->chaines);
	printf("Longueur Chaine : %lf \n", distance);

	double longueur_tot = longueurTotale(C);
	printf("Longueur Totale : %lf \n", longueur_tot);

	int points = comptePointsTotal(C);
	printf("Nombre Total De Points : %d \n", points);

	liberer_Chaines(C);
	fclose(f);
*/

	/* EXERCICE 2 & 3 */


								//test des fonctions mémoire pour les structures
/*	Reseau* B = creerReseau();
	Noeud* noeud = creerNoeud(3, 2.0, 1.0);
	Noeud* noeud2 = creerNoeud(3, 3.0, 1.0);
	CellNoeud* cn = creerCellNoeud(noeud);
	CellCommodite* c = creerCellCommodite(neoud, noeud2);
	
								//test des fonctions de gestions du réseau
	ajout_NoeudReseau(B, noeud);
	ajout_NoeudReseau(B, noeud2);
	Noeud* noeud3 = creerNoeud(3, 4.0, 1.0);
	Noeud* noeud4 = creerNoeud(3, 8.0, 1.0);
	CellCommodite* c2 = creerCellCommodite(neoud3, noeud4);
	ajout_CellCommodite_EnTete(c, c2);
	egalite_Noeud(noeud, neoud2);
	egalite_Noeud(noeud3, noeud3);
	egalite_Noeud_Coord(noeud, 2.0, 1.0);
	egalite_Noeud_Coord(noeud, 2.0, 10.0);
	
	libererReseau(B);
	libererNoeud(noeud3);
	libererNoeud(noeud4);
	libererCellCommodite(c);
*/
								//test de reconstitueReseauListe

	/*FILE* f = fopen(argv[1], "r");
    	if (f == NULL) {
      		fprintf(stderr, "Probleme ouverture : il nous faut le nom du fichier  pour le lire \n");
    	}

   	Chaines* c = lectureChaine(f);
	if (c) {
		printf("C existe ! \n");
		printf("%d %d \n", c->gamma, c->nbChaines);
		printf("%d \n", c->chaines->numero);
	}

	Reseau* R = reconstitueReseauListe(c);*/

								//test de nbLiaisons et nbCommodites ex4

/*	if (R) {
		printf("Info sur le réseau : %d %d %d %d", R->nbNoeuds, R->gamma, nbLiaisons(R), nbCommodites(R));
	}
*/
/*								//test de rechercheNoeudListe

	rechercheCreeNoeudListe(R, 5.9, 9.7);
	rechercheCreeNoeudListe(R, 5.9, 9.7);
	rechercheCreeNoeudListe(R, 5.9, 10.0);
	afficherListe(R->Noeuds);
*/
								//test de ecrireReseau

	//FILE* f2 = fopen(argv[1], "w");
	//ecrireReseau(R, f2);
/*	if (argc == 3)
		afficheReseauSVG(R, argv[2]);
	else
		afficheReseauSVG(R, "SVGreseauTEST");

	libererReseau(R);
	fclose(f2);
*/
		
	/* EXERCICE 4 */

 								//test des fonctions basique pour la table de hachage
 
    //	TableHachage* H = creerTableH(250);
/*	afficherTH(H);
	libererTableH(H);

	for (double x = 0.0; x < 10.0; x++) {
        	for (double y = 0.0; y < 10.0; y++) {
	     		printf("Pour x : %.1f et y : %.1f, la clef f test est %.1f \n", x, y, clef_f(x,y));
        	}
    	}

	double a = clef_f(1.0, 2.5);
	double b = clef_f(100.2, 56.3);
	double c = clef_f(100.2, 56.3);

	printf("%d \n", hachage(a, 10));
	printf("%d \n", hachage(b, 10));
	printf("%d \n", hachage(c, 10));

								//test rechercheNoeudHachage

	rechercheCreeNoeudHachage(R, H, 12.0, 13.4);
	afficherTH(H);
	rechercheCreeNoeudHachage(R, H, 12.0, 13.4);
	rechercheCreeNoeudHachage(R, H, 12.5, 4.8);
	afficherTH(H);
*/
								//test de reconstitueReseauHachage

	//Reseau* G = reconstitueReseauHachage(c, H->taille);
/*	if (G) {
		printf("Info sur le réseau : %d %d %d %d", G->nbNoeuds, G->gamma, nbLiaisons(G), nbCommodites(G));
	}
*/
	//libererTableH(H);
	//libererReseau(G);

	//fclose(f);

	/* EXERCICE 5 */

	/*FILE* f = fopen("00014_burma.cha","r");
	ArbreQuat* a = creerArbreQuat(2.5,4.0,8.2,4.2);
	//ArbreQuat* parent = creerArbreQuat(8.4,2.2,3.6,9.6);
	Chaines* C = lectureChaine(f);

	printf("%f\n",a->xc );
	printf("%d\n",C->gamma );
	Reseau* R = creerReseau();
	//Noeud* n = creerNoeud(4,2.3,5.6);
	FILE* f2 = fopen("reseauArbreQuat.txt","w+");

	R = reconstitueReseauArbre(C);
	ecrireReseau(R,f2);
	afficheReseauSVG(R,"ReseauArbreQuatSVG");
	*/

	/* CREATION DES SVG */

	/*FILE *f1 = fopen("00014_burma.cha","r+");
	FILE *f2 = fopen("05000_USA-road-d-NY.cha","r+");
	FILE *f3 = fopen("07397_pla.cha","r+");
    if( f1 == NULL || f2 == NULL || f3 == NULL ){
        fprintf(stderr,"Erreur ouverture fichier 1.\n");
        exit(02);
    }

    Chaines* C1 = lectureChaine(f1);
	Chaines* C2 = lectureChaine(f2);
	Chaines* C3 = lectureChaine(f3);

	Reseau* R1 = creerReseau();
	Reseau* R2 = creerReseau();
	Reseau* R3 = creerReseau();

	int M = 30;

	R1 = reconstitueReseauArbre(C1);
	R2 = reconstitueReseauArbre(C2);
	R3 = reconstitueReseauArbre(C3);

	afficheReseauSVG(R1, "reseauArbreBurmaSVG");
	afficheReseauSVG(R2, "reseauArbreUsaSVG");
	afficheReseauSVG(R3, "reseauArbrePlaSVG");*/


	return 0;
}