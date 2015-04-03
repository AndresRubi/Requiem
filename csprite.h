#ifndef CSPRITE_H
#define CSPRITE_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "ccollisionrectangle.h"
using namespace std;

class CSprite
{
    public:
        CSprite(SDL_Renderer* passed_renderer,string FilePath,int x,int y, int w , int h, float *CameraX, float *CameraY,CCollisionRectangle passed_CollisionRect);
        virtual ~CSprite();
        void Draw();
        void DrawSteady();

        void SetX(float X);
        void SetY(float Y);
        void SetPosition(float x,float y);

        void DrawMovimiento();

        float GetX();
        float GetY();

        void SetWidth(int w);
        void SetHeight(int h);
        int GetWidth();
        int GetHight();
        void SetOrigin(float x , float y);
        void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
        void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

        bool isColliding(CCollisionRectangle theCollider);
        CCollisionRectangle GetCollisionRect() {return CollisionRect;};


    protected:

    private:
    CCollisionRectangle CollisionRect;
    SDL_Rect Camera, test;
    float *CameraX;
    float *CameraY;
    float Origin_X, Origin_Y;
    float X_pos, Y_pos;
    int img_width, img_height;
    int CurrentFrame;
    int animationDelay;
    int Amount_Frame_X,Amount_Frame_Y;

    SDL_Texture* fondo, *player, *CollisionImage;
    SDL_Rect fondo_rect,player_rect,crop;
    SDL_Renderer* renderer;




};

#endif // CSPRITE_H
