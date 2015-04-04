#include "cenviroment.h"

CEnviroment::CEnviroment(int ScreenWidth, int ScreenHeight, float  *passed_CameraX, float *passed_CameraY,SDL_Setup *passed_csdl_setup)
{
    //ctor
    csdl_setup = passed_csdl_setup;
    CameraX = passed_CameraX;
    CameraY = passed_CameraY;
     for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                grass[i][j] = new CSprite(csdl_setup->GetRenderer(),"data/stage/jardin.png",ScreenWidth * i,ScreenHeight * j,ScreenWidth,ScreenHeight,CameraX,CameraY,CCollisionRectangle());
            }
        }

//    enemy1 = new Arquero_Enemigo(200,300,&CameraX,&CameraY,csdl_setup, "archer");
//    enemy2 = new Ninja_Enemigo(300,200,&CameraX,&CameraY,csdl_setup, "ninja");
//    enemy3 = new Warrior_Enemigo(400,200,&CameraX,&CameraY,csdl_setup, "warrior");

    Mode = LevelCreation;

OnePressed = false;
//        tree = new Tree(300,300, CameraX,CameraY,csdl_setup);
LoadFromFile();

}

CEnviroment::~CEnviroment()
{
    //dtor

     for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 7; j++)
                    {
                        delete grass[i][j];
                    }
                }

    for(vector<Tree*>::iterator i = trees.begin(); i!= trees.end(); i++)
    {
        delete (*i);
    }
    trees.clear();

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
    {
        delete (*x);
    }
    enemies.clear();

 exitLoop=false;
}

void CEnviroment::DrawBack()
{
     for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 7; j++)
                    {
                        grass[i][j] ->Draw();
                    }
                }
//    tree->DrawTrunk();
    for(vector<Tree*>::iterator i = trees.begin(); i!= trees.end(); i++)
    {
        (*i)->DrawTrunk();
    }


    for(vector<Enemigos*>::iterator p = enemies.begin(); p!= enemies.end(); p++)
    {
        if(!(*p)->EnemigoEliminado())
        {
            (*p)->Draw();
            (*p)->Update();
        }else if((*p)->EnemigoEliminado() && enemies.back()>0)
        {

            enemies.erase(p);


        }

    }

}

void CEnviroment::DrawFront()
{
//    tree->DrawCrown();
for(vector<Tree*>::iterator i = trees.begin(); i!= trees.end(); i++)
    {
        (*i)->DrawCrown();
    }



}

void CEnviroment::LoadFromFile()
{
    ifstream LoadedFile("data/stageLayout.txt");
    ifstream patito("data/stageEnemy.txt");
    ifstream war("data/stageEnemyWarrior.txt");
    ifstream xul("data/coordinates/stageEnemyXultur.txt");
    ifstream kam("data/coordinates/stageEnemyKamikaze.txt");
    ifstream nin("data/stageEnemyNinja.txt");

    string line;


    enum ObjetType{ TypeNone,
        TypeTree,TypeArcher,TypeWarrior,TypeNinja,TypeKamikaze,TypeXultur
        };

    int CurrentType = TypeNone;

    if(LoadedFile.is_open())
    {
        while(LoadedFile.good())
        {
            getline(LoadedFile,line);
            if(line == "---====BeginTree====---" )
            {
                CurrentType = TypeTree;
            }
            else if(line == "---====EndTree====---")
            {
                CurrentType = TypeNone;
            }
            else
            {
                if(CurrentType == TypeTree)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            trees.push_back(new Tree(TempX,TempY,CameraX,CameraY,csdl_setup));
                        }
                        previousWord = word;
                    }
                }
            }
        }
    }else
    {
        cout<<"Mapa no se abrio"<<endl;
    }

    if(patito.is_open())
    {
        while(patito.good())
        {
         ///upload archer
             getline(patito,line);
            if(line == "---====BeginArcher====---" )
            {
                CurrentType = TypeArcher;
            }
            else if(line == "---====EndArcher====---")
            {
                CurrentType = TypeArcher;
            }
            else
            {
                if(CurrentType == TypeArcher)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            enemies.push_back(new Arquero_Enemigo(TempX,TempY,CameraX,CameraY,csdl_setup,"archer"));
                        }
                        previousWord = word;
                    }
                }
            }
            ///find de archer

        }
    }
    else
    {
        cout<<"Enemigos Archers no se abrio"<<endl;
    }

    if(war.is_open())
    {
        while(war.good())
        {
            getline(war,line);
            if(line == "---====BeginWarrior====---" )
            {
                CurrentType = TypeWarrior;
            }
            else if(line == "---====EndWarrior====---")
            {
                CurrentType = TypeWarrior;
            }
            else
            {
                if(CurrentType == TypeWarrior)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            enemies.push_back(new Warrior_Enemigo(TempX,TempY,CameraX,CameraY,csdl_setup,"warrior"));
                        }
                        previousWord = word;
                    }
                }
            }
        }
    }
    else
    {
        cout<<"no pudo abrir el archivo warrior"<<endl;
    }
