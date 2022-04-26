#include "JoueursPerso.h"


bool nouveauJoueur(Joueur **pNouvJoueur) {
	*pNouvJoueur = (Joueur*)malloc(sizeof(Joueur));
	return *pNouvJoueur != NULL;
}

bool nouveauPersonnage(Personnage** pNouvPerso) {
	*pNouvPerso = (Personnage*)malloc(sizeof(Personnage));
	return *pNouvPerso != NULL;
}

void libereJoueur(Joueur* pJoueur) {
	free(pJoueur);
}

void liberePersonnage(Personnage* pPerso) {
	free(pPerso);
}

void ajouteJoueur(Joueur** pDebJoueur, char pseudo[], Joueur* pNouvJoueur, Joueur* pJoueur,Joueur* pSauvJoueur) {
	Joueur nouvJoueur;
	strcpy_s(nouvJoueur.pseudo, TPSEUDO, pseudo);
	nouvJoueur.pDebPerso = NULL;
	if (pJoueur == *pDebJoueur) {
		*pDebJoueur = pNouvJoueur;
	} else {
		pSauvJoueur->pSuiv = pNouvJoueur;
	}
	pNouvJoueur->pSuiv = pJoueur;
}

void supprimerJoueur(Joueur** pDebJoueur, Joueur* pJoueur, Joueur* pSauvJoueur) {
	Personnage* pPerso = pJoueur->pDebPerso;
	while (pPerso) {
		Personnage* pSauvPerso = pPerso->Psuiv;
		liberePersonnage(pPerso);
		pPerso = pSauvPerso;
	}
	if (pJoueur == *pDebJoueur) {
		*pDebJoueur = pJoueur->pSuiv;
	} else {
		pSauvJoueur->pSuiv = pJoueur->pSuiv;
	}
	libereJoueur(pJoueur);
}

bool joueurExiste(Joueur** pDebJoueur, char pseudo[], Joueur* pJoueur, Joueur* pSauvJoueur) {
	pJoueur = *pDebJoueur;
	while (pJoueur && strcmp(pseudo, pJoueur->pseudo) < 0) {
		Joueur* pSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	return (pJoueur && strcmp(pseudo, pJoueur->pseudo) == 0);
}

bool personnageExiste(Joueur* pDebJoueur, char nom[]) {
	Joueur* pJoueur = pDebJoueur;
	bool existe = false;
	while (pJoueur != NULL && !existe) {
		Personnage* pPerso = pJoueur->pDebPerso;
		while (pPerso != NULL && strcmp(nom, pPerso->nom) != 0) {
			pPerso = pPerso->Psuiv;
		}
		existe = (pPerso != NULL && strcmp(nom, pPerso->nom) == 0);
		if (existe)
			return existe;
		pJoueur = pJoueur->pSuiv;
	}
	return false;
}

void ajoutePersonnage(Joueur* pJoueur, char nom[], int points, Personnage * pNouvPerso) {
	strcpy_s(pNouvPerso->nom, TNOM, nom);
	pNouvPerso->nbXp = points;
	pNouvPerso->Psuiv = pJoueur->pDebPerso;

	pJoueur->pDebPerso = pNouvPerso;
}

void listeJoueur(Joueur* pDebJoueur) {
	Joueur* pJoueur = pDebJoueur;
	while (pJoueur) {
		printf("%s", pJoueur->pseudo);
		ENTER;
		Personnage* pPerso = pJoueur->pDebPerso;
		while (pPerso) {
			TAB;
			printf("%s -- %d XP", pPerso->nom, pPerso->nbXp);
			ENTER;
			pPerso = pPerso->Psuiv;
		}
		pJoueur = pJoueur->pSuiv;
	}
}

int nbrPersonnages(Joueur* pJoueur) {
	int nbPerso = 0;
	while (pJoueur) {
		nbPerso++;
		pJoueur = pJoueur->pSuiv;
	}
	return nbPerso;
}

void libèreJoueursPersonnages(Joueur** pDebJoueur) {
	Joueur* pJoueur = *pDebJoueur;
	while (pJoueur) {
		Personnage* pPerso = pJoueur->pDebPerso;
		while (pPerso) {
			Personnage* pPersoSauve = pPerso;
			pPerso = pPerso->Psuiv;
			liberePersonnage(pPersoSauve);
		}
		Joueur* pJoueurSauve = pJoueur;
		pJoueur = pJoueur->pSuiv;
		libereJoueur(pJoueurSauve);
	}
	pDebJoueur = NULL;
}

