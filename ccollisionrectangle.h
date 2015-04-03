#ifndef CCOLLISIONRECTANGLE_H
#define CCOLLISIONRECTANGLE_H


#include "sdl_setup.h"
//#include "csprite.h"

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <math.h>

class CCollisionRectangle
{
    public:
        CCollisionRectangle();
        CCollisionRectangle(int x, int y, int w, int h);
        virtual ~CCollisionRectangle();

        void SetRectangle(int x, int y, int w, int h);
        SDL_Rect GetRectangle();
        void SetX(int x){CollisionRect.x = x + OffsetX;}
        void SetY(int y){CollisionRect.y = y + OffsetY;}
    protected:
    private:
    int OffsetX, OffsetY;
    SDL_Rect CollisionRect;
};

#endif // CCOLLISIONRECTANGLE_H
