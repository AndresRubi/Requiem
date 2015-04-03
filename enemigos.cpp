#include "enemigos.h"
Enemigos::Enemigos()
{

}
Enemigos::Enemigos(int x,int y,float  *passed_CameraX, float *passed_CameraY, SDL_Setup *passed_SDL_Setup, string direcion_enemigo)
{
    //ctor
//    Enviroment = passed_Enviroment;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
    csdl_setup = passed_SDL_Setup;
    this->x=x;
    this->y=y;
}

Enemigos::~Enemigos()
{
    //dtor
    delete enemy;

}

void Enemigos::Draw()
{
    enemy->Draw();

}

