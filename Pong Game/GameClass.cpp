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

	m_Scene1 = new Scene1;
	result = m_Scene1->Initialize(m_Graphics->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the scene1 object.", L"Error", MB_OK);
		return false;
	}

	m_ShaderManager = new ShaderManagerClass;
	result = m_ShaderManager->Initialize(m_Graphics->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
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

	if (m_Scene1)
	{
		m_Scene1->Shutdown();
		delete m_Scene1;
		m_Scene1 = 0;
	}

	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}
}


bool GameClass::Frame(InputClass* m_Input)
{
	bool result;

	// Render the graphics scene.
	result = Render(m_Input);
	if (!result)
	{
		return false;
	}
	m_Scene1->Update(0.0015f, m_Input);
	return true;

}


bool GameClass::Render(InputClass* m_Input)
{
	XMMATRIX projectionMatrix;
	bool result;

	m_Graphics->GetProjectionMatrix(projectionMatrix);
	m_Graphics->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Scene1->Render(m_Graphics->GetDeviceContext(), m_ShaderManager, projectionMatrix);
	m_Graphics->EndScene();
	return true;
}
