#include "arquero_enemigo.h"

Arquero_Enemigo::Arquero_Enemigo(int x,int y,float  *passed_CameraX, float *passed_CameraY, SDL_Setup *passed_SDL_Setup, string direcion_enemigo)
{
    //ctor
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    this->x=x;
    this->y=y;
    direcion_enemigo = "archer";
    csdl_setup = passed_SDL_Setup;

    enemy= new CSprite(csdl_setup->GetRenderer(),"data/enemigos/ranger_f.png",x,y,32,36,CameraX,CameraY,CCollisionRectangle(0,0,28,36));

    enemy->SetUpAnimation(3,4);


    tipoEnemigo="archer";
    Follow =false;
    timeCheck = SDL_GetTicks();
    distance = 0;
    stopAnimation = false;
    movimientoPrueba=0;
    direccion=0;
    dir_rand=0;
    frame=0;

    enemigoVivoMuerto=false;
    vidaEnemy = 8;
    ataqueEnemy =1;
    experienciaEnemy=2;

}

Arquero_Enemigo::~Arquero_Enemigo()
{
    //dtor
    delete enemy;
}

///
void Arquero_Enemigo::SetVidaEnemy(int ataquePersonaje)
{
    vidaEnemy-=ataquePersonaje;
    cout<<vidaEnemy<<endl;
    if(vidaEnemy<=0)
    {
        enemigoVivoMuerto=true;
    }

}

void Arquero_Enemigo::SetAtaqueEnemy()
{
    ataqueEnemy=2;
}

void Arquero_Enemigo::SetExperiencia()
{
    experienciaEnemy=2;
}
///


int Arquero_Enemigo::GetX()
{
    return x;
}

int Arquero_Enemigo::GetY()
{
    return y;
}

void Arquero_Enemigo::Draw()
{
        enemy->Draw();
}

void Arquero_Enemigo::UpdateEnemyMovement()
{
            if(direccion==DOWN)
                enemy->SetY(enemy->GetY()+ 0.2);

            else if(direccion == UP)
                enemy->SetY(enemy->GetY()-0.2);

            else if(direccion == LEFT)
                enemy->SetX(enemy->GetX()-0.2);

            else if(direccion == RIGHT)
                enemy->SetX(enemy->GetX()+ 0.2);

}

void Arquero_Enemigo::UpdateEnemyAnimation()
{
        if(frame%500==0)
        dir_rand = rand() % 4 + 1;
        movimientoPrueba = dir_rand;
           switch(movimientoPrueba)
            {
                case 1:
                {
//                abajo
                    direccion=DOWN;
                    enemy->PlayAnimation(0,2,2 ,125);
                    break;
                }

                case 2:
                {
//                derecha
                    direccion=RIGHT;
                    enemy->PlayAnimation(0,2,1 ,125);
                    break;
                }

                case 3:
                {
//                izquierda
                    direccion=LEFT;
                    enemy->PlayAnimation(0,2,3 ,125);
                    break;
                }

                case 4:
                {
//                arriba
                    direccion=UP;
                    enemy->PlayAnimation(0,2,0 ,125);

                    break;
                }

            }
            frame++;




}


void Arquero_Enemigo::Update()
{
    if(!enemigoVivoMuerto)
    {
        UpdateEnemyAnimation();
        UpdateEnemyMovement();
    }

}

