/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#include "Jeu.h"
#define milieuPion 32
#define facile 3
#define moyen 5
#define difficile 7


Jeu::Jeu()
{
    al_init();
    al_init_image_addon();
    al_install_audio();
    al_install_mouse();
    al_init_acodec_addon();

    fenetre = al_create_display(1100, 620);
    imageGrille = al_load_bitmap("images/tablejeu.png");
    pionJaune = al_load_bitmap("images/pionjaune.png");
    pionRouge = al_load_bitmap("images/pionrouge.png");
    pionVert = al_load_bitmap("images/piongagnant.png");
    menuPrincipal = al_load_bitmap("images/menu.png");
    joueur1 = al_load_bitmap("images/joueur1.png");
    joueur2 = al_load_bitmap("images/joueur2.png");
    joueur = al_load_bitmap("images/joueur.png");
    intelligenceA = al_load_bitmap("images/IA.png");
    fenetreParametre = al_load_bitmap("images/popsettings.png");
    icone = al_load_bitmap("images/icon.png");
    al_set_display_icon(fenetre, icone);
	queue = al_create_event_queue();
	/// Les variables sound_bool, rencontrées plus loin dans le code sont utilisées pour éviter que certains sons sont répétées en boucle

    al_register_event_source(queue, al_get_display_event_source(fenetre));
	al_register_event_source(queue, al_get_mouse_event_source());

	enCours = true;
    gagnant = 0;
    tour = 1;
}

void Jeu::delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void Jeu::changeTour()
{
    if (tour == 1) tour = 2;
    else tour = 1;
}

void Jeu::reinitialiserJeu()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0 ; j < 7; j++)
        {
            grille.setT(i,j,0);
        }
    }

    gagnant = 0;
    tour = 1;
    enCours = true;
}

