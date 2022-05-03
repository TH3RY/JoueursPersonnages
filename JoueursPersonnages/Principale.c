#include "JoueursPerso.h"

void main() {
	Message* pLexique = NULL;
	CodeErreur codeErreur;
	codeErreur = chargerLexique(&pLexique);
	if (codeErreur != PAS_D_ERREUR) {
		if (codeErreur == ALLOCATION_MEMOIRE) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + ALLOCATION_MEMOIRE);
			libererLexique(pLexique);
		} else if (codeErreur == FICHIER_INEXISTANT) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + FICHIER_INEXISTANT);
		}
	} else {
		dialogue(pLexique);
		libererLexique(pLexique);
	}
}