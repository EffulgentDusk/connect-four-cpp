/*
 * Connect Four
 * MIT License, Copyright 2018 Loukmane Maada, Soukaina Moumou & Anas Limouri
 */
#include <iostream>
#include "Table.h"
#include "Jeu.h"
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

int main()
{
    ///FreeConsole();
    Jeu game;
    game.commencerJeu();
}
