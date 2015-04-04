#include "xultur_boss_enemigo.h"

Xultur_Boss_Enemigo::Xultur_Boss_Enemigo(int x,int y,float  *passed_CameraX, float *passed_CameraY, SDL_Setup *passed_SDL_Setup, string direcion_enemigo)
{
   CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    this->x=x;
    this->y=y;
    direcion_enemigo = "archer";
    csdl_setup = passed_SDL_Setup;

    enemy= new CSprite(csdl_setup->GetRenderer(),"data/sprites/enemies/xultur_boss/xultur_walk.png",x,y,64,64,CameraX,CameraY,CCollisionRectangle(0,0,60,64));

    enemy->SetUpAnimation(9,4);


    tipoEnemigo="xultur";
    Follow =false;
    timeCheck = SDL_GetTicks();
    distance = 0;
    stopAnimation = false;
    movimientoPrueba=0;
    direccion=0;
    dir_rand=0;
    frame=0;

    enemigoVivoMuerto=false;
    vidaEnemy = 40;
    ataqueEnemy =10;
    experienciaEnemy=50;

}

Xultur_Boss_Enemigo::~Xultur_Boss_Enemigo()
{
    //dtor
    delete enemy;
}

///
void Xultur_Boss_Enemigo::SetVidaEnemy(int ataquePersonaje)
{
    vidaEnemy-=ataquePersonaje;
    cout<<vidaEnemy<<endl;
    if(vidaEnemy<=0)
    {
//        enemigoVivoMuerto=true;
    }

}

void Xultur_Boss_Enemigo::AnimacionMuerte()
{
    if(vidaEnemy<=0)
    {
    enemy= new CSprite(csdl_setup->GetRenderer(),"data/sprites/enemies/xultur_boss/xultur_fall.png",x,y,64,64,CameraX,CameraY,CCollisionRectangle(0,0,60,64));
    enemy->SetUpAnimation(6,1);
    enemy->PlayAnimation(0,2,0 ,50);
    }
}

void Xultur_Boss_Enemigo::SetAtaqueEnemy()
{
    ataqueEnemy=2;
}

void Xultur_Boss_Enemigo::SetExperiencia()
{
    experienciaEnemy=2;
}
///


int Xultur_Boss_Enemigo::GetX()
{
    return x;
}

int Xultur_Boss_Enemigo::GetY()
{
    return y;
}

void Xultur_Boss_Enemigo::Draw()
{
        enemy->Draw();
}

void Xultur_Boss_Enemigo::UpdateEnemyMovement()
{
            if(direccion==DOWN)
                enemy->SetY(enemy->GetY()+ 0.2);

            else if(direccion == UP)
                enemy->SetY(enemy->GetY()-0.2);

            else if(direccion == RIGHT)
                enemy->SetX(enemy->GetX()-0.2);

            else if(direccion == LEFT)
                enemy->SetX(enemy->GetX()+ 0.2);

}

void Xultur_Boss_Enemigo::UpdateEnemyAnimation()
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


void Xultur_Boss_Enemigo::Update()
{
    if(!enemigoVivoMuerto)
    {
        UpdateEnemyAnimation();
        UpdateEnemyMovement();
    }

}
