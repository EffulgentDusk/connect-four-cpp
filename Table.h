/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>

using namespace std;

/// Gère la modélisation de la table
class Table
{
    public:
        /// Constructeur de la classe Table
        Table();

        /// Fonction utilité
        int utilite();

        /// Permet de placer les pions dans le tableau
        void placerPion(int,int);

        /// Retourne vrai si une colonne de la table est vide
        bool colonneVide(int);

        /// Permet de tester si un gagnant existe dans une instance de jeu
        bool verifierGagnant(int&);

        /// Permet de colorier les pions du gagnant
        void colorierGagnant();

        /// Génère les successeurs de la table en se basant sur les règles du jeu
        vector <Table> genereSuccesseurs(int);

        /// Définition de la fonction heuristique implémentée dans les algos Minimax et AlphaBeta
        /// @utilise les méthodes nbrDe3DeSuite et nbrDe2DeSuite
        int fonctionHeuristique();

        /// Retourne la table ayant le plus grand poids
        Table minTable(Table);

        /// Retourne la table ayant le plus petit poids
        Table maxTable(Table);

        /// Retourne "true" si la table est pleine
        bool tablePleine();

        /// Setteur du poids de la table
        void setPoids(int);

        /// Getteur du poids de la table
        int getPoids();

        /// Getteur du poids d'une case dont les coordonnées sont données en @param
        int getT(int, int);

        /// Setteur du poids d'une case dont les coordonnées sont données en @param
        void setT(int, int, int);

        /// Retourne le nombres de triplets successifs selon les règles du jeu
        int nbrDe3DeSuite(int);

        /// Retourne le nombres de couples successifs selon les règles du jeu
        int nbrDe2DeSuite(int);

    protected:

    private:
        int poids;
        int t[6][7];
};

#endif // TABLE_H
