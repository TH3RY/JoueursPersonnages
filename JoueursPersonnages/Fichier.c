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

CodeErreur sauverJoueurs(Joueur* pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	FILE* fiJoueur;
	fopen_s(&fiJoueur, NOMFICHIER, "wb");
	if (fiJoueur == NULL) {
		codeErreur = FICHIER_INEXISTANT;
	} else {
		Joueur* pJoueur = pDebJoueurs;
		while (pJoueur != NULL)	{
			Joueur joueur;
			strcpy_s(joueur.pseudo, TPSEUDO, pJoueur->pseudo);
			int nbPerso = nbrPersonnages(pJoueur);
			fwrite(&joueur.pseudo, sizeof(char)*TPSEUDO, 1, fiJoueur);
			fwrite(&nbPerso, sizeof(int), 1, fiJoueur);

			Personnage* pPerso = pJoueur->pDebPerso;
			Personnage tmpPerso;
			while (pPerso != NULL) {
				strcpy_s(tmpPerso.nom, TNOM, pPerso->nom);
				tmpPerso.nbXp = pPerso->nbXp;
				fwrite(&tmpPerso.nom, sizeof(char) * TNOM, 1, fiJoueur);
				fwrite(&tmpPerso.nbXp, sizeof(int), 1, fiJoueur);

				pPerso = pPerso->Psuiv;
			}
			pJoueur = pJoueur->pSuiv;
		}
		fclose(fiJoueur);
	}
	return codeErreur;
}

//CodeErreur chargerJoueurs(Joueur** pDebJoueurs) {
//	CodeErreur codeErreur = PAS_D_ERREUR;
//	FILE* fiJoueur;
//	fopen_s(&fiJoueur, NOMFICHIER, "wb");
//	if (fiJoueur == NULL) {
//		codeErreur = FICHIER_INEXISTANT;
//	}
//	else {
//		Joueur* pJoueur = NULL;
//		Joueur* pSauvJoueur = NULL;
//		Joueur* pDebJoueurs = NULL;
//	}
//}