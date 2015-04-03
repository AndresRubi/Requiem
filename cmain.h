#ifndef CMAIN_H
#define CMAIN_H

#include "sdl_setup.h"
#include "csprite.h"

#include <iostream>
#include "maincharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <math.h>
#include "cenviroment.h"
#include "enemigos.h"
#include "arquero_enemigo.h"
#include "ninja_enemigo.h"
#include "warrior_enemigo.h"

using namespace std;

class CMain
{
    public:
        CMain(int passed_ScreenWidth, int passed_ScreenHeight);
        virtual ~CMain();
        void GameLoop();



    protected:

    private:
    MainCharacter *player;
    float CameraX;
    float CameraY;

    CEnviroment* ForestArea;

    Enemigos* enemy1,*enemy2, *enemy3;

    int ScreenWidth,ScreenHeight;
    bool quit;
    SDL_Event *GMod;
    string hola;
//    CSprite* grass[4][7];

    SDL_Setup* csdl_setup;
//    bool MoveRight;
//    bool MoveUp;
//    bool MoveDown;
//    bool MoveLeft;

    int MouseX,MouseY;
};

#endif // CMAIN_H
