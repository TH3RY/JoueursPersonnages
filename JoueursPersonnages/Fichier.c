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
		Joueur* pJoueur;
		pJoueur = pDebJoueurs;
		while (pJoueur != NULL) {
			jSauve tmpJoueur;
			strcpy_s(tmpJoueur.pseudo, TPSEUDO, pJoueur->pseudo);
			tmpJoueur.nbPerso = nbrPersonnages(pJoueur);
			fwrite(&tmpJoueur, sizeof(jSauve), 1, fiJoueur);

			Personnage* pPerso;
			pPerso = pJoueur->pDebPerso;
			while (pPerso != NULL) {
				pSauve tmpPerso;
				strcpy_s(tmpPerso.nom, TNOM, pPerso->nom);
				tmpPerso.nbXp = pPerso->nbXp;
				fwrite(&tmpPerso, sizeof(pSauve), 1, fiJoueur);
				pPerso = pPerso->Psuiv;
			}
			pJoueur = pJoueur->pSuiv;
		}
		fclose(fiJoueur);
	}
	return codeErreur;
}

CodeErreur chargerJoueurs(Joueur** pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	FILE* fiJoueur;
	fopen_s(&fiJoueur, NOMFICHIER, "rb");
	if (fiJoueur == NULL) {
		codeErreur = FICHIER_INEXISTANT;
	} else {
		Joueur* pJoueur = NULL;
		Joueur* pSauvJoueur = NULL;
		Joueur* pNouvJoueur = NULL;

		jSauve tmpJoueur;
		
		bool allocOk = true;
		
		fread(&tmpJoueur, sizeof(jSauve), 1, fiJoueur);
		
		while (!feof(fiJoueur) && allocOk) {
			allocOk = nouveauJoueur(&pNouvJoueur);
			if (!allocOk) {
				codeErreur = ALLOCATION_MEMOIRE;
			} else {
				ajouteJoueur(pDebJoueurs, tmpJoueur.pseudo, &pNouvJoueur, &pJoueur, &pSauvJoueur);
				pSauvJoueur = pNouvJoueur;
				int iPersonnage = 0;
				Personnage* pNouvPerso;
				while (iPersonnage < tmpJoueur.nbPerso && allocOk) {
					allocOk = nouveauPersonnage(&pNouvPerso);
					if (!allocOk) {
						codeErreur = ALLOCATION_MEMOIRE;
					} else {
						pSauve tmpPerso;
						fread(&tmpPerso, sizeof(pSauve), 1, fiJoueur);
						ajoutePersonnage(pNouvJoueur, tmpPerso.nom, tmpPerso.nbXp, pNouvPerso);
						iPersonnage++;
					}
				}
				if (allocOk) {
					fread(&tmpJoueur, sizeof(jSauve), 1, fiJoueur);
				}
			}
		}
		fclose(fiJoueur);
	}
	return codeErreur;
}