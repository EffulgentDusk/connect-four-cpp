/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#ifndef JEU_H
#define JEU_H
#include "Table.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <time.h>

using namespace std;

/// Gère la logique du jeu
class Jeu
{
    public:
        /// Constructeur de la classe Jeu
        Jeu();

        /// Gère l'affichage de l'interface J vs.J
        void joueurVSjoueur();

        /// Gère l'affichage et les sons de l'interface J vs. AI, algo MinMax
        void minMaxInterface();

        /// Gère l'affichage et les sons de l'interface J vs. AI, algo AlphaBeta
        void alphaBetaInterface();

        /// Gère l'affichage et les sons du choix de la difficulté, pour les deux algos
        int choixDifficulte();

        /// Implémentation de l'algo AlphaBeta
        /// @param tour, profondeur, profondeur voulue, Tablea, et Tableb
        Table alphaBeta(int,int,int,Table,Table);

        /// Gère l'affichage et les sons de pour les deux algos, et appelle @alphaBetaInterface et @minMaxinterface suivant le choix de l'algo
        void algorithmeInterface();

        /// Implementation de l'algo Minimax
        /// @param tour, profondeur, profondeur voulue
        Table minMax(int,int,int);

        /// Affiche le gagnant dans le mode J vs. AI
        void afficherGagnantAI(int);

        /// Permet d'afficher le gagnant dans le mode J vs. J
        void afficherGagnant();

        /// Lance le jeu
        void commencerJeu();

        /// Gère l'affichage et les sons des paramètres du jeu (continuer le jeu, rejouer, menu principal, règles)
        void interfaceParametre(int);

        /// Gère l'affichage de la table du jeu avec les pions
        /// @appelle la méthode colorierGagnant pour colorier les pions
        void afficherGrille(int = 0);

        /// Gère l'affichage des pions correspondants au tour du joueur en cours
        void afficherJoueur(int);

        /// Gère l'affichage du menu principal : les modes (J vs. J, J vs. AI), et les règles
        void afficherMenuPrincipal();

        /// Permet d'alterner les tours entre les deux joueurs au cours du jeu
        void changeTour();

        /// Permet de placer les pions sur l'interface graphique
        bool placerPion(int,int,int);

        /// Remet le jeu à l'état initial (Table vide ayant le poids nul)
        void reinitialiserJeu();

        /// Gère l'affichage et les sons de l'interface qui affiche les règles du jeu
        void afficheReglement();

        /// Met en pause le jeu pour un laps de temps
        void delay(unsigned int);

        /// Destructeur de la classe
        ~Jeu();

    protected:

    private:
        /// Définition les interfaces utilisées par Allegro et nécessaires au fonctionnement de l'interface graphique du jeu
        ALLEGRO_DISPLAY * fenetre;
        ALLEGRO_BITMAP * imageGrille;
        ALLEGRO_BITMAP * pionRouge;
        ALLEGRO_BITMAP * pionJaune;
        ALLEGRO_BITMAP * pionVert;
        ALLEGRO_BITMAP * joueur2;
        ALLEGRO_BITMAP * joueur1;
        ALLEGRO_BITMAP * joueur;
        ALLEGRO_BITMAP * intelligenceA;
        ALLEGRO_BITMAP * fenetreParametre;
        ALLEGRO_BITMAP * menuPrincipal;
        ALLEGRO_BITMAP * icone;

        /// Définition de la partie évenemmentielle
        ALLEGRO_EVENT_QUEUE *queue;
        ALLEGRO_EVENT evenement;

        Table grille;
        int gagnant;
        int tour;
        bool enCours;
        long long nombreDeNoeuds;
};

#endif // JEU_H
