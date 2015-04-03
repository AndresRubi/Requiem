#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "cmain.h"

using namespace std;

int main(int argc,char *argv[])
{


    CMain* cmain=new CMain(640,400);

    cmain->GameLoop();

    return 0;
}
