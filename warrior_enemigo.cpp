#include "warrior_enemigo.h"

Warrior_Enemigo::Warrior_Enemigo(int x, int y, float  *passed_CameraX, float *passed_CameraY, SDL_Setup *passed_SDL_Setup, string direcion_enemigo)
{
    //ctor
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    this->x=x;
    this->y=y;

    direcion_enemigo="warrior";
    csdl_setup = passed_SDL_Setup;

    enemy= new CSprite(csdl_setup->GetRenderer(),"data/enemigos/warrior_f.png",x,y,32,36,CameraX,CameraY,CCollisionRectangle(0,0,28,36));
//    player = new CSprite(csdl_setup->GetRenderer(),"data/players/healer_m.png",96,144,32,36,CameraX,CameraY,CCollisionRectangle(80,126,28,36));
    enemy->SetUpAnimation(3,4);

    Follow =false;
    timeCheck = SDL_GetTicks();
    distance = 0;
    stopAnimation = false;
    movimientoPrueba=0;
    direccion=0;
    dir_rand=0;
    frame=0;
    tipoEnemigo="warrior";



    enemigoVivoMuerto=false;
    vidaEnemy = 10;
    ataqueEnemy =2;
    experienciaEnemy=10;
}

Warrior_Enemigo::~Warrior_Enemigo()
{
    //dtor
    delete enemy;
}

///
void Warrior_Enemigo::SetVidaEnemy(int ataquePersonaje)
{
    vidaEnemy-=ataquePersonaje;
    cout<<vidaEnemy<<endl;
    if(vidaEnemy<=0)
    {
        enemigoVivoMuerto=true;
    }

}

void Warrior_Enemigo::SetAtaqueEnemy()
{
    ataqueEnemy=2;
}

void Warrior_Enemigo::SetExperiencia()
{
    ataqueEnemy=2;
}
///


int Warrior_Enemigo::GetX()
{
    return x;
}

int Warrior_Enemigo::GetY()
{
    return y;
}


void Warrior_Enemigo::Draw()
{
    enemy->Draw();
}

void Warrior_Enemigo::UpdateEnemyMovement()
{
            if(direccion==DOWN)
                enemy->SetY(enemy->GetY()+ 0.1);

            else if(direccion == UP)
                enemy->SetY(enemy->GetY()-0.1);

            else if(direccion == LEFT)
                enemy->SetX(enemy->GetX()-0.1);

            else if(direccion == RIGHT)
                enemy->SetX(enemy->GetX()+ 0.1);

}

void Warrior_Enemigo::UpdateEnemyAnimation()
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


void Warrior_Enemigo::Update()
{
    UpdateEnemyAnimation();
    UpdateEnemyMovement();
}

