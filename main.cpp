#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "cmain.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Rect rect_background;
CMain* cmain,*prueba;
Mix_Music *music= NULL;
Mix_Chunk *sound= NULL;



void instrucciones()
{
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
            }
        }

        int w=0,h=0;
        background = IMG_LoadTexture(cmain->csdl_setup->GetRenderer(),"data/sprites/menu/instructions.png");
        SDL_QueryTexture(background, NULL, NULL, &w, &h);
        rect_background.x = 0;
        rect_background.y = 0;
        rect_background.w = w;
        rect_background.h = h;
        SDL_RenderClear(cmain->csdl_setup->GetRenderer());
        SDL_RenderCopy(cmain->csdl_setup->GetRenderer(),background,NULL,&rect_background);
        SDL_RenderPresent(cmain->csdl_setup->GetRenderer());
    }
}

void mainMenu()
{

    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf("SDL_mixer Error %s\n", SDL_GetError());
    }
    music=Mix_LoadMUS("data/media/audio/intro_menu.ogg");
    if(music == NULL)
    {
        printf("coulnt load  Error %s\n", Mix_GetError());
    }

    cmain=new CMain(640,400);
    int opcion = 1;
    SDL_Texture *menu_fondo[4];
    menu_fondo[0] = IMG_LoadTexture(cmain->csdl_setup->GetRenderer(),"data/sprites/menu/Empezar.png");
    menu_fondo[1] = IMG_LoadTexture(cmain->csdl_setup->GetRenderer(),"data/sprites/menu/CrearMapa.png");
    menu_fondo[2] = IMG_LoadTexture(cmain->csdl_setup->GetRenderer(),"data/sprites/menu/Instrucciones.png");
    menu_fondo[3] = IMG_LoadTexture(cmain->csdl_setup->GetRenderer(),"data/sprites/menu/Salir.png");
    SDL_Rect menu_rect;
    SDL_QueryTexture(menu_fondo[0], NULL, NULL, &menu_rect.w, &menu_rect.h);
    menu_rect.x = 0;
    menu_rect.y = 0;
    Mix_PlayMusic(music,-1);
    while(true)
    {


        while(SDL_PollEvent(cmain->csdl_setup->GetMainEvent()))
        {
            if(cmain->csdl_setup->GetMainEvent()->type == SDL_QUIT)
            {
                return;
            }
            if(cmain->csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
            {
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_4)
                {
                    exit(0);
                }
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
                {
                    Mix_PauseMusic();
                    cmain->GameLoop();
                    Mix_PlayMusic(music,-1);
                }
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_DOWN)
                {
                    opcion++;
                    if(opcion > 4)
                        opcion = 4;
                }
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_UP)
                {
                    opcion--;
                    if(opcion < 1)
                        opcion = 1;
                }
                if(cmain->csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_RETURN)
                {
                    switch(opcion)
                    {
                        case 1:
                            Mix_PauseMusic();
                            cmain->GameLoop();
                            Mix_PlayMusic(music,-1);
                            break;
                        case 2:
                            Mix_PauseMusic();
                            cmain->GMLoop();
                            Mix_PlayMusic(music,-1);
                            break;
                        case 3:
                            instrucciones();
                            break;
                        case 4:
                            exit(0);
                            break;
                    }
                }
            }

        }

        SDL_RenderCopy(cmain->csdl_setup->GetRenderer(),menu_fondo[opcion-1],NULL,&menu_rect);

        SDL_RenderPresent(cmain->csdl_setup->GetRenderer());
    }
    Mix_FreeMusic(music);
    music=NULL;
}

int main(int argc,char *argv[])
{


//    cmain->GameLoop();

    mainMenu();



    return 0;
}
