#ifndef _GAMECLASS_H_
#define _GAMECLASS_H_

#include "InputClass.h"
#include "GraphicsClass.h"
#include "ShaderManager.h"
#include "Scene1.h"

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
    bool Frame(InputClass*);

private:
    bool Render(InputClass*);
    GraphicsClass* m_Graphics;
	ShaderManagerClass* m_ShaderManager;
	Scene1* m_Scene1;
};

#endif // !GAMECLASS_H
