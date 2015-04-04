#ifndef CENVIROMENT_H
#define CENVIROMENT_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "sdl_setup.h"
#include "csprite.h"
#include <math.h>
#include <iostream>
#include "tree.h"

#include "enemigos.h"
#include "arquero_enemigo.h"
#include "warrior_enemigo.h"
#include "ninja_enemigo.h"
#include "xultur_boss_enemigo.h"
#include "kamikaze_boss_enemigo.h"


#include <vector>
#include <fstream>
#include <string>
#include <sstream>
class CEnviroment
{
    public:
        CEnviroment(int ScreenWith, int ScreenHeight, float  *CameraX, float *CameraY,SDL_Setup *csdl_setup);
        virtual ~CEnviroment();

        void DrawBack();
        void DrawFront();
        void Update();
        void SaveToFile();
        void LoadFromFile();
        bool exitLoop;

        enum ModeType
        {
            Gameplay,
            LevelCreation
        };
        vector<Tree*> GetTrees(){return trees;}
        vector<Enemigos*> GetEnemigos(){return enemies;}


    protected:
    private:
        int Mode;
        CSprite* grass[4][7];
        vector<Tree*> trees;
        vector<Enemigos*> enemies;
//        Enemigos enemy1,enemy2,enemy3;
//        Enemigos *contrario;


        bool OnePressed;
        SDL_Setup *csdl_setup;
        float *CameraX,*CameraY;

};

#endif // CENVIROMENT_H
