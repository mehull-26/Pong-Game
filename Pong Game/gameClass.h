#ifndef _GAMECLASS_H_
#define _GAMECLASS_H_

#include "GraphicsClass.h"

//////////
//GLOABALS
//////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

class GameClass 
{
public:
	GameClass();
    GameClass(const GameClass&);
    ~GameClass();
    bool Initialize(int,int,HWND hwnd);
    void Shutdown();
    bool Frame();

private:
    bool Render();
    GraphicsClass* m_Graphics;
};

#endif // !GAMECLASS_H