///BEGIN BOSSES

/// BEGIN XULTUR
if(xul.is_open())
    {
        while(xul.good())
        {
            getline(xul,line);
            if(line == "---====BeginXultur====---" )
            {
                CurrentType = TypeXultur;
            }
            else if(line == "---====EndXultur====---")
            {
                CurrentType = TypeXultur;
            }
            else
            {
                if(CurrentType == TypeXultur)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            enemies.push_back(new Xultur_Boss_Enemigo(TempX,TempY,CameraX,CameraY,csdl_setup,"xultur"));
                        }
                        previousWord = word;
                    }
                }
            }
        }
    }
    else
    {
        cout<<"no pudo abrir el archivo xultur"<<endl;
    }
/// END XULTUR

/// BEGIN KAMIKAZE
/// END KAMIKAZE
if(kam.is_open())
    {
        while(kam.good())
        {
            getline(kam,line);
            if(line == "---====BeginKamikaze====---" )
            {
                CurrentType = TypeKamikaze;
            }
            else if(line == "---====EndKamikaze====---")
            {
                CurrentType = TypeKamikaze;
            }
            else
            {
                if(CurrentType == TypeKamikaze)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            enemies.push_back(new Kamikaze_Boss_Enemigo(TempX,TempY,CameraX,CameraY,csdl_setup,"kamikaze"));
                        }
                        previousWord = word;
                    }
                }
            }
        }
    }
    else
    {
        cout<<"no pudo abrir el archivo kamikaze"<<endl;
    }
///END BOSSES
    if(nin.is_open())
    {
        while(nin.good())
        {
            getline(nin,line);
            if(line == "---====BeginNinja====---" )
            {
                CurrentType = TypeNinja;
            }
            else if(line == "---====EndNinja====---")
            {
                CurrentType = TypeNinja;
            }
            else
            {
                if(CurrentType == TypeNinja)
                {

                    istringstream iss(line);
                    string previousWord = "";
                    int TempX = 0;
                    int TempY = 0;

                    while(iss)
                    {
                        string word;
                        iss>> word;



                        if(previousWord ==  "x:")
                        {
                            TempX = atoi(word.c_str());

                        }
                        if(previousWord == "y:")
                        {
                            TempY = atoi(word.c_str());
                            enemies.push_back(new Ninja_Enemigo(TempX,TempY,CameraX,CameraY,csdl_setup,"ninja"));
                        }
                        previousWord = word;
                    }
                }
            }
        }
    }
    else
    {
        cout<<"no pudo abrir el archivo ninja"<<endl;
    }
}

void CEnviroment::SaveToFile()
{
    ofstream LoadedFile,patito,burbuja,ninja,xultur,kamikaze;

    LoadedFile.open("data/stageLayout.txt");

    LoadedFile << "---====BeginTree====---"<<endl;

    for(vector<Tree*>::iterator i = trees.begin(); i!= trees.end(); i++)
        {
            (*i)->DrawCrown();
            LoadedFile << "x: "<< (*i)->GetX() <<"\ty: "<< (*i)->GetY() <<endl;
        }

    LoadedFile << "---====EndTree====---"<<endl;

    LoadedFile.close();

    ///save de enemigo archer
    patito.open("data/stageEnemy.txt");
    patito << "---====BeginArcher====---"<<endl;

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
        {
            if((*x)->getID() == "archer")
            {
                (*x)->Draw();
                patito << "x: "<< (*x)->GetX() <<"\ty: "<< (*x)->GetY() <<endl;
            }
        }

    patito << "---====EndArcher====---"<<endl;
    patito.close();
    ///fin de archer

    ///new
    burbuja.open("data/stageEnemyWarrior.txt");
    burbuja << "---====BeginWarrior====---"<<endl;

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
        {
            if((*x)->getID() == "warrior")
            {
                (*x)->Draw();
                burbuja << "x: "<< (*x)->GetX() <<"\ty: "<< (*x)->GetY() <<endl;
            }

        }

    burbuja << "---====EndWarrior====---"<<endl;
    burbuja.close();
    ///end

    ///KAMIKAZE

    kamikaze.open("data/coordinates/stageEnemyKamikaze.txt");
    kamikaze << "---====BeginKamikaze====---"<<endl;

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
        {
            if((*x)->getID() == "kamikaze")
            {
                (*x)->Draw();
                kamikaze << "x: "<< (*x)->GetX() <<"\ty: "<< (*x)->GetY() <<endl;
            }
        }
    kamikaze << "---====EndKamikaze====---"<<endl;
    kamikaze.close();
    ///KAMIKAZE END


    ///XULTUR

    xultur.open("data/coordinates/stageEnemyXultur.txt");
    xultur << "---====BeginXultur====---"<<endl;

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
        {
            if((*x)->getID() == "xultur")
            {
                (*x)->Draw();
                xultur << "x: "<< (*x)->GetX() <<"\ty: "<< (*x)->GetY() <<endl;
            }
        }
    xultur << "---====EndXultur====---"<<endl;
    xultur.close();
    ///XULTUR END




///new
    ninja.open("data/stageEnemyNinja.txt");
    ninja << "---====BeginNinja====---"<<endl;

    for(vector<Enemigos*>::iterator x = enemies.begin(); x!= enemies.end(); x++)
        {
            if((*x)->getID() == "ninja")
            {
                (*x)->Draw();
                ninja << "x: "<< (*x)->GetX() <<"\ty: "<< (*x)->GetY() <<endl;
            }

        }

    ninja << "---====EndNinja====---"<<endl;
    ninja.close();
    ///end

    cout<<"level saved"<<endl;


}