void Jeu::commencerJeu()
{
    ALLEGRO_SAMPLE* effetMenu = al_load_sample("sounds/title.wav");
	al_reserve_samples(1);
    al_play_sample(effetMenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

	afficherMenuPrincipal();
}

void Jeu::afficherGrille(int modeJeu)
{
    al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
    al_draw_bitmap(imageGrille,0, 0, 0);

    ///Initialisation Allegro

    int tablePixel[]={321,401,481,561,640,719,798};

    for(int i = 0 ; i < 6 ; i++ )
    {
        for (int j = 0 ; j < 7 ; j++)
        {
            if(grille.getT(i,j) == 1)
            {
                al_draw_bitmap(pionRouge,tablePixel[j]-milieuPion,183+i*77-milieuPion, 0);
            }
            else if (grille.getT(i,j) == 2)
            {
                al_draw_bitmap(pionJaune,tablePixel[j]-milieuPion,183+i*77-milieuPion, 0);
            }
            else if(grille.getT(i,j) == 3)
            {
                al_draw_bitmap(pionVert,tablePixel[j]-milieuPion,183+i*77-milieuPion, 0);
            }
        }
    }
    afficherJoueur(modeJeu);
    al_flip_display();
}

void Jeu::afficherJoueur(int modeJeu)
{
    if (modeJeu == 1)
    {
        if (tour == 1)
        {
            al_draw_bitmap(joueur1,0,0,0);

        }
        else
        {
            al_draw_bitmap(joueur2,0,0,0);

        }
    }
    if (modeJeu == 2)
    {
        if (tour == 1)
        {
            al_draw_bitmap(joueur,0,0,0);

        }
        else
        {
            al_draw_bitmap(intelligenceA,0,0,0);
        }
    }
}


void Jeu::afficheReglement()
{
    ALLEGRO_BITMAP* reglement = al_load_bitmap("images/rulesanglais.png");
    ALLEGRO_BITMAP* reglementallume = al_load_bitmap("images/rulesanglaislighton.png");

    ALLEGRO_SAMPLE* survolerBouton = al_load_sample("sounds/button_hover.wav");

    bool sound_bool1 = true;

    al_draw_bitmap(reglement, 0, 0, 0);
    al_flip_display();
    while(1)
       {
           al_wait_for_event(queue, &evenement);
           if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
           {
               int x, y;
               x=evenement.mouse.x;
               y=evenement.mouse.y;
               if (x > 310 && x < 370 && y > 500 && y < 530)
                {
                    al_draw_bitmap(reglementallume, 0, 0, 0);
                    al_flip_display();

                    if(sound_bool1 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = false;
                    }
                }
                else
                    {
                        al_draw_bitmap(reglement,0,0,0);
                        al_flip_display();
                        sound_bool1 = true;
                    }

           }

           if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
           {
               int x, y;
               x=evenement.mouse.x;
               y=evenement.mouse.y;

               if (x > 310 && x < 370 && y > 500 && y < 530)
                {
                    return;
                }
           }
           if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(0);
       }
}

void Jeu::afficherMenuPrincipal()
{

    al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
    al_draw_bitmap(menuPrincipal,0, 0, 0);
    al_flip_display();

    ALLEGRO_BITMAP * lumiere1 = al_load_bitmap("images/menu1.png");
    ALLEGRO_BITMAP * lumiere2 = al_load_bitmap("images/menu2.png");
    ALLEGRO_BITMAP * lumiere3 = al_load_bitmap("images/menu3.png");

    ALLEGRO_SAMPLE *survolerBouton = al_load_sample("sounds/button_hover.wav");

    reinitialiserJeu();
    bool sound_bool1 = true;
    bool sound_bool2 = true;
    bool sound_bool3 = true;

	while(enCours)
	{
        al_wait_for_event(queue,&evenement);
        if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 275 && evenement.mouse.y >= 230) joueurVSjoueur();
            if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 375 && evenement.mouse.y >= 330) algorithmeInterface();
            if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 490 && evenement.mouse.y >= 440)
            {
                afficheReglement();
                al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
                al_draw_bitmap(menuPrincipal,0, 0, 0);
                al_flip_display();
            }
        }
        if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
                if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 275 && evenement.mouse.y >= 230)
                {
                    al_draw_bitmap(lumiere1,0,0,0);
                    al_flip_display();

                    if(sound_bool1 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = false;
                        sound_bool2 = true;
                        sound_bool3 = true;
                    }
                }
                else if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 375 && evenement.mouse.y >= 330)
                {
                    al_draw_bitmap(lumiere2,0,0,0);
                    al_flip_display();

                    if(sound_bool2 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = true;
                        sound_bool2 = false;
                        sound_bool3 = true;
                    }

                }
                else if(evenement.mouse.x <= 760 && evenement.mouse.x >= 350 && evenement.mouse.y <= 490 && evenement.mouse.y >= 440)
                {
                    al_draw_bitmap(lumiere3,0,0,0);
                    al_flip_display();

                    if(sound_bool3 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = true;
                        sound_bool2 = true;
                        sound_bool3 = false;
                    }

                }

                else
                {
                    al_draw_bitmap(menuPrincipal,0, 0, 0);
                    al_flip_display();

                    sound_bool1 = true;
                    sound_bool2 = true;
                    sound_bool3 = true;
                }

        }
        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            enCours = false;
	}
}

void Jeu::algorithmeInterface()
{
    ALLEGRO_BITMAP* popAlgorithm;
    ALLEGRO_BITMAP* popAlgorithmRed1;
    ALLEGRO_BITMAP* popAlgorithmRed2;
    ALLEGRO_BITMAP* curseur;

    ALLEGRO_SAMPLE* survolerBouton = al_load_sample("sounds/button_hover.wav");

    popAlgorithm = al_load_bitmap("images/popalgorithm1lightoff.png");
    popAlgorithmRed1 = al_load_bitmap("images/popalgorithm2.png");
    popAlgorithmRed2 = al_load_bitmap("images/popalgorithm3.png");
    curseur = al_load_bitmap("images/popalgorithm1lighton.png");


    al_draw_bitmap(popAlgorithm,0,0,0);
    al_flip_display();

    bool sound_bool1 = true;
    bool sound_bool2 = true;
    bool sound_bool3 = true;

    while (enCours)
    {
       al_wait_for_event(queue,&evenement);
       if(evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
       {
            int x, y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if(x > 470 && x < 680 && y < 380 && y > 310)
            {
                al_draw_bitmap(popAlgorithmRed1,0,0,0);
                al_flip_display();
                if(sound_bool1 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = false;
                        sound_bool2 = true;
                        sound_bool3 = true;
                    }
            }
            else if (x > 425 && x < 720 && y > 405 && y < 470)
            {
                al_draw_bitmap(popAlgorithmRed2,0,0,0);
                al_flip_display();
                if(sound_bool2 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = true;
                        sound_bool2 = false;
                        sound_bool3 = true;
                    }

            }
            else if (x > 335 && x < 390 && y > 465 && y < 495 )
            {
                al_draw_bitmap(curseur,0,0,0);
                al_flip_display();

                if(sound_bool3 == true)
                {
                    al_reserve_samples(1);
                    al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    sound_bool1 = true;
                    sound_bool2 = true;
                    sound_bool3 = false;
                }
            }

            else
            {
                al_draw_bitmap(popAlgorithm,0,0,0);
                al_flip_display();
                sound_bool1 = true;
                sound_bool2 = true;
                sound_bool3 = true;

            }

       }
       if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
       {
           int x , y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if(x>470 && x < 680 && y < 380 && y > 310)
            {
                minMaxInterface();
            }
            else if (x>425 && x < 720 && y > 405 && y < 470)
            {
                alphaBetaInterface();
            }
            else if (x > 335 && x < 390 && y > 465 && y < 495 )
            {
                afficherMenuPrincipal();
            }
       }

       if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);

    }
}

