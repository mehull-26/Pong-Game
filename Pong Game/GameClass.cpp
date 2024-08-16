#include "gameClass.h"


GameClass::GameClass()
{
	m_Graphics = 0;
	m_camera = 0;
	m_paddle1 = 0;
	m_paddle2 = 0;
	m_shaderManager = 0;
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

	m_camera = new CameraClass;
	m_camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_camera->Render();

	m_shaderManager = new ShaderManagerClass;
	result = m_shaderManager->Initialize(m_Graphics->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	m_paddle1 = new Paddle;

	result = m_paddle1->Initialize(m_Graphics->GetDevice());
	if (!result)
	{
		return false;
	}

	m_paddle2 = new Paddle;

	result = m_paddle2->Initialize(m_Graphics->GetDevice());
	if (!result)
	{
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

	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	if (m_shaderManager)
	{
		m_shaderManager->Shutdown();
		delete m_shaderManager;
		m_shaderManager = 0;
	}

	if (m_paddle1)
	{
		m_paddle1->Shutdown();
		delete m_paddle1;
		m_paddle1 = 0;
	}
	
	if (m_paddle2)
	{
		m_paddle2->Shutdown();
		delete m_paddle2;
		m_paddle2 = 0;
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix;
	bool result;

	m_Graphics->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_Graphics->GetWorldMatrix(worldMatrix);
	m_camera->GetViewMatrix(viewMatrix);
	m_Graphics->GetProjectionMatrix(projectionMatrix);

	m_paddle1->SetScale(2, 0.2, 0.2);
	m_paddle1->SetPosition(0, -2, 0);
	result = m_paddle1->Render(m_Graphics->GetDeviceContext(), m_shaderManager, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	
	m_paddle2->SetScale(2, 0.2, 0.2);
	m_paddle2->SetPosition(0, 2, 0);
	result = m_paddle2->Render(m_Graphics->GetDeviceContext(), m_shaderManager, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	m_Graphics->EndScene();
	return true;
}
