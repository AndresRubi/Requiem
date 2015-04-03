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
        void UpdateCreator();


        int GetNivel(){return nivel;}
        int GetVida(){return vida;}
        int GetAtaque(){return ataque;}
        bool GetEstado(){return VivoMuerto;}

        void SubirNivel(int ExperienciaEnemiga);
        void SetVida(int ataqueEnemigo);
        void SetEstatus();
        void SetVidaNivel(int porNivel);
        void SetAtaqueNivel(int porNivel);
        bool VivoMuerto;

    protected:
    private:
        int vida, ataque,experiencia,nivel;
        CEnviroment *Enviroment;
//        Enemigos *Contra_Enemigos;
//        Enemigos* CEnemigos;

        void UpdateCreatorControls();
        void UpdateStats();
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
