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

    vida=0;
    nivel=1;
    ataque = 0;
    experiencia = 0;
    SetEstatus();

}

MainCharacter::~MainCharacter()
{
    //dtor
    delete player;
}

void MainCharacter::SetVidaNivel(int porNivel)
{
    vida=porNivel;
}
void MainCharacter::SetAtaqueNivel(int porNivel)
{
    ataque=porNivel;
}

void MainCharacter::SubirNivel(int ExperienciaEnemiga)
{
    experiencia+=ExperienciaEnemiga;
    if(experiencia > 4 )
    {
        nivel=2;
    }
    if(16 < experiencia)
    {
        nivel=3;
    }
   if(80 < experiencia)
    {
        nivel=4;
    }
    if(116 < experiencia)
    {
        nivel=5;
    }
    if(156 < experiencia)
    {
        nivel=6;
    }
}
void MainCharacter::Draw()
{
    player->DrawSteady();
}

void MainCharacter::SetEstatus()
{
    int passedNivel=nivel;
    switch(passedNivel)
    {
        case 1:
        {
            SetVidaNivel(10);
            SetAtaqueNivel(2);
            break;
        }
        case 2:
        {
            SetVidaNivel(20);
            SetAtaqueNivel(6);
            break;
        }

        case 3:
        {
            SetVidaNivel(30);
            SetAtaqueNivel(10);
            break;
        }

        case 4:
        {
            SetVidaNivel(40);
            SetAtaqueNivel(14);
            break;
        }

        case 5:
        {
            SetVidaNivel(50);
            SetAtaqueNivel(20);
            break;
        }


    }
}

void MainCharacter::SetVida(int ataqueEnemigo)
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

void MainCharacter::UpdateCreatorControls()
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


    int check = timeCheck + 10;
            if(check < SDL_GetTicks())
            {


////////                MOVER CON MOUSE
                 distance= GetDistance(*CameraX,*CameraY, Follow_Point_X,Follow_Point_Y);

                if(distance == 0 )
                    stopAnimation = true;
                else
                    stopAnimation=false;

                if(distance > 15)
                {


                        if(*CameraX != Follow_Point_X)
                        {
                            *CameraX = *CameraX - (((*CameraX  - Follow_Point_X) /distance) * 2.1f);
                        }

                        if(*CameraY != Follow_Point_Y)
                        {
                            *CameraY =  *CameraY - (((*CameraY - Follow_Point_Y) /distance) * 2.1f);
                        }




                }else
                    Follow=false;

                timeCheck = SDL_GetTicks();

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
            int check = timeCheck + 10;
            if(check < SDL_GetTicks())
            {
////////                MOVER CON MOUSE
                 distance= GetDistance(*CameraX,*CameraY, Follow_Point_X,Follow_Point_Y);

                if(distance == 0 )
                    stopAnimation = true;
                else
                    stopAnimation=false;

                if(distance > 15)
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



                    ///con ataque
//                    for(int x=0 ; x< Enviroment->GetEnemigos().size(); x++)
//                    {
//                        if(player->isColliding(Enviroment->GetEnemigos()[x]->GetEnemy()->GetCollisionRect()))
//                        {
//                            if(*CameraX > Follow_Point_X)
//                            {
//                                *CameraX = *CameraX +10;
//                            }
//                            if(*CameraX < Follow_Point_X)
//                            {
//                                *CameraX = *CameraX - 10;
//                            }
//
//                            if(*CameraY > Follow_Point_Y)
//                            {
//                                *CameraY = *CameraY +10;
//                            }
//                            if(*CameraY < Follow_Point_Y)
//                            {
//                                *CameraY = *CameraY - 10;
//                            }
//
//                            if((Enviroment->GetEnemigos()[x]->GetVidaEnemy() - GetAtaque()) < GetAtaque())
//                            {
//                                SubirNivel(Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy());
//                                SetEstatus();
//                                cout<<"nivel actual "<<GetNivel()<<endl;
//                                cout<<"vida "<<GetVida()<<endl;
//                                cout<<"Ataque "<<GetAtaque()<<endl;
//                                cout<<"EXPERIENCIA DEL JUGADOR "<<experiencia<<endl;
//                                cout<<"EXPERIENCIA PROPORCIONADA "<<Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy()<<endl;
//
//                            }
//                            Enviroment->GetEnemigos()[x]->SetVidaEnemy(GetAtaque());
//
////                            SetVida(1);
//                            cout<<GetVida()<<endl;
//                            if(vida<=0)
//                            {
//                                VivoMuerto=true;
//                                return;
//                            }
//                            Follow_Point_X = *CameraX;
//                            Follow_Point_Y = *CameraY;
//                            distance = 0 ;
//                            Follow=false;
//                            cout<<"colision con enemigo"<<endl;
//                            colliding = true;
//                        }
//                    }
                    ///final de ataque
                    ///prueba colision con enemigos modoAGRESIVO
                    for(int x=0 ; x< Enviroment->GetEnemigos().size(); x++)
                    {
                        if(player->isColliding(Enviroment->GetEnemigos()[x]->GetEnemy()->GetCollisionRect()))
                        {
                            if(*CameraX > Follow_Point_X)
                            {
                                *CameraX = *CameraX +10;
                            }
                            if(*CameraX < Follow_Point_X)
                            {
                                *CameraX = *CameraX - 10;
                            }

                            if(*CameraY > Follow_Point_Y)
                            {
                                *CameraY = *CameraY +10;
                            }
                            if(*CameraY < Follow_Point_Y)
                            {
                                *CameraY = *CameraY - 10;
                            }

//                            if((Enviroment->GetEnemigos()[x]->GetVidaEnemy() - GetAtaque()) < GetAtaque())
//                            {
//                                SubirNivel(Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy());
//                                SetEstatus();
//                                cout<<"nivel actual "<<GetNivel()<<endl;
//                                cout<<"vida "<<GetVida()<<endl;
//                                cout<<"Ataque "<<GetAtaque()<<endl;
//                                cout<<"EXPERIENCIA DEL JUGADOR "<<experiencia<<endl;
//                                cout<<"EXPERIENCIA PROPORCIONADA "<<Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy()<<endl;
//
//                            }
//                            Enviroment->GetEnemigos()[x]->SetVidaEnemy(GetAtaque());

                            SetVida(Enviroment->GetEnemigos()[x]->GetAtaqueEnemy());
                            cout<<GetVida()<<endl;
                            if(GetVida()<=0)

                            {
                                VivoMuerto=true;
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

void MainCharacter::UpdateStats()
{
    SetEstatus();
}

void MainCharacter::Update()
{

    UpdateStats();
    UpdateAnimation();
    UpdateControls();


}

void MainCharacter::UpdateCreator()
{
    UpdateAnimation();
    UpdateCreatorControls();
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
    double DifferenceX = X1-X2;
    double DifferenceY = Y1-Y2;
    double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
    return distance;

}
