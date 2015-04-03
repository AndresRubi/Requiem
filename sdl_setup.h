#ifndef SDL_SETUP_H
#define SDL_SETUP_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
using namespace std;

class SDL_Setup
{
    public:
        SDL_Setup(bool* quit,int ScreenWidth, int ScreenHeight);
        virtual ~SDL_Setup();
        SDL_Renderer* GetRenderer();
        SDL_Event* GetMainEvent();

        void Begin();
        void End();

    protected:
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event* mainEvent;
};

#endif // SDL_SETUP_H
