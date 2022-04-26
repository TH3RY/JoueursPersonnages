#include "JoueursPerso.h"

CodeErreur fichierExiste() {
	CodeErreur codeErreur = PAS_D_ERREUR;
	FILE* fiJoueur;
	fopen_s(&fiJoueur, NOMFICHIER, "rb");
	if (fiJoueur == NULL) {
		codeErreur = FICHIER_INEXISTANT;
	} else {
		fclose(fiJoueur);
	}
	return codeErreur;
}