#ifndef NINJA_ENEMIGO_H
#define NINJA_ENEMIGO_H
#include "enemigos.h"

class Ninja_Enemigo : public Enemigos

{
    public:
        Ninja_Enemigo(int x,int y,float  *CameraX, float *CameraY,SDL_Setup *passed_SDL_Setup, string direcion_enemigo);
        virtual ~Ninja_Enemigo();

        void Draw();
        void Update();

        enum DIRECTION{DOWN,RIGHT,LEFT,UP};
        int direccion,dir_rand;

        int GetX();
        int GetY();


        int vidaEnemy,ataqueEnemy,experienciaEnemy;
        int SetVidaEnemy(int ataquePersonaje);
        int SetAtaqueEnemy();
        int SetExperiencia();

        bool enemigoVivoMuerto;
        bool EnemigoEliminado(){return enemigoVivoMuerto;}
        int GetVidaEnemy(){return vidaEnemy;}
        int GetAtaqueEnemy(){return ataqueEnemy;}
        int GetExpecienciaEnemy(){return experienciaEnemy;}




    protected:
    private:
        string tipoEnemigo;
        string getID(){return tipoEnemigo;}
        CSprite* GetEnemy() {return enemy;}
        int x,y;
        SDL_Setup* csdl_setup;
        CSprite *enemy;
        float *CameraX;
        float *CameraY;
        int movimientoPrueba;
        int tiempo,temp,frame;

        void UpdateEnemyMovement();
        void UpdateEnemyAnimation();

        int timeCheck;
        bool Follow;
        float distance;
        bool stopAnimation;
};

#endif // NINJA_ENEMIGO_H
