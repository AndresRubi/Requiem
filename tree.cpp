#include "tree.h"

Tree::Tree(int x , int y, float  *CameraX, float *CameraY, SDL_Setup *csdl_setup)
{
    //ctor
    this->x = x;
    this->y = y;
     Trunk= new CSprite(csdl_setup->GetRenderer(),"data/stage/log.png",x,y,64,64,CameraX,CameraY,CCollisionRectangle(26,16,9,40));
     Crown= new CSprite(csdl_setup->GetRenderer(),"data/stage/leave.png",x,y-58,64,64,CameraX,CameraY,CCollisionRectangle(15,30,32,32));
}

Tree::~Tree()
{
    //dtor
    delete Crown;
    delete Trunk;
}

int Tree::GetX()
{
    return x;
}

int Tree::GetY()
{
    return y;
}

void Tree:: DrawCrown()
{
    Crown->Draw();
}

void Tree::DrawTrunk()
{
    Trunk->Draw();
}
