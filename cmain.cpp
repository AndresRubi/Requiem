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

//    enemy1 = new Arquero_Enemigo(200,300,&CameraX,&CameraY,csdl_setup, "gola");
//    enemy2 = new Ninja_Enemigo(300,200,&CameraX,&CameraY,csdl_setup, "gola");
//    enemy3 = new Warrior_Enemigo(400,200,&CameraX,&CameraY,csdl_setup, "gola");
//    enemy1 = new Enemigos(&CameraX,&CameraY,csdl_setup, "gola");

    GMPlayer = new MainCharacter(csdl_setup,&MouseX,&MouseY,&CameraX,&CameraY,ForestArea);

    hola="corriente";
    GMod = new SDL_Event;
    Fin=false;
}

CMain::~CMain()
{
    delete csdl_setup;
    delete player;
}

void CMain::GameLoop()
{
    CameraX = 0;
    CameraY = 0;
    MouseX=0;
    MouseY=0;

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
            csdl_setup->End();
//            if(ForestArea->exitLoop)
//                return;
            if(player->GetEstado())
            {

            Fin=player->VivoMuerto;

            }
        }

}

void CMain::GMLoop()
{
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
        return;
}