void Jeu::interfaceParametre(int modeJeu)
{
    al_draw_bitmap(fenetreParametre,0,0,0);
    al_flip_display();

    while(enCours)
    {
        al_draw_bitmap(fenetreParametre,0,0,0);
        al_flip_display();
        al_wait_for_event(queue,&evenement);

        if(evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int x,y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;
            if(x<470 && 410 < x)
            {
                if(y<305 && y>240)
                {
                    return;
                }
                if(y < 385 && y>320)
                {
                    if(modeJeu == 1)
                    {
                        reinitialiserJeu();
                        joueurVSjoueur();
                    }
                    if(modeJeu == 2)
                    {
                        reinitialiserJeu();
                        minMaxInterface();
                    }
                    if(modeJeu==3)
                    {
                        reinitialiserJeu();
                        alphaBetaInterface();
                    }
                }
                if(y < 455 && y > 395)
                {
                    afficherMenuPrincipal();
                }
                if (y < 540 && y > 480)
                {
                    afficheReglement();
                }
            }
        }
        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);

    }
}

void Jeu::joueurVSjoueur()
{
    while(enCours)
    {
        al_wait_for_event(queue,&evenement);
        if(evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int x,y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if(placerPion(tour,x,y))
                {
                    changeTour();
                }
            else if (x>=20 && x <= 70 && y >= 555 && y <= 600)
            {
                interfaceParametre(1);
            }
        }
        if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            int x , y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;
        }
        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);
        enCours = !grille.verifierGagnant(gagnant);
        if(grille.tablePleine()) break;
        if(gagnant!=0) changeTour();
        afficherGrille(1);
    }
    cout << gagnant << endl;
    if(gagnant == 0) enCours = false;
    grille.colorierGagnant();
    afficherGrille();
    delay(1000);

    afficherGagnant();
}

bool Jeu::placerPion(int pion, int x, int y)
{
    ALLEGRO_SAMPLE *valid_move_sound = al_load_sample("sounds/valid_move.wav");
    ALLEGRO_SAMPLE *invalid_move_sound = al_load_sample("sounds/invalid_move.wav");


    if(y>115 && y<620)
    {
        if(x>280 && x<=360)
        {
            if(grille.colonneVide(0))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 0);
                    return true;
                }
        }

        if(x>360 && x<=440)
        {
             if(grille.colonneVide(1))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 1);
                    return true;
                }
        }
        if(x>440 && x<=520)
        {
             if(grille.colonneVide(2))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 2);
                    return true;
                }
        }
        if(x>520 && x<=600)
        {
             if(grille.colonneVide(3))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 3);
                    return true;
                }
        }
        if(x>600 && x<=680)
        {
            if(grille.colonneVide(4))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 4);
                    return true;
                }
        }
        if(x>680 && x<=760)
        {
             if(grille.colonneVide(5))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 5);
                    return true;
                }
        }
        if(x>760 && x<=850)
        {
            if(grille.colonneVide(6))
                {
                    al_reserve_samples(1);
                    al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    grille.placerPion(pion, 6);
                    return true;
                }
        }
    }

