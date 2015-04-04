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
    OnePressed =false;
//    vida=0;
    nivel=1;
    ataque = 0;
    experiencia = 0;
    SetEstatus();

    w=0,h=0;
    healthBars = IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
    SDL_QueryTexture(healthBars, NULL, NULL, &w, &h);
    rect_bar.x = 0;
    rect_bar.y = 0;
    rect_bar.w = w;
    rect_bar.h = h;
//    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);

    winScreen  = IMG_LoadTexture(csdl_setup->GetRenderer(),"data/media/screens/winFondo.png");
    SDL_QueryTexture(winScreen, NULL, NULL, &w, &h);
    rect_winScreen.x = 0;
    rect_winScreen.y = 0;
    rect_winScreen.w = 640;
    rect_winScreen.h = 400;

    deathScreen = IMG_LoadTexture(csdl_setup->GetRenderer(),"data/media/screens/dead.png");
    SDL_QueryTexture(deathScreen, NULL, NULL, &w, &h);
    rect_deatScreen.x = 0;
    rect_deatScreen.y = 0;
    rect_deatScreen.w = 640;
    rect_deatScreen.h = 400;

    vidaLvl1=10,vidaLvl2=20,vidaLvl3=30,vidaLvl4=40,vidaLvl5=50;
    por1=0,por2=0,por3=0,por4=0,po5=0;

    hit=NULL;
//    win=NULL;
//    loose=NULL;

        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        hit=Mix_LoadWAV("data/media/audio/personaje/hit.ogg");
        if(hit ==  NULL)
        {
            printf("coulnt load  Error %s\n", Mix_GetError());
        }



        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        killEnemy=Mix_LoadWAV("data/media/audio/enemigo/kill.ogg");
        if(killEnemy ==  NULL)
        {
            printf("coulnt load  Error %s\n", Mix_GetError());
        }



        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        killXultur=Mix_LoadWAV("data/media/audio/enemigo/muerteXultur.ogg");
        if(killXultur ==  NULL)
        {
            printf("coulnt load  muerte xultur Error %s\n", Mix_GetError());
        }



        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        contactXultur=Mix_LoadWAV("data/media/audio/enemigo/messageXultur.ogg");
        if(contactXultur ==  NULL)
        {
            printf("coulnt load  messange Error %s\n", Mix_GetError());
        }

                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        win=Mix_LoadMUS("data/media/audio/personaje/winPersonaje.ogg");
        if(win == NULL)
        {
            printf("coulnt load  Error %s\n", Mix_GetError());
        }

                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            printf("SDL_mixer Error %s\n", SDL_GetError());
        }
        loose=Mix_LoadMUS("data/media/audio/personaje/muertePersonaje.ogg");
        if(loose == NULL)
        {
            printf("coulnt load  Error %s\n", Mix_GetError());
        }
        XulturMessage=true;

        Ganar=false;
}

MainCharacter::~MainCharacter()
{
    //dtor
//    delete deathScreen;
//    delete healthBars;
    delete player;
}

void MainCharacter::UpdatePantallaWin(bool Ganar)
{
    if(Ganar)
    {
////        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
////        {
////            printf("SDL_mixer Error %s\n", SDL_GetError());
////        }
////        win=Mix_LoadMUS("data/media/audio/personaje/winPersonaje.ogg");
////        if(win == NULL)
////        {
////            printf("coulnt load  Error %s\n", Mix_GetError());
////        }
        Mix_PlayMusic(win,-1);
        SDL_RenderCopy(csdl_setup->GetRenderer(),winScreen,NULL,&rect_winScreen);
    }
}

void MainCharacter::UpdatePantallaMuerte(bool VivoMuerto)
{
    if(VivoMuerto)
    {
//        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
//        {
//            printf("SDL_mixer Error %s\n", SDL_GetError());
//        }
//        loose=Mix_LoadMUS("data/media/audio/personaje/muertePersonaje.ogg");
//        if(loose == NULL)
//        {
//            printf("coulnt load  Error %s\n", Mix_GetError());
//        }
        Mix_PlayMusic(loose,-1);
        SDL_RenderCopy(csdl_setup->GetRenderer(),deathScreen,NULL,&rect_deatScreen);
    }
}

