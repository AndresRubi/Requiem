#include "maincharacter.h"

MainCharacter::MainCharacter(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY,float *passed_CameraX,float *passed_CameraY, CEnviroment * passed_Enviroment)
{
    //ctor
    Enviroment = passed_Enviroment;

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;


    csdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    player = new CSprite(csdl_setup->GetRenderer(),"data/players/healer_m.png",320,200,32,36,CameraX,CameraY,CCollisionRectangle(305,183,28,36));
    player->SetUpAnimation(3,4);
    player->SetOrigin(player->GetWidth()/2, player->GetHight()/2);

    Follow =false;
    timeCheck = SDL_GetTicks();
    distance = 0;
    stopAnimation = false;
    VivoMuerto=false;
    vida=50;
    nivel=1;
    ataque = 5;
    experiencia = 0;
}

MainCharacter::~MainCharacter()
{
    //dtor
    delete player;
}

void MainCharacter::Draw()
{
    player->DrawSteady();
}

int MainCharacter::SetAtaque(int nivel)
{
    ataque=1;
}

int MainCharacter::SetVida(int ataqueEnemigo)
{
    vida-=ataqueEnemigo;
}
void MainCharacter::UpdateAnimation()
{
            float angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
            angle = (angle * (180/3.14)) + 180;

//            cout<<angle<<endl;

//TUTORIAL 22 MINUTO 5

            if(!stopAnimation)
            {
                if(angle > 45 && angle <= 135)
                {
                    //                DOWN
                    if(distance > 15)
                        player->PlayAnimation(0,2,2 ,125);
                    else
                        player->PlayAnimation(1,1,2 ,125);
//                    cout<<'D'<<endl;
                }
                else if(angle >135 && angle <= 225)
                {
    //                LEFT
                    if(distance > 15 )
                        player->PlayAnimation(0,2,3 ,125);
                    else
                        player->PlayAnimation(1,1,3 ,125);
//                    cout<<'L'<<endl;
                }
                else if(angle >225 && angle <= 315)
                {
                                    //UP
                    if(distance > 15)
                        player->PlayAnimation(0,2,0 ,125);
                    else
                        player->PlayAnimation(1,2,0 ,125);
//                    cout<<'U'<<endl;

                }
                else if((angle <= 360 && angle > 315 ) || (angle >= 0 && angle<= 45))
                {
                    //                 RIGHT
                    if(distance > 15  )
                        player->PlayAnimation(0,2,1 ,125);
                    else
                        player->PlayAnimation(1,1,1 ,125);
//                    cout<<'R'<<endl;

                }
            }

}

void MainCharacter::UpdateControls()
{
            if(csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
            {
                if(csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
                {
                    Follow_Point_X = *CameraX - *MouseX + 320;
                    Follow_Point_Y = *CameraY - *MouseY + 200;
                    Follow=true;
                }
            }
//            cada medio segundo el personaje se va a estar moviendo
int check = timeCheck + 10;
            if(check < SDL_GetTicks())
            {

//////                movimiento con teclado
//                if(csdl_setup->GetMainEvent()-> type)
//             {
//                if(csdl_setup->GetMainEvent()-> type == SDL_KEYDOWN)
//                {
//                    switch (csdl_setup->GetMainEvent()->key.keysym.sym)
//                    {
//                        case SDLK_a:
//                        {
//                            player->SetX(player->GetX() - 1);
//                            break;
//                        }
//                        case SDLK_s:
//                        {
//                            player->SetY(player->GetY() + 1);
//                            break;
//                        }
//                        case SDLK_w:
//                        {
//                            player->SetY(player->GetY() - 1);
//                            break;
//                        }
//                        case SDLK_d:
//                        {
//                            player->SetX(player->GetX() + 1);
//                            break;
//                        }
//                    }
//                }
//             }

////////                MOVER CON MOUSE
                 distance= GetDistance(*CameraX,*CameraY, Follow_Point_X,Follow_Point_Y);

                if(distance == 0 )
                    stopAnimation = true;
                else
                    stopAnimation=false;

                if(distance > 15 && Follow)
                {
                    bool colliding = false;
                    for(int i = 0 ; i<Enviroment->GetTrees().size(); i++)
                    {
                        if(player->isColliding(Enviroment->GetTrees()[i]->GetTrunk() ->GetCollisionRect()))
                        {
                            if(*CameraX > Follow_Point_X)
                            {
                                *CameraX = *CameraX +5;
                            }
                            if(*CameraX < Follow_Point_X)
                            {
                                *CameraX = *CameraX - 5;
                            }

                            if(*CameraY > Follow_Point_Y)
                            {
                                *CameraY = *CameraY +5;
                            }
                            if(*CameraY < Follow_Point_Y)
                            {
                                *CameraY = *CameraY - 5;
                            }

                            Follow_Point_X = *CameraX;
                            Follow_Point_Y = *CameraY;
                            distance = 0 ;
                            Follow=false;

                            colliding = true;
                        }
                    }

                    ///prueba colision con enemigos
                    for(int x=0 ; x< Enviroment->GetEnemigos().size(); x++)
                    {
                        if(player->isColliding(Enviroment->GetEnemigos()[x]->GetEnemy()->GetCollisionRect()))
                        {
                            if(*CameraX > Follow_Point_X)
                            {
                                *CameraX = *CameraX +5;
                            }
                            if(*CameraX < Follow_Point_X)
                            {
                                *CameraX = *CameraX - 5;
                            }

                            if(*CameraY > Follow_Point_Y)
                            {
                                *CameraY = *CameraY +5;
                            }
                            if(*CameraY < Follow_Point_Y)
                            {
                                *CameraY = *CameraY - 5;
                            }


                            Enviroment->GetEnemigos()[x]->SetVidaEnemy(2);
//                            SetVida(1);
                            cout<<GetVida()<<endl;
                            if(vida<=0)
                            {
                                VivoMuerto=true;
                                cout<<"muerto"<<endl;
                            }
                            Follow_Point_X = *CameraX;
                            Follow_Point_Y = *CameraY;
                            distance = 0 ;
                            Follow=false;
                            cout<<"colision con enemigo"<<endl;
                            colliding = true;
                        }
                    }
                    ///fin de prueba enemigos
                    if(!colliding)
                    {
                        if(*CameraX != Follow_Point_X)
                        {
                            *CameraX = *CameraX - (((*CameraX  - Follow_Point_X) /distance) * 1.5f);
                        }

                        if(*CameraY != Follow_Point_Y)
                        {
                            *CameraY =  *CameraY - (((*CameraY - Follow_Point_Y) /distance) * 1.5f);
                        }
                    }


                }else
                    Follow=false;

                timeCheck = SDL_GetTicks();

            }
}

void MainCharacter::Update()
{
    UpdateAnimation();
    UpdateControls();

//    for(int i = 0 ; i<Enviroment->GetTrees().size(); i++)
//    {
//        if(player->isColliding(Enviroment->GetTrees()[i]->GetTrunk() ->GetCollisionRect()))
//        {
//            cout<<"colliding iwth a tree"<<endl;
//        }
//    }
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
    double DifferenceX = X1-X2;
    double DifferenceY = Y1-Y2;
    double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
    return distance;

}
