#include "JoueursPerso.h"

void nomObtenu(Message* pLexique, char nomObtenu[]) {
	afficherMessage(pLexique, OBT_NOM);
	scanf_s(" %s", nomObtenu, TNOM);
	while (isdigit(nomObtenu[0])) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + NOM_NON_VALIDE);
		scanf_s(" %s", nomObtenu, TNOM);
	}
}

int pointsObtenus(Message* pLexique) {
	int nbPoints;
	afficherMessage(pLexique, OBT_POINTS);
	scanf_s("%d", &nbPoints);
	while (nbPoints < 1 || nbPoints > 999) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + POINTS_NON_VALIDES);
		scanf_s("%d", &nbPoints);
	}
	return nbPoints;
}

int reponseObtenue(Message* pLexique, int numMessage) {
	int reponse;
	afficherMessage(pLexique, numMessage);
	scanf_s("%d", &reponse);
	while (reponse != 1 && reponse != 2) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + REPONSE_NON_VALIDE);
		scanf_s("%d", &reponse);
	}
	return reponse;
}

void pseudoObtenu(Message* pLexique, char pseudo[]) {
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		scanf_s(" %s", pseudo, TPSEUDO);

		pseudoValide = (isalpha(pseudo[0]) && isupper(pseudo[0]));
		if (!pseudoValide) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE);
		}
	} while (!pseudoValide);
}

int choixObtenu(Message* pLexique, int numMenu) {
	int maxChoix;
	int choix;
	bool choixValide;
	do {
		maxChoix = afficherMenu(pLexique, numMenu);
		afficherMessage(pLexique, OBT_CHOIX);
		scanf_s("%d", &choix);
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) 
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX);		
	} while (!choixValide);
	return choix;
}

CodeErreur chargerJoueursPersonnages(Message* pLexique, Joueur** pDebJoueur) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	codeErreur = fichierExiste();
	if (codeErreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if (*pDebJoueur != NULL) {
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			int reponse = reponseObtenue(pLexique, OBT_CONTINUER);
			if (reponse == OUI) {
				libèreJoueursPersonnages(pDebJoueur);
				//chargerJoueurs
			}
		} else {
			//chargerJoueurs
		}
	}
	return codeErreur;
}

CodeErreur ajouterPersonnageAJoueur(Message* pLexique, Joueur** pDebJoueur, Joueur* pJoueur, Personnage* pNouvPerso) {
	char nom[TNOM];
	nomObtenu(pLexique, nom);
	if (personnageExiste(*pDebJoueur, nom)) {
		liberePersonnage(pNouvPerso);
		return PERSONNAGE_DEJA_PRESENT;
	} else {

		if (nbrPersonnages(pJoueur) < NBMAXPERSO) {

			ajoutePersonnage(pJoueur, nom, pointsObtenus(pLexique), pNouvPerso);
		} else {
			return NB_MAX_PERSO_ATTEINT;
		}
	}
	return PAS_D_ERREUR;
}

CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueur) {
	Joueur* pNouv;
	bool allocOK;
	CodeErreur codeErreur = PAS_D_ERREUR;
	int reponse;
	if (!nouveauJoueur(&pNouv)) {
		return ALLOCATION_MEMOIRE;
	} else {
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		char pseudo[TPSEUDO];
		pseudoObtenu(pLexique, pseudo);
		Joueur* pJoueur = NULL;
		Joueur* pSauvJoueur = NULL;
		if (joueurExiste(pDebJoueur, pseudo, pJoueur, pSauvJoueur)) {
			libereJoueur(pNouv);
			return JOUEUR_DEJA_PRESENT;
		} else {
			ajouteJoueur(pDebJoueur, pseudo, pNouv, pJoueur, pSauvJoueur);
			do {
				Personnage *pNouv = NULL;
				allocOK = nouveauPersonnage(&pNouv);

				if (!allocOK) {
					return ALLOCATION_MEMOIRE;
				} else {
					ajouterPersonnageAJoueur(pLexique, pDebJoueur, pJoueur, pNouv);
					if (codeErreur == PAS_D_ERREUR) {
						reponse = reponseObtenue(pLexique, OBT_ENCORE);
					}
				}
			} while (allocOK && codeErreur == PAS_D_ERREUR && reponse == OUI);
		}
	}
	return PAS_D_ERREUR;
}

CodeErreur ajouterPersonnage(Message* pLexique, Joueur** pDebJoueur) {
	Personnage* pNouvPerso = NULL;
	bool allocOK = nouveauPersonnage(&pNouvPerso);
	CodeErreur codeErreur = PAS_D_ERREUR;
	if (!allocOK) {
		return ALLOCATION_MEMOIRE;
	} else {
		afficherTitre(pLexique, TITRE_PERSO_AJOUT);
		char pseudo[TPSEUDO];
		pseudoObtenu(pLexique, pseudo);
		Joueur* pSauve = NULL;
		Joueur* pJoueur = NULL;
		if (!joueurExiste(pDebJoueur, pseudo, pJoueur, pSauve)) {
			liberePersonnage(pNouvPerso);
			return JOUEUR_ABSENT;
		} else {
			codeErreur = ajouterPersonnageAJoueur(pLexique, pDebJoueur, pJoueur, pNouvPerso);
		}
	}
	return codeErreur;
}

void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur) {
	if (!pDebJoueur) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
		PAUSE;
	} else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueur(pDebJoueur);
	}
}

void dialogue(Message* pLexique) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	Joueur *pDebJoueurs = NULL;

	int choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	while (choix != QUITTER) {
		switch (choix) {
		case CHARGER_JOUEURS_PERSONNAGES:
			codeErreur = chargerJoueursPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_JOUEUR_PERSONNAGES:
			codeErreur = ajouterJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGE_PERSONNAGES:
			codeErreur = ajouterPersonnage(pLexique, &pDebJoueurs);
			break;
		case SUPPRIMER_JOUEUR:

			break;
		case AFFICHER_JOUEURS_PERSONNAGES:
			afficherJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		case SAUVER_JOUEURS_PERSONNAGES:
			break;
		}
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + codeErreur);
			codeErreur = PAS_D_ERREUR;
		}
		choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	}
}