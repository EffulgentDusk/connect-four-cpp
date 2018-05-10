/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#include "Table.h"

Table::Table()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            t[i][j] = 0;
        }
    }
    poids = 0;
}

void Table::placerPion(int pion, int colonne)
{
    int ligne = 0;

    while (t[ligne+1][colonne] == 0 && ligne < 5)
    {
        ligne += 1;
    }

    t[ligne][colonne] = pion;
}

bool Table::colonneVide(int colonne)
{
    return t[0][colonne] == 0;
}

void Table::setPoids(int pds)
{
    poids = pds;
}

int Table::getPoids()
{
    return poids;
}

bool Table::verifierGagnant(int& gagnant)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] == t[i][j+1] && t[i][j] == t[i][j+2] && t[i][j] == t[i][j+3] && t[i][j] != 0)
            {
                gagnant = t[i][j];

                return true;
            }
        }
    }

    for (int i = 3; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (t[i][j] == t[i-1][j] && t[i][j] == t[i-2][j] && t[i][j] == t[i-3][j] && t[i][j] != 0)
            {
                gagnant = t[i][j];

                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] == t[i+1][j+1] && t[i][j] == t[i+2][j+2] && t[i][j] == t[i+3][j+3] && t[i][j] != 0)
            {
                gagnant = t[i][j];

                return true;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i-3 >= 0 && j+3 < 7)
            {
                if (t[i][j] == t[i-1][j+1] && t[i][j] == t[i-2][j+2] && t[i][j] == t[i-3][j+3] && t[i][j] != 0)
                {
                    gagnant = t[i][j];
                    return true;
                }
            }
        }
    }

    return false;
}

int Table::getT(int x, int y)
{
    return t[x][y];
}

void Table::setT(int x, int y, int val)
{
    t[x][y] = val;
}

vector <Table> Table::genereSuccesseurs(int pion)
{
    vector <Table> successeurs;

    Table temp=*this;

    for(int i = 0; i < 7; i++)
    {
        if(colonneVide(i))
        {
            temp.placerPion(pion, i);
            successeurs.push_back(temp);
        }
        temp=*this;
    }
    return successeurs;
}
void Table::colorierGagnant()
{
    for (int i = 0; i < 6; i++)
    {
        for ( int j = 0; j < 4; j++)
        {
            if (t[i][j] == t[i][j+1] && t[i][j] == t[i][j+2] && t[i][j] == t[i][j+3] && t[i][j] != 0)
            {
                t[i][j] = t[i][j+1] = t[i][j+2] = t[i][j+3] = 3;
            }
        }
    }
    for (int i = 3; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
				if (t[i][j] == t[i-1][j] && t[i][j] == t[i-2][j] && t[i][j] == t[i-3][j] && t[i][j] != 0) {
					t[i][j] = t[i-1][j] = t[i-2][j] = t[i-3][j] = 3;
				}
			}
		}
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
         {
            if (t[i][j] == t[i+1][j+1] && t[i][j] == t[i+2][j+2] && t[i][j] == t[i+3][j+3] && t[i][j] != 0)
                {
                    t[i][j] = t[i+1][j+1] = t[i+2][j+2] = t[i+3][j+3] = 3;
                }
         }
    }
    for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (i-3 >= 0 && j+3 < 7)
                {
					if (t[i][j] == t[i-1][j+1] && t[i][j] == t[i-2][j+2] && t[i][j] == t[i-3][j+3] && t[i][j] != 0)
					{
					    t[i][j] = t[i-1][j+1] = t[i-2][j+2] = t[i-3][j+3] = 3;
					}
				}
			}
		}
}


int Table::nbrDe3DeSuite(int pion)
{
    int repeated = 0;

    for (int i = 0; i < 6; i++)
    {
        for ( int j = 0; j < 5; j++)
        {
            if (t[i][j] == t[i][j+1] && t[i][j] == t[i][j+2] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }

    for (int i = 2;  i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (t[i][j] == t[i-1][j] && t[i][j] == t[i-2][j] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (t[i][j] == t[i+1][j+1] && t[i][j] == t[i+2][j+2] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i-2 >= 0 && j+2 < 7)
            {
                if (t[i][j] == t[i-1][j+1] && t[i][j] == t[i-2][j+2] && t[i][j] == pion)
                {
                    repeated++;
                }
            }
        }
    }

    return repeated;
}

int Table::nbrDe2DeSuite(int pion)
{
    int repeated = 0;

    for (int i = 0; i < 6; i++)
    {
        for ( int j = 0; j < 6; j++)
        {
            if (t[i][j] == t[i][j+1] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (t[i][j] == t[i-1][j] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (t[i][j] == t[i+1][j+1] && t[i][j] == pion)
            {
                repeated++;
            }
        }
    }

    for (int i=0; i<6; i++)
    {
        for (int j=0; j<7; j++)
        {
            if (i-1 >= 0 && j+1 < 7)
            {
                if (t[i][j] == t[i-1][j+1] && t[i][j] == pion)
                {
                    repeated++;
                }
            }
        }
    }

    return repeated;
}

int Table::fonctionHeuristique()
{
    int joueur1 = 0, joueur2 = 0;

    joueur1 = joueur1 + nbrDe3DeSuite(1)*30 + nbrDe2DeSuite(1)*2;
    joueur2 = joueur2 + nbrDe3DeSuite(2)*30 + nbrDe2DeSuite(2)*2;

    return joueur2 - joueur1;
}

int Table::utilite()
{
    int gagnant;
    if(verifierGagnant(gagnant))
    {
        if(gagnant == 1)
        {
            return -400;
        }
        if(gagnant == 2)
        {
            return +400;
        }
    }
    return 0;
}

Table Table::minTable(Table tab)
{
    if(poids < tab.poids)
    {
        return *this;
    }
    else
        return tab;
}

Table Table::maxTable(Table tab)
{
    if(poids > tab.poids)
        return *this;
    else
        return tab;
}

bool Table::tablePleine()
{
    for(int i = 0; i < 7; i++)
    {
        if(colonneVide(i))
            return false;
    }
    return true;
}
