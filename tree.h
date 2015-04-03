#ifndef TREE_H
#define TREE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "sdl_setup.h"
#include "csprite.h"
#include <math.h>
#include <iostream>
#include <vector>

class Tree
{
    public:
        Tree(int x , int y,float  *CameraX, float *CameraY,SDL_Setup *csdl_setup);
        virtual ~Tree();

        void DrawCrown();
        void DrawTrunk();

        int GetX();
        int GetY();

        CSprite* GetCrown() {return Crown;}
        CSprite* GetTrunk() {return Trunk;}

    protected:
    private:
    int x,y;
    CSprite *Crown, *Trunk;

};

#endif // TREE_H
