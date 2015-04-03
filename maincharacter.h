#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include "sdl_setup.h"
#include "csprite.h"

//#include "enemigos.h"
#include "cenviroment.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <math.h>


class MainCharacter
{
    public:

        MainCharacter(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY,float *CameraX,float *CameraY, CEnviroment * passed_Enviroment);
        virtual ~MainCharacter();

        double GetDistance(int X1, int Y1, int X2, int Y2);
        void Draw();
        void Update();

        int vida, ataque,experiencia,nivel;
        int GetVida(){return vida;}
        int GetAtaque(){return ataque;}
        bool GetEstado(){return VivoMuerto;}

        int SetVida(int ataqueEnemigo);
        int SetAtaque(int nivel);
        bool VivoMuerto;

    protected:
    private:

        CEnviroment *Enviroment;
//        Enemigos *Contra_Enemigos;
//        Enemigos* CEnemigos;
        void UpdateAnimation();
        void UpdateControls();

        int *MouseX, *MouseY;
        float *CameraX;
        float *CameraY;
        SDL_Setup* csdl_setup;

        CSprite *player;
        int timeCheck;
        int Follow_Point_X,Follow_Point_Y;
        bool Follow;
        float distance;
        bool stopAnimation;




};

#endif // MAINCHARACTER_H
