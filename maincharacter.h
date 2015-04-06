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
#include "SDL2/SDL_ttf.h"
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

        bool atacando;
        bool OnePressed;
        int GetNivel(){return nivel;}
        int GetVida(){return vida;}
        int GetAtaque(){return ataque;}
        bool GetEstado(){return VivoMuerto;}

        void SubirNivel(int ExperienciaEnemiga);
        void SetVida(int ataqueEnemigo);
        void SetEstatus();
        void SetVidaNivel(int porNivel);
        void SetAtaqueNivel(int porNivel);
        bool VivoMuerto,Ganar;
        void UpdateHealthBar();
        void UpdatePantallaWin(bool Ganar);
        void UpdatePantallaMuerte(bool VivoMuerto);

    protected:
    private:
        void initTTF();
        void showTTF(int nivel);
        TTF_Font* Sans;
        SDL_Color White;
        Mix_Chunk *hit,*killEnemy,*killXultur,*contactXultur;
        Mix_Music *loose,*win;
        bool XulturMessage;

        int vida, ataque,experiencia,nivel;
        CEnviroment *Enviroment;
//        Enemigos *Contra_Enemigos;
//        Enemigos* CEnemigos;
        int w,h;
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


        int vidaLvl1,vidaLvl2,vidaLvl3,vidaLvl4,vidaLvl5;
        int por1,por2,por3,por4,po5;
        int vidaActual;
        int passedNivel;

        int porcentual;


        SDL_Texture *healthBars,*healthBarActual,*deathScreen,*winScreen;
        SDL_Rect rect_bar,rect_deatScreen,rect_winScreen;


};

#endif // MAINCHARACTER_H