void MainCharacter::UpdateHealthBar()
{
    passedNivel=nivel;
    por1=vida/10*100;
    switch(passedNivel)
    {
    case 1:
    {
        if(vida > 2 && 4<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra25.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 4 && 6<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra50.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 6 && 10<vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida == 10)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra100.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        break;
    }
    case 2:
    {
        if(vida > 4 && 9 <= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra25.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);

        }
        if(vida > 9 && 14<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra50.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 14 && 19<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida == 20)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra100.png");
//                    healthBars=healthBarActual;
        }
        SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        break;
    }

    case 3:
    {
        if(vida > 7 && 15<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra25.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);

        }
        if(vida > 15 && 21<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra50.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 21 && 29<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida == 30)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra100.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        break;
    }
    case 4:
    {
        if(vida > 10 && 20<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra25.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);

        }
        if(vida > 20 && 30<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra50.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 30 && 39<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida == 40)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra100.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        break;
    }

    case 5:
    {
        if(vida > 13 && 25<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra25.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);

        }
        if(vida > 25 && 37<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra50.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida > 37 && 49<= vida)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra75.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        if(vida == 50)
        {
            healthBars=IMG_LoadTexture(csdl_setup->GetRenderer(),"data/sprites/UI/HealthBar/barra100.png");
//                    healthBars=healthBarActual;
//                    SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        }
        SDL_RenderCopy(csdl_setup->GetRenderer(),healthBars,NULL,&rect_bar);
        break;
    }


    }

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

    break;
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




        }
        else
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
            for(int x=0 ; x< Enviroment->GetEnemigos().size(); x++)
            {
                if(player->isColliding(Enviroment->GetEnemigos()[x]->GetEnemy()->GetCollisionRect()))
                {
                    Mix_PlayChannel(-1,hit,0);

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

                    if(Enviroment->GetEnemigos()[x]->getID()== "xultur" && XulturMessage)
                        {
                            Mix_PlayChannel(-1,contactXultur,0);
                            XulturMessage=false;
                        }

                    if((Enviroment->GetEnemigos()[x]->GetVidaEnemy() - GetAtaque()) < GetAtaque())
                    {
                        SubirNivel(Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy());
                        Mix_PlayChannel(-1,killEnemy,0);
                        SetEstatus();

                        if(Enviroment->GetEnemigos()[x]->getID()== "xultur")
                        {
//                            Enviroment->GetEnemigos()[x]->AnimacionMuerte();
                            Mix_PlayChannel(-1,killXultur,0);
                            Ganar=true;
                        }

                        cout<<"nivel actual "<<GetNivel()<<endl;
                        cout<<"vida "<<GetVida()<<endl;
                        cout<<"Ataque "<<GetAtaque()<<endl;
                        cout<<"EXPERIENCIA DEL JUGADOR "<<experiencia<<endl;
                        cout<<"EXPERIENCIA PROPORCIONADA "<<Enviroment->GetEnemigos()[x]->GetExpecienciaEnemy()<<endl;
                        atacando=false;
                    }
                    Enviroment->GetEnemigos()[x]->SetVidaEnemy(GetAtaque());

                    cout<<"booleano atacando "<<atacando<<endl;
                    cout<<"la vida del personaje "<<GetVida()<<endl;
                    cout<<" "<<endl;
                    cout<<"se resto "<<Enviroment->GetEnemigos()[x]->GetAtaqueEnemy()<< "de la colision"<<endl;

                    SetVida(Enviroment->GetEnemigos()[x]->GetAtaqueEnemy());

                    cout<<" "<<endl;
                    cout<<"la vida del personaje"<<GetVida()<<endl;

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


        }
        else
            Follow=false;
        timeCheck = SDL_GetTicks();
    }

////        Mix_FreeMusic(killEnemy);
//     delete killEnemy;
////        Mix_FreeMusic(killXultur);
//        delete killXultur;
////        Mix_FreeMusic(contactXultur);
//        delete contactXultur;
////        Mix_FreeMusic(hit);
//        hit=NULL;


}

void MainCharacter::UpdateStats()
{
    SetEstatus();
}

void MainCharacter::Update()
{
//    UpdateHealthBar();
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
