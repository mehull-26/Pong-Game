#include "gameClass.h"


GameClass::GameClass()
{
	m_Graphics = 0;
}


GameClass::GameClass(const GameClass& other)
{
}


GameClass::~GameClass()
{
}


bool GameClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_Graphics = new GraphicsClass;
	result = m_Graphics->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GameClass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}
	return;
}


bool GameClass::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}


bool GameClass::Render()
{
	m_Graphics->BeginScene(1.0f, 0.0f, 1.0f, 1.0f);

	m_Graphics->EndScene();
	return true;
}
