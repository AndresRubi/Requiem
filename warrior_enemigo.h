#ifndef WARRIOR_ENEMIGO_H
#define WARRIOR_ENEMIGO_H
#include "enemigos.h"

class Warrior_Enemigo : public Enemigos
{
    public:
        Warrior_Enemigo(int x,int y,float  *CameraX, float *CameraY,SDL_Setup *passed_SDL_Setup, string direcion_enemigo);
        virtual ~Warrior_Enemigo();

        void Draw();
        void Update();

        enum DIRECTION{DOWN,RIGHT,LEFT,UP};
        int direccion,dir_rand;

        int GetX();
        int GetY();


        int vidaEnemy,ataqueEnemy,experienciaEnemy;
        void SetVidaEnemy(int ataquePersonaje);
        void SetAtaqueEnemy();
        void SetExperiencia();

        bool enemigoVivoMuerto;
        bool EnemigoEliminado(){return enemigoVivoMuerto;}
        int GetVidaEnemy(){return vidaEnemy;}
        int GetAtaqueEnemy(){return ataqueEnemy;}
        int GetExpecienciaEnemy(){return experienciaEnemy;}


    protected:
    private:
    void AnimacionMuerte(){return;}
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

#endif // WARRIOR_ENEMIGO_H
