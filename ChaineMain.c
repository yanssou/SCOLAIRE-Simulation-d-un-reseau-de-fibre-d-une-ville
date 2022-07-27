#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"


int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Erreur, il faut mettre un nom de fichier en argument \n");
		exit(1);
	}

	/* Exercice 1 */

	// test de la fonction lectureChaine
	FILE* f = fopen(argv[1], "r");
	Chaines* c = lectureChaine(f);

	// test de la fonction ecrireChaines
	FILE* f2 = fopen("lectureChaine.cha", "w");
	ecrireChaines(c, f2);

	//affichage des chaînes
	if (argc == 3)
		afficheChainesSVG(c, argv[2]);
	else
		afficheChainesSVG(c, "SVGchaines");

	liberer_Chaines(c);

	fclose(f2);
	fclose(f);

	return 0;
}
