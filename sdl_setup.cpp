#include "sdl_setup.h"

SDL_Setup::SDL_Setup(bool* quit,int ScreenWidth, int ScreenHeight)
{

    SDL_Init(SDL_INIT_VIDEO);
    window = NULL;
    window = SDL_CreateWindow("Kitbot",100,100,ScreenWidth,ScreenHeight,SDL_WINDOW_SHOWN  | SDL_WINDOW_RESIZABLE);

    if(window  == NULL)
    {
        cout<<"window couldt be created"<<endl;
        *quit=true;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    mainEvent = new SDL_Event();

}

SDL_Setup::~SDL_Setup()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;
}

SDL_Renderer* SDL_Setup::GetRenderer()
{
    return renderer;
}

SDL_Event* SDL_Setup::GetMainEvent()
{
    return mainEvent;
}

void SDL_Setup::Begin()
{
    SDL_PollEvent(mainEvent);
    SDL_RenderClear(renderer);
}

void SDL_Setup::End()
{
    SDL_RenderPresent(renderer);
}
