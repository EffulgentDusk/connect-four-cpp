/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>

using namespace std;

/// G�re la mod�lisation de la table
class Table
{
    public:
        /// Constructeur de la classe Table
        Table();

        /// Fonction utilit�
        int utilite();

        /// Permet de placer les pions dans la tableau
        void placerPion(int,int);

        /// Retourne vrai si une colonne de la table est vide
        bool colonneVide(int);

        /// Permet de tester si un gagnant existe dans un instance de jeu
        bool verifierGagnant(int&);

        /// Permet de colorier les pions du gagnant
        void colorierGagnant();

        /// G�n�re les successeurs de la table en se basant sur les r�gles du jeu
        vector <Table> genereSuccesseurs(int);

        /// D�finition de la fonction heuristique impl�ment�e dans les algos Minimax et AlphaBeta
        /// @utilise les m�thodes nbrDe3DeSuite et nbrDe2DeSuite
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

        /// Getteur du poids d'une case dont les coordonn�es sont donn�es en @param
        int getT(int, int);

        /// Setteur du poids d'une case dont les coordonn�es sont donn�es en @param
        void setT(int, int, int);

        /// Retourne le nombres de triplets successifs selon les r�gles du jeu
        int nbrDe3DeSuite(int);

        /// Retourne le nombres de couples successifs selon les r�gles du jeu
        int nbrDe2DeSuite(int);

    protected:

    private:
        int poids;
        int t[6][7];
};

#endif // TABLE_H