void CEnviroment::Update()
{
    if(Mode == LevelCreation)
    {

    if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F11 )
            {
                enemies.push_back(new Ninja_Enemigo(-1000,-1000,CameraX,CameraY,csdl_setup,"ninja"));
                SaveToFile();
                OnePressed = true;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F11 )
            {
                OnePressed = false;
            }
        }


//305,183

    //////////////////////////////////
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F1 )
            {
                trees.push_back(new Tree(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup));
                OnePressed = true;
                cout<<"creo un pasto lol"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F1)
            {
                OnePressed = false;
            }
        }

        ////////////////////////////////

        ///prueba de enemigo
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F5 )
            {
                enemies.push_back(new Arquero_Enemigo(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup,"archer"));
                OnePressed = true;
                cout<<"creo un archer"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F5)
            {
                OnePressed = false;
            }
        }
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F6 )
            {
                enemies.push_back(new Ninja_Enemigo(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup,"ninja"));
                OnePressed = true;
                cout<<"creo un ninja"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F6)
            {
                OnePressed = false;
            }
        }
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F7)
            {
                enemies.push_back(new Warrior_Enemigo(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup,"warrior"));
                OnePressed = true;
                cout<<"creo un warrior"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F7)
            {
                OnePressed = false;
            }
        }

        ///BOSSES XULTUR KAMIKAZE
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F8)
            {
                enemies.push_back(new Kamikaze_Boss_Enemigo(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup,"kamikaze"));
                OnePressed = true;
                cout<<"creo el boss Kamikaze"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F8)
            {
                OnePressed = false;
            }
        }
        ///DIVISION
        if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F9)
            {
                enemies.push_back(new Xultur_Boss_Enemigo(-*CameraX+310,-*CameraY+160,CameraX,CameraY,csdl_setup,"xultur"));
                OnePressed = true;
                cout<<"creo el boss XULTUR"<<endl;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F9)
            {
                OnePressed = false;
            }
        }
        ///END BOSSES

        ///find de prueba de enemigo





/////////////////////////////////////////
  if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F2 )
            {
                if(trees.size() > 0 )
                {
                    int count=0;
                    for(vector<Tree*>::iterator i = trees.begin(); i!= trees.end(); i++)
                    {
                        if(count == trees.size())
                        delete(*i);

                        count++;
                    }
                    trees.pop_back();

                }
                OnePressed = true;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F2)
            {
                OnePressed = false;
            }
        }
    }
////////////////////////////////



    if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F12 )
            {
                if(Mode == LevelCreation)
                {
                    Mode = Gameplay;
                }else if( Mode == Gameplay)
                {
                    cout<<"GM MODE"<<endl;
                    Mode = LevelCreation;
                }

                OnePressed = true;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_F12)
            {
                OnePressed = false;
            }
        }


        ///


    if(csdl_setup->GetMainEvent() -> type == SDL_KEYDOWN)
        {
            if(!OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_ESCAPE )
            {
                exitLoop=true;
                OnePressed = true;
            }
        }

        if(csdl_setup->GetMainEvent() -> type == SDL_KEYUP)
        {
            if(OnePressed && csdl_setup->GetMainEvent() -> key.keysym.sym == SDLK_ESCAPE)
            {
                OnePressed = false;
            }
        }

}
