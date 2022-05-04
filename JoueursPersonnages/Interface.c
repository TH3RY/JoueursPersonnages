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
	bool pseudoValide = true;
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
	bool choixValide = true;
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
				libereJoueursPersonnages(pDebJoueur);
				//chargerJoueurs
			}
		} else {
			//chargerJoueurs
		}
	}
	return codeErreur;
}

CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueurs) {
	Joueur* pNouvJoueur;
	CodeErreur codeErreur;
	bool allocationOk = nouveauJoueur(&pNouvJoueur);

	if (!allocationOk) {
		codeErreur = ALLOCATION_MEMOIRE;
	}
	else {
		codeErreur = PAS_D_ERREUR;
		afficherTitre(pLexique, TITRE_PERSO_AJOUT);
		char pseudo[TPSEUDO];
		pseudoObtenu(pLexique, pseudo);
		Joueur* pJoueur;
		Joueur* pSauvJoueur;
		bool joueurPresent = joueurExiste(*pDebJoueurs, pseudo, &pJoueur, &pSauvJoueur);
		if (joueurPresent) {
			codeErreur = JOUEUR_DEJA_PRESENT;
			libereJoueur(&pNouvJoueur);
		}
		else {
			ajouteJoueur(pDebJoueurs, pseudo, &pNouvJoueur, &pJoueur, &pSauvJoueur);
			bool allocationOk;
			int reponse;
			do
			{
				Personnage* pNouvPerso;
				allocationOk = nouveauPersonnage(&pNouvPerso);
				if (!allocationOk) {
					codeErreur = ALLOCATION_MEMOIRE;
				}
				else {
					codeErreur = ajouterPersonnageAJoueur(pLexique, pDebJoueurs, pNouvJoueur, pNouvPerso);

					if (codeErreur == PAS_D_ERREUR) {
						reponse = reponseObtenue(pLexique, OBT_ENCORE);
					}
				}
			} while (allocationOk && codeErreur == PAS_D_ERREUR && reponse == OUI);
		}
	}
	return codeErreur;
}

CodeErreur ajouterPersonnageAJoueur(Message* pLexique, Joueur** pDebJoueurs, Joueur* pJoueur, Personnage* pNouvPerso) {
	CodeErreur codeErreur = PAS_D_ERREUR;

	char nom[TNOM];
	nomObtenu(pLexique, nom);
	bool persoExiste = personnageExiste(*pDebJoueurs, nom);
	if (persoExiste) {
		codeErreur = PERSONNAGE_DEJA_PRESENT;
		liberePersonnage(&pNouvPerso);
	}
	else {
		int nbrPerso = nbrPersonnages(pJoueur);
		if (nbrPerso < NBMAXPERSO) {
			int points = pointsObtenus(pLexique);

			ajoutePersonnage(pJoueur, nom, points, pNouvPerso);
		}
		else {
			codeErreur = NB_MAX_PERSO_ATTEINT;
		}

	}
	return codeErreur;
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
		nouveauJoueur(&pJoueur);
		nouveauJoueur(&pSauve);
		bool jExiste = joueurExiste(*pDebJoueur, pseudo, &pJoueur, &pSauve);
		if (!jExiste) {
			liberePersonnage(&pNouvPerso);
			return JOUEUR_ABSENT;
		} else {
			codeErreur = ajouterPersonnageAJoueur(pLexique, pDebJoueur, pJoueur, pNouvPerso);
		}
	}
	return codeErreur;
}

void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur) {
	Joueur* p = pDebJoueur;
	if (!p) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
		PAUSE;
	} else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueur(pDebJoueur);
	}
}

void dialogue(Message* pLexique) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	//Personnage x2 = { "Arya", 120, NULL};
	//Personnage x1 = { "Bryan", 75, &x2};
	//Personnage p3 = { "Legolas", 50, NULL};
	//Personnage p2 = { "Gimli", 50, &p3};
	//Personnage p1 = { "Aragorn", 100, &p2};
	////Joueur j3 = { "Cock", NULL, NULL };
	//Joueur j2 = { "Cunegpnde", &x1, NULL };
	//Joueur j1 = { "Adalbert", &p1, &j2 };

	Joueur* pDebJoueurs = NULL;
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
			// codeErreur = supprimerJoueur()
			break;
		case AFFICHER_JOUEURS_PERSONNAGES:
			afficherJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		case SAUVER_JOUEURS_PERSONNAGES:
			codeErreur = sauverJoueurs(pDebJoueurs);
			break;
		}
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + codeErreur);
			PAUSE;
			codeErreur = PAS_D_ERREUR;
		}
		choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	}
}