/// Jouer "invalid_move_sound" dans le cas ou on essaye de cliquer sur une region non permise (sauf sur le button pop settings)
    if (!(x>=20 && x <= 70 && y >= 555 && y <= 600))
    {
        al_reserve_samples(1);
        al_play_sample(invalid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    return false;
}

Table Jeu::minMax(int profondeurDynamique, int tour, int profondeurVoulue)
{
    /// Si la grille est pleine, retourner l'utilité correspondant a l'égalité
    if(grille.tablePleine())
    {
        grille.setPoids(grille.utilite());
    }

    /// Si on a un gagnant
    else if(grille.verifierGagnant(gagnant))
    {
        /// Si le gagnant est Max, retourner l'utilité moins la profondeur (amélioration)
        if (gagnant == 1)
        {
            grille.setPoids(grille.utilite() - profondeurDynamique);
        }
        /// Si le gagnant est Min, retourner l'utilité plus la profondeur (amélioration)
        else if(gagnant == 2)
        {
            grille.setPoids(grille.utilite() + profondeurDynamique);
        }
        return grille;
    }

    /// Si la profondeur est nulle, retourner la fonction heuristique
    else if (profondeurDynamique == 0)
    {
        grille.setPoids(grille.fonctionHeuristique());
        return grille;
    }

    /// Sinon, on génere les successeurs
    else
    {
        Table Tablev, copieGrille = grille;
        /// Si c'est le tour de Max
        if (tour == 1)
        {

            Tablev.setPoids(-10000);
            /// Génération des successeurs
            vector <Table> listNoeuds = grille.genereSuccesseurs(2);
            for (int i = 0 ; i < listNoeuds.size(); i++)
            {
                nombreDeNoeuds++;
                grille = listNoeuds[i];
                /// Appel récursif de la méthode
                Tablev = Tablev.maxTable(minMax(profondeurDynamique - 1, tour+1, profondeurVoulue));
            }

            if (profondeurDynamique == profondeurVoulue)
            {
                return Tablev;
            }

            copieGrille.setPoids(Tablev.getPoids());
            Tablev = copieGrille;
            return Tablev;
        }
        /// Si c'est le tour de Min
        else
        {
            Tablev.setPoids(10000);
            ///Génération des successeurs
            vector <Table> listNoeuds = grille.genereSuccesseurs(1);
            for (int i = 0 ; i < listNoeuds.size(); i++)
            {
                nombreDeNoeuds++;
                grille = listNoeuds[i];
                /// Appel récursif de la méthode MiniMax
                Tablev = Tablev.minTable(minMax(profondeurDynamique - 1,tour-1,profondeurVoulue));
            }
            grille = copieGrille;

            if (profondeurDynamique == profondeurVoulue)
            {
                return Tablev;
            }
            copieGrille.setPoids(Tablev.getPoids());
            Tablev = copieGrille;
            return Tablev;
        }
    }
}

void Jeu::minMaxInterface()
{
    int difficulte = choixDifficulte();

    ALLEGRO_SAMPLE *valid_move_sound = al_load_sample("sounds/valid_move.wav");

    while(enCours)
    {
        if(tour == 1)
        {
            al_wait_for_event(queue,&evenement);
            if(evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                int x,y;
                x=evenement.mouse.x;
                y=evenement.mouse.y;
            if(placerPion(tour,x,y))
            {
                changeTour();
            }
            else if (x>=20 && x <= 70 && y >= 555 && y <= 600)
            {
                interfaceParametre(2);
            }
        }

        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(0);
        enCours = !grille.verifierGagnant(gagnant);
        afficherGrille(2);
        }

        else
        {
            changeTour();
            nombreDeNoeuds = 0;
            grille = minMax(difficulte,tour,difficulte);
            changeTour();
            if (difficulte == facile)
            {
                delay(500);
            }

            if (difficulte == moyen)
            {
                delay(500);
            }

            al_reserve_samples(1);
            al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            cout << "Nombre de noeuds parcourus par l'algo MinMax :" << nombreDeNoeuds << endl;
            afficherGrille(2);
            changeTour();
            enCours = !grille.verifierGagnant(gagnant);
        }
        if(grille.tablePleine()) {gagnant = 0; break;}
    }

    if(gagnant == 0)
    {
        reinitialiserJeu();
    }

    grille.colorierGagnant();
    afficherGrille();
    delay(1000);
    afficherGagnantAI(3);
    afficherMenuPrincipal();
}

int Jeu::choixDifficulte()
{
    ALLEGRO_BITMAP* fenetreChoix = al_load_bitmap("images/poplevel.png");
    ALLEGRO_BITMAP* choixFacile = al_load_bitmap("images/poplevel1.png");
    ALLEGRO_BITMAP* choixMoyen = al_load_bitmap("images/poplevel2.png");
    ALLEGRO_BITMAP* choixDifficile = al_load_bitmap("images/poplevel3.png");

    ALLEGRO_SAMPLE* survolerBouton = al_load_sample("sounds/button_hover.wav");

    bool sound_bool1 = true;
    bool sound_bool2 = true;
    bool sound_bool3 = true;

    al_draw_bitmap(fenetreChoix,0,0,0);
    al_flip_display();
    while(enCours)
    {
        al_wait_for_event(queue,&evenement);
        if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            int x , y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if (x > 465 && x < 675)
            {
                if (y > 280 && y < 345)
                {
                    al_draw_bitmap(choixFacile,0,0,0);
                    al_flip_display();
                    if(sound_bool1 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = false;
                        sound_bool2 = true;
                        sound_bool3 = true;
                    }
                }

                if (y > 360 && y < 430)
                {
                    al_draw_bitmap(choixMoyen,0,0,0);
                    al_flip_display();
                    if(sound_bool2 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = true;
                        sound_bool2 = false;
                        sound_bool3 = true;
                    }
                }

                if (y > 440 && y < 505)
                {
                    al_draw_bitmap(choixDifficile,0,0,0);
                    al_flip_display();
                    if(sound_bool3 == true)
                    {
                        al_reserve_samples(1);
                        al_play_sample(survolerBouton, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        sound_bool1 = true;
                        sound_bool2 = true;
                        sound_bool3 = false;
                    }
                }
            }

            else
                {
                    al_draw_bitmap(fenetreChoix,0,0,0);
                    al_flip_display();
                    sound_bool1 = true;
                    sound_bool2 = true;
                    sound_bool3 = true;
                }
        }
        if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int x , y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if (x > 465 && x < 675)
            {
                if (y > 280 && y < 345)
                {
                    return facile;
                }
                if (y > 360 && y < 430)
                {
                    return moyen;
                }
                if (y > 440 && y < 505)
                {
                    return difficile;
                }
            }
        }

        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);
    }
}

