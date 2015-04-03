#include "csprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer,string FilePath,int x,int y, int w , int h, float *passed_CameraX, float *passed_CameraY,CCollisionRectangle passed_CollisionRect)
{
    //ctor
    CollisionRect = passed_CollisionRect;
    renderer=passed_renderer;
    fondo=NULL;
    fondo=IMG_LoadTexture(renderer,FilePath.c_str());
    fondo_rect.x = x;
    fondo_rect.y = y;
    fondo_rect.w = w;
    fondo_rect.h = h;
//test=passed_CollisionRect.GetRectangle();
    SDL_QueryTexture(fondo,NULL,NULL,&img_width,&img_height);
    crop.x = 0;
    crop.y = 0;
    crop.w = img_width;
    crop.h = img_height;

    Amount_Frame_X=0;
    Amount_Frame_Y=0;

    CurrentFrame=0;
    X_pos=x;
    Y_pos=y;

    Origin_X=0;
    Origin_Y=0;
    if(fondo == NULL)
    {
        cout<<"no pudo cargar el fondo"<<FilePath<<endl;
    }

    CollisionImage = NULL;
    CollisionImage = IMG_LoadTexture(renderer,"data/debug/collision.png");
     if(CollisionImage == NULL)
        {
            cout<<"no pudo cargar el fondásdasdasdo"<<endl;
        }

    CameraX = passed_CameraX;
    CameraY = passed_CameraY;

    Camera.x = fondo_rect.x + *CameraX;
    Camera.y = fondo_rect.y + *CameraY;
    Camera.w = fondo_rect.w;
    Camera.h = fondo_rect.h;
}

void CSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
    Amount_Frame_X = passed_Amount_X;
    Amount_Frame_Y = passed_Amount_Y;
}

void CSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
    if(animationDelay+Speed < SDL_GetTicks())
    {
        if(EndFrame <= CurrentFrame)
        {
            CurrentFrame = BeginFrame;
        }
        else
            CurrentFrame++;

        crop.x = CurrentFrame * (img_width/Amount_Frame_X);
        crop.y = Row * (img_height/Amount_Frame_Y);
        crop.w = img_width/Amount_Frame_X;
        crop.h = img_height/Amount_Frame_Y;
        animationDelay=SDL_GetTicks();
    }

}


CSprite::~CSprite()
{
    SDL_DestroyTexture(fondo);
    SDL_DestroyTexture(player);
}

void CSprite::Draw()
{

    Camera.x = fondo_rect.x + *CameraX;
    Camera.y = fondo_rect.y + *CameraY;

    CollisionRect.SetX(fondo_rect.x + *CameraX);
    CollisionRect.SetY(fondo_rect.y + *CameraY);

    test=CollisionRect.GetRectangle();

    SDL_RenderCopy(renderer,fondo,&crop,&Camera);
    SDL_RenderCopy(renderer,CollisionImage,NULL,&test);
}

void CSprite:: DrawSteady()
{
    SDL_RenderCopy(renderer,fondo,&crop,&fondo_rect);
    test=CollisionRect.GetRectangle();
    SDL_RenderCopy(renderer,CollisionImage,NULL,&test);
}

void CSprite::SetX(float x)
{
    X_pos=x;
    fondo_rect.x = int(X_pos - Origin_X) ;
}

void CSprite::SetY(float y)
{
    Y_pos=y;
    fondo_rect.y = int(Y_pos - Origin_Y);
}

void CSprite::SetPosition(float x, float y)
{
    X_pos=x;
    Y_pos=y;

    fondo_rect.x = int(X_pos - Origin_X);
    fondo_rect.y = int(Y_pos - Origin_Y);

}

float CSprite::GetX()
{
    return X_pos;
}

float CSprite::GetY()
{
    return Y_pos;
}

void CSprite::SetOrigin(float x , float y)
{
    Origin_X= x;
    Origin_Y= y;
        SetPosition(GetX(),GetY());

}

void CSprite::SetWidth(int w)
{
    fondo_rect.w = w;
}

void CSprite::SetHeight(int h)
{
    fondo_rect.h = h;
}

int CSprite::GetWidth()
{
    return fondo_rect.w;
}

int CSprite::GetHight()
{
    return fondo_rect.h;
}

bool CSprite::isColliding(CCollisionRectangle theCollider)
{
    return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x  ||
        CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y ||
        CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w ||
        CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h );
}


void CSprite::DrawMovimiento()
{
    Camera.x = fondo_rect.x + *CameraX +5;
    Camera.y = fondo_rect.y + *CameraY +5;

    CollisionRect.SetX(fondo_rect.x + *CameraX);
    CollisionRect.SetY(fondo_rect.y + *CameraY);

    test=CollisionRect.GetRectangle();

    SDL_RenderCopy(renderer,fondo,&crop,&Camera);
    SDL_RenderCopy(renderer,CollisionImage,NULL,&test);
}
