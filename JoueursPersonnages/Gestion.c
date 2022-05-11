#include "JoueursPerso.h"

bool nouveauJoueur(Joueur **pNouvJoueur) {
	*pNouvJoueur = (Joueur*)malloc(sizeof(Joueur));
	return *pNouvJoueur != NULL;
}

bool nouveauPersonnage(Personnage** pNouvPerso) {
	*pNouvPerso = (Personnage*)malloc(sizeof(Personnage));
	return *pNouvPerso != NULL;
}

void libereJoueur(Joueur** pJoueur) {
	free(*pJoueur);
	*pJoueur = NULL;
}

void liberePersonnage(Personnage** pPerso) {
	free(*pPerso);
	*pPerso = NULL;

}

void ajouteJoueur(Joueur** pDebJoueur, char pseudo[], Joueur** pNouvJoueur, Joueur** pJoueur,Joueur** pSauvJoueur) {
	strcpy_s((*pNouvJoueur)->pseudo, TPSEUDO, pseudo);
	(*pNouvJoueur)->pDebPerso = NULL;
	if (*pJoueur == *pDebJoueur) {
		*pDebJoueur = *pNouvJoueur;
	} else {
		(*pSauvJoueur)->pSuiv = *pNouvJoueur;
	}
	(*pNouvJoueur)->pSuiv = *pJoueur;

}

void supprimerJoueur(Joueur** pDebJoueur, Joueur* pJoueur, Joueur* pSauvJoueur) {
	Personnage* pPerso = pJoueur->pDebPerso;
	while (pPerso) {
		Personnage* pSauvPerso = pPerso->Psuiv;
		liberePersonnage(&pPerso);
		pPerso = pSauvPerso;
	}
	if (pJoueur == *pDebJoueur) {
		*pDebJoueur = pJoueur->pSuiv;
	} else {
		pSauvJoueur->pSuiv = pJoueur->pSuiv;
	}
	libereJoueur(&pJoueur);
}

bool joueurExiste(Joueur* pDebJoueur, char pseudo[], Joueur** pJoueur, Joueur** pSauvJoueur) {
	*pJoueur = pDebJoueur;
	while (*pJoueur != NULL && strcmp(pseudo, (*pJoueur)->pseudo) > 0) {
		*pSauvJoueur = *pJoueur;
		*pJoueur = (*pJoueur)->pSuiv;
	}
	return (*pJoueur != NULL && strcmp(pseudo, (*pJoueur)->pseudo) == 0);
}

bool personnageExiste(Joueur* pDebJoueurs, char nom[]) {
	Joueur* pJoueur = pDebJoueurs;
	Personnage* pPerso = NULL;
	nouveauPersonnage(&pPerso);
	bool existe = false;
	while (pJoueur != NULL && !existe) {
		pPerso = pJoueur->pDebPerso;
		while (pPerso != NULL && strcmp(nom, pPerso->nom) != 0) {
			pPerso = pPerso->Psuiv;
		}
		existe = (pPerso != NULL && strcmp(nom, pPerso->nom) == 0);
		pJoueur = pJoueur->pSuiv;
	}
	return existe;
}

void ajoutePersonnage(Joueur* pJoueur, char nom[], int points, Personnage * pNouvPerso) {
	strcpy_s(pNouvPerso->nom, TNOM, nom);
	pNouvPerso->nbXp = points;
	pNouvPerso->Psuiv = pJoueur->pDebPerso;

	pJoueur->pDebPerso = pNouvPerso;
}

void listeJoueur(Joueur* pDebJoueur) {
	Joueur* pJoueur = pDebJoueur;
	while (pJoueur != NULL) {
		printf("%s", pJoueur->pseudo);
		ENTER;
		Personnage* pPerso = pJoueur->pDebPerso;
		while (pPerso != NULL) {
			TAB;
			printf("%s -- %d XP", pPerso->nom, pPerso->nbXp);
			ENTER;
			pPerso = pPerso->Psuiv;
		}
		pJoueur = pJoueur->pSuiv;
	}
	PAUSE;
}

int nbrPersonnages(Joueur* pJoueur) {
	int nbr = 0;
	Personnage* pPerso = pJoueur->pDebPerso;
	while (pPerso != NULL) {
		pPerso = pPerso->Psuiv;
		nbr++;
	}
	return nbr;
}

void libereJoueursPersonnages(Joueur** pDebJoueur) {
	Joueur* pJoueur = *pDebJoueur;
	while (pJoueur) {
		Personnage* pPerso = pJoueur->pDebPerso;
		while (pPerso) {
			Personnage* pPersoSauve = pPerso;
			pPerso = pPerso->Psuiv;
			liberePersonnage(&pPersoSauve);
		}
		Joueur* pJoueurSauve = pJoueur;
		pJoueur = pJoueur->pSuiv;
		libereJoueur(&pJoueurSauve);
	}
	pDebJoueur = NULL;
}

