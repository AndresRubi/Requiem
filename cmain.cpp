#include "cmain.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
    //ctor
    ScreenWidth=passed_ScreenWidth;
    ScreenHeight=passed_ScreenHeight;
    quit = false;
    csdl_setup = new SDL_Setup(&quit,ScreenWidth,ScreenHeight);


    GMForestArea = new CEnviroment(ScreenWidth,ScreenHeight, &CameraX,&CameraY,csdl_setup);

    CameraX = 0;
    CameraY = 0;
    MouseX=0;
    MouseY=0;

    enemy1 = new Xultur_Boss_Enemigo(200,300,&CameraX,&CameraY,csdl_setup, "Xultur");
//    enemy2 = new Ninja_Enemigo(300,200,&CameraX,&CameraY,csdl_setup, "gola");
//    enemy3 = new Warrior_Enemigo(400,200,&CameraX,&CameraY,csdl_setup, "gola");
//    enemy1 = new Enemigos(&CameraX,&CameraY,csdl_setup, "gola");

    GMPlayer = new MainCharacter(csdl_setup,&MouseX,&MouseY,&CameraX,&CameraY,ForestArea);
    Mix_Music *music= NULL;
    Mix_Chunk *sound= NULL;

    hola="corriente";
    GMod = new SDL_Event;
    Fin=false;
    testLost = Mix_LoadMUS("data/media/audio/personaje/muertePersonaje.ogg");
    music=Mix_LoadMUS("data/media/audio/gamePlay.ogg");

}

CMain::~CMain()
{
    delete csdl_setup;
    delete player;
}

void CMain::GameLoop()
{
//    CameraX = 0;
//    CameraY = 0;
//    MouseX=0;
//    MouseY=0;
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf("SDL_mixer Error %s\n", SDL_GetError());
    }
    music=Mix_LoadMUS("data/media/audio/gamePlay.ogg");
    if(music == NULL)
    {
        printf("coulnt load  Error %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music,-1);

    ForestArea = new CEnviroment(ScreenWidth,ScreenHeight, &CameraX,&CameraY,csdl_setup);
    player = new MainCharacter(csdl_setup,&MouseX,&MouseY,&CameraX,&CameraY,ForestArea);
    while(!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
        {

            csdl_setup->Begin();
            SDL_GetMouseState(&MouseX, &MouseY);
            ForestArea->DrawBack();


            if(!player->GetEstado())
            {
                player->Draw();
                player->Update();

            }


//            ForestArea->Update();

            ForestArea->DrawFront();

//            if(player->VivoMuerto)
//            {

////                music = Mix_LoadMUS("data/media/audio/personaje/muertePersonaje.ogg");
//                Mix_PlayMusic(testLost,-1);
////

//            }

            player->UpdateHealthBar();
            player->UpdatePantallaWin(player->Ganar);
            player->UpdatePantallaMuerte(player->VivoMuerto);
            csdl_setup->End();
//            if(ForestArea->exitLoop)
//                return;

        }
        Mix_FreeMusic(music);
        music=NULL;

}

void CMain::GMLoop()
{
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf("SDL_mixer Error %s\n", SDL_GetError());
    }
    music=Mix_LoadMUS("data/media/audio/gamePlay.ogg");
    if(music == NULL)
    {
        printf("coulnt load  Error %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music,-1);

    while(!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
        {

            csdl_setup->Begin();
            SDL_GetMouseState(&MouseX, &MouseY);
            GMForestArea->DrawBack();

            GMPlayer->Draw();
            GMPlayer->UpdateCreator();


            GMForestArea->Update();
            GMForestArea->DrawFront();
            csdl_setup->End();
//            if(ForestArea->exitLoop)
//                return;


        }
        Mix_FreeMusic(music);
        music=NULL;
}

