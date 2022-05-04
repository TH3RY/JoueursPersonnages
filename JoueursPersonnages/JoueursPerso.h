#ifndef JOUEURSPERSO_H
#define JOUEURSPERSO_H

#include "Constantes.h"
#include "Lexique.h"

#define NOMFICHIER "joueurs.dat"

typedef struct personnage Personnage;
struct personnage {
	char nom[TNOM];
	int nbXp;
	Personnage* Psuiv;
};

typedef struct joueur Joueur;
struct joueur {
	char pseudo[TPSEUDO];
	Personnage* pDebPerso;
	Joueur* pSuiv;
};

CodeErreur fichierExiste();
CodeErreur sauverJoueurs(Joueur* pDebJoueurs);
// CodeErreur chargerJoueurs(Joueur** pDebJoueurs);
// -------------------
void nomObtenu(Message* pLexique, char nomObtenu[]);
void dialogue(Message* pLexique);
int pointsObtenus(Message* pLexique);
int reponseObtenue(Message* pLexique, int numMessage);
void pseudoObtenu(Message* pLexique, char pseudo[]);
int choixObtenu(Message* pLexique, int numMenu);

// -------------------
bool nouveauJoueur(Joueur** pNouvJoueur);
bool nouveauPersonnage(Personnage** pNouvPerso);
void libereJoueur(Joueur** pJoueur);
void ajouteJoueur(Joueur** pDebJoueur, char pseudo[], Joueur** pNouvJoueur, Joueur** pJoueur, Joueur** pSauvJoueur);
void liberePersonnage(Personnage** pPerso);
void supprimerJoueur(Joueur** pDebJoueur, Joueur* pJoueur, Joueur* pSauvJoueur);
bool joueurExiste(Joueur* pDebJoueur, char pseudo[], Joueur** pJoueur, Joueur** pSauvJoueur);
bool personnageExiste(Joueur* pDebJoueur, char nom[]);
void ajoutePersonnage(Joueur* pJoueur, char nom[], int points, Personnage* pNouvPerso);
void listeJoueur(Joueur* pDebJoueur);
int nbrPersonnages(Joueur* pJoueur);
void libereJoueursPersonnages(Joueur** pDebJoueur);

CodeErreur chargerJoueursPersonnages(Message* pLexique, Joueur** pDebJoueur);
CodeErreur ajouterPersonnageAJoueur(Message* pLexique, Joueur** pDebJoueur, Joueur* pJoueur, Personnage* pNouvPerso);
CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueur);
CodeErreur ajouterPersonnage(Message* pLexique, Joueur** pDebJoueur);
void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur);
#endif // !JOUEURSPERSO_H
