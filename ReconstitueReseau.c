#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"

int main(int argc, char* argv[]) {

	if (argc != 2) {
        	printf("Attention donner un nom de fichier '.cha' ou se trouve le reseau a reconstruire. \n");
        	exit(-30);
    	}
		
	printf("Veuillez maintenant rentrer un numero pour une reconstitution du reseau par \n 1 - Listes \n 2 - Hachage \n 3 - Arbres \n");
	int methode = 0;
	scanf("%d", &methode);
	while (methode != 1 && methode != 2 && methode != 3) {
		printf("erreur, veuillez rechoisir entre une des methodes listees ! \n");
		scanf("%d", &methode);
	}

    	FILE* f = fopen(argv[1], "r");
    	if (f == NULL) {
      		fprintf(stderr, "Probleme d'ouverture ! \n");
    	}

    	Chaines* c = lectureChaine(f);
/*	if (c) {
		printf("C existe ! \n");
		printf("%d %d \n", c->gamma, c->nbChaines);
		printf("%d \n", c->chaines->numero);
	}
*/
	Reseau* R;
	switch (methode) {
		case 1:			
			R = reconstitueReseauListe(c);
			if( R != NULL)
				printf("Le reseau a bien ete cree\n");
			break;
		case 2:
			R = reconstitueReseauHachage(c,100);
			if( R != NULL)
				printf("Le reseau a bien ete cree\n");
			break;
		case 3:
			R = reconstitueReseauArbre(c);
			if( R != NULL)
				printf("Le reseau a bien ete cree\n");
			break; 
	}

/*	if (R) {
		printf("Infos sur le reseau : %d %d %d %d", R->nbNoeuds, R->gamma, nbLiaisons(R), nbCommodites(R));
	}
*/
	afficheReseauSVG(R, "ReseauSVG");
	
	liberer_Chaines(c);
	libererReseau(R);

    fclose(f);

    return 0;
}
