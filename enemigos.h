#ifndef ENEMIGOS_H
#define ENEMIGOS_H


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "sdl_setup.h"
#include "csprite.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <fstream>

class Enemigos
{
    public:

        Enemigos();
        Enemigos(int x, int y ,float  *CameraX, float *CameraY,SDL_Setup *passed_SDL_Setup, string direcion_enemigo);
        virtual ~Enemigos();
//        double GetDistance(int X1, int Y1, int X2, int Y2);
//        CSprite *GetEnemigo(){return enemy;}

        SDL_Setup* csdl_setup;
        CSprite *enemy;
        float *CameraX;
        float *CameraY;
        int movimientoPrueba;
        int x,y;

        int vida,ataque,experiencia;

        virtual int SetVidaEnemy(int ataquePersonaje)=0;
        virtual int SetAtaqueEnemy()=0;
        virtual int SetExperiencia()=0;


        bool enemigoVivoMuerto;
        virtual bool EnemigoEliminado()=0;
        virtual int GetVidaEnemy()=0;
        virtual int GetAtaqueEnemy()=0;
        virtual int GetExpecienciaEnemy()=0;


        virtual int GetX()=0;
        virtual int GetY()=0;
        virtual string getID()=0;
        virtual CSprite *GetEnemy()=0;
        virtual void Draw()=0;
        virtual void Update()=0;
        virtual void UpdateEnemyAnimation()=0;
        virtual void UpdateEnemyMovement()=0;

        int timeCheck;
        bool Follow;
        float distance;
        bool stopAnimation;

    protected:
    private:




};

#endif // ENEMIGOS_H