void Jeu::afficherGagnant()
{
    ALLEGRO_BITMAP* rougegagne = al_load_bitmap("images/redwins.png");
    ALLEGRO_BITMAP* jaunegagne = al_load_bitmap("images/yellowwins.png");
    ALLEGRO_BITMAP* exequo = al_load_bitmap("images/draw.png");

    ALLEGRO_SAMPLE *gagnerEffet = al_load_sample("sounds/win.wav");
    ALLEGRO_SAMPLE *egaliteEffet = al_load_sample("sounds/draw.wav");

/// sound playing
    if (gagnant == 1)
    {
        al_reserve_samples(1);
        al_play_sample(gagnerEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    if (gagnant == 2)
    {
        al_reserve_samples(1);
        al_play_sample(gagnerEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    if (gagnant == 0)
    {
        al_reserve_samples(1);
        al_play_sample(egaliteEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

        while(!enCours)
            {
                al_wait_for_event(queue, &evenement);
                if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
                {
                    int x , y;
                    x=evenement.mouse.x;
                    y=evenement.mouse.y;
                }

                if (gagnant == 1)
                {
                    al_draw_bitmap(rougegagne, 0, 0, 0);
                }

                if (gagnant == 2)
                {
                    al_draw_bitmap(jaunegagne, 0 ,0, 0);
                }

                if (gagnant == 0)
                {
                    al_draw_bitmap(exequo, 0, 0, 0);
                }

                if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                {
                    int x, y;
                    x = evenement.mouse.x;
                    y = evenement.mouse.y;

                    if (y > 485 && y < 535)
                    {
                        if (x > 315 && x < 370)
                        {
                            reinitialiserJeu();
                            joueurVSjoueur();
                        }
                        if (x > 745 && x < 795)
                        {
                            afficherMenuPrincipal();
                        }
                    }
                }
                if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    exit(0);
                al_flip_display();

            }
    }

Table Jeu::alphaBeta(int profondeurDynamique, int tour, int profondeurVoulue, Table Tablea, Table Tableb)
{
    /// Si la grille est pleine, retourner l'utilité correspondant a l'égalité
     if(grille.tablePleine())
    {
        grille.setPoids(grille.utilite());
    }
    /// Si on a un gagnant
    else if(grille.verifierGagnant(gagnant))
    {
        /// Si le gagnant est Max, retourner l'utilité moins la profondeur (amélioration)
        if (gagnant == 1)
        {
            grille.setPoids(grille.utilite() - profondeurDynamique);
        }
        /// Si le gagnant est Min, retourner l'utilité plus la profondeur (amélioration)
        else if(gagnant == 2)
        {
            grille.setPoids(grille.utilite() + profondeurDynamique);
        }
        return grille;
    }
    /// Si la profondeur est nille
    else if (profondeurDynamique == 0)
    {
        /// Appeler la fonction heuristique
        grille.setPoids(grille.fonctionHeuristique());
        return grille;
    }
    else
    {
        Table Tablev, copieGrille = grille;

        /// Si c'est le tour de Max
        if (tour == 1)
        {
            Tablev.setPoids(-10000);
            /// Génération des successeurs
            vector <Table> listNoeuds = grille.genereSuccesseurs(2);
            for (int i = 0 ; i < listNoeuds.size(); i++)
            {
                nombreDeNoeuds++;
                grille = listNoeuds[i];
                /// Appel récursif de la méthode alphaBeta
                Tablev = Tablev.maxTable(alphaBeta(profondeurDynamique - 1, tour+1, profondeurVoulue, Tablea, Tableb));
                /// Phase de l'alphaBeta pruning
                if (Tablev.getPoids() > Tableb.getPoids())
                    {
                        if (profondeurDynamique == profondeurVoulue)
                        {
                            return Tablev;
                        }
                        copieGrille.setPoids(Tablev.getPoids());
                        Tablev = copieGrille;
                        return Tablev;
                    }

                Tablea=Tablev.maxTable(Tablea);
            }

            if (profondeurDynamique == profondeurVoulue)
            {
                return Tablev;
            }
            copieGrille.setPoids(Tablev.getPoids());
            Tablev = copieGrille;
            return Tablev;
        }

        else
            /// Si c'est le tour de Min
            {
                Tablev.setPoids(10000);
            /// Génération des successeurs
                vector <Table> listNoeuds = grille.genereSuccesseurs(1);
                for (int i = 0 ; i < listNoeuds.size(); i++)
                {
                    nombreDeNoeuds++;
                    grille = listNoeuds[i];
                    /// Appel récursif de la méthode alphaBeta
                    Tablev = Tablev.minTable(alphaBeta(profondeurDynamique - 1, tour-1, profondeurVoulue, Tablea, Tableb));
                    /// Phase de l'alphaBeta pruning
                    if (Tablev.getPoids() < Tablea.getPoids())
                        {
                            if (profondeurDynamique == profondeurVoulue)
                            {
                                return Tablev;
                            }
                            copieGrille.setPoids(Tablev.getPoids());
                            Tablev = copieGrille;
                            return Tablev;
                        }
                    Tableb=Tablev.maxTable(Tableb);
                }
                grille = copieGrille;

                if (profondeurDynamique == profondeurVoulue)
                {
                    return Tablev;
                }
                copieGrille.setPoids(Tablev.getPoids());
                Tablev = copieGrille;
                return Tablev;
            }
        }
}

void Jeu::alphaBetaInterface()
{

    Table Tablea, Tableb;
    Tablea.setPoids(-10000);
    Tableb.setPoids(10000);
    int difficulte = choixDifficulte();

    ALLEGRO_SAMPLE *valid_move_sound = al_load_sample("sounds/valid_move.wav");

    while(enCours)
    {
        if(tour == 1)
        {
            al_wait_for_event(queue,&evenement);
            if(evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
            int x,y;
            x=evenement.mouse.x;
            y=evenement.mouse.y;

            if(placerPion(tour,x,y))
            {
                changeTour();
            }
            else if (x>=20 && x <= 70 && y >= 555 && y <= 600)
            {
                interfaceParametre(3);
            }
        }

        if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(0);
        enCours = !grille.verifierGagnant(gagnant);
        afficherGrille(2);
        }
        else
        {
            nombreDeNoeuds = 0;
            changeTour();
            grille = alphaBeta(difficulte, tour, difficulte, Tablea, Tableb);
            changeTour();
            if (difficulte == facile)
            {
                delay(500);
            }
            if (difficulte == moyen)
            {
                delay(500);
            }
            if (difficulte == difficile)
            {
                delay(700);
            }
            al_reserve_samples(1);
            al_play_sample(valid_move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            cout << "Nombre de noeuds parcourus par l'algo Alphabeta :" << nombreDeNoeuds << endl;
            afficherGrille(2);
            changeTour();
            enCours = !grille.verifierGagnant(gagnant);
        }
        if(grille.tablePleine()) {gagnant = 0 ; break;}
    }
    if(gagnant == 0)
    {
        reinitialiserJeu();
    }
    grille.colorierGagnant();
    afficherGrille();
    delay(1000);
    afficherGagnantAI(3);
    afficherMenuPrincipal();
}

void Jeu::afficherGagnantAI(int modeJeu)
{
    ALLEGRO_BITMAP* aigagne = al_load_bitmap("images/gameover.png");
    ALLEGRO_BITMAP* joeurgagne = al_load_bitmap("images/youwin.png");
    ALLEGRO_BITMAP* exequo = al_load_bitmap("images/draw.png");

    ALLEGRO_SAMPLE *gagnerEffet = al_load_sample("sounds/win.wav");
    ALLEGRO_SAMPLE *egaliteEffet = al_load_sample("sounds/draw.wav");
    ALLEGRO_SAMPLE *perdreEffet = al_load_sample("sounds/lose.wav");

    enCours = false ;
    /// sound playing
    if (gagnant == 1)
    {
        al_reserve_samples(1);
        al_play_sample(gagnerEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    if (gagnant == 2)
    {
        al_reserve_samples(1);
        al_play_sample(perdreEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    if (gagnant == 0)
    {
        al_reserve_samples(1);
        al_play_sample(egaliteEffet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    while(!enCours)
            {
                al_wait_for_event(queue, &evenement);
                if (evenement.type == ALLEGRO_EVENT_MOUSE_AXES)
                {
                    int x , y;
                    x=evenement.mouse.x;
                    y=evenement.mouse.y;
                }
                if (gagnant == 1)
                {
                    al_draw_bitmap(joeurgagne,0,0,0);
                }
                if (gagnant == 2)
                {
                    al_draw_bitmap(aigagne,0,0,0);
                }
                if (gagnant == 0)
                {
                    al_draw_bitmap(exequo, 0, 0, 0);
                }

                if (evenement.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                {
                    int x , y;
                    x = evenement.mouse.x;
                    y = evenement.mouse.y;

                    if (y > 485 && y < 535)
                    {
                        if (x > 315 && x < 370)
                        {
                            if (modeJeu == 2)
                            {
                                reinitialiserJeu();
                                minMaxInterface();
                            }
                            if (modeJeu == 3)
                            {
                                reinitialiserJeu();
                                alphaBetaInterface();
                            }
                        }
                        if (x > 745 && x < 795)
                        {
                            afficherMenuPrincipal();
                        }
                    }
                }
                if (evenement.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    exit(0);
                al_flip_display();

            }
    }

Jeu::~Jeu()
{
    al_destroy_display(fenetre);
    al_destroy_bitmap(imageGrille);
    al_destroy_bitmap(pionJaune);
    al_destroy_bitmap(pionRouge);
    al_destroy_bitmap(pionVert);
    al_destroy_bitmap(joueur1);
    al_destroy_bitmap(joueur2);
    al_destroy_bitmap(joueur);
    al_destroy_bitmap(intelligenceA);
    al_destroy_bitmap(fenetreParametre);
    al_destroy_bitmap(menuPrincipal);
    al_destroy_bitmap(icone);
}

