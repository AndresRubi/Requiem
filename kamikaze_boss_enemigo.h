#ifndef KAMIKAZE_BOSS_ENEMIGO_H
#define KAMIKAZE_BOSS_ENEMIGO_H
#include "enemigos.h"

class Kamikaze_Boss_Enemigo : public Enemigos
{
    public:
        Kamikaze_Boss_Enemigo(int x,int y,float  *passed_CameraX, float *passed_CameraY, SDL_Setup *passed_SDL_Setup, string direcion_enemigo);
        virtual ~Kamikaze_Boss_Enemigo();

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
        int x,y;
        string tipoEnemigo;
        string getID(){return tipoEnemigo;}
        CSprite* GetEnemy() {return enemy;}
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

#endif // KAMIKAZE_BOSS_ENEMIGO_H
