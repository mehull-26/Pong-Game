#include "Scene1.h"

Scene1::Scene1()
{
	m_paddle = 0;
	m_paddle1 = 0;
}

Scene1::~Scene1()
{
}

bool Scene1::Initialize(ID3D11Device* device)
{
	bool result;

	Scene::Initialize(device);

	m_paddle = new Paddle(1);
	m_paddle->SetPosition(0, 0, -2);
	m_paddle->SetScale(2, 0.2, 0.1);
	result = m_paddle->Initialize(device);
	if (!result)
	{
		return false;
	}

	m_ball = new Ball();
	m_ball->SetPosition(0, 0, 8);
	m_ball->SetScale(0.2, 0.2, 0.2);
	result = m_ball->Initialize(device);
	if (!result)
	{
		return false;
	}

	m_paddle1 = new Paddle(2);
	m_paddle1->SetPosition(0, 0, 18);
	m_paddle1->SetScale(2, 0.2, 0.1);
	result = m_paddle1->Initialize(device);
	if (!result)
	{
		return false;
	}


	m_bar0 = new Paddle(3);
	m_bar0->SetPosition(-7, 0, 5);
	m_bar0->SetScale(0.3, 0.3, 20);
	result = m_bar0->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_bar1 = new Paddle(3);
	m_bar1->SetPosition(7, 0, 5);
	m_bar1->SetScale(0.3, 0.3, 20);
	result = m_bar1->Initialize(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void Scene1::Update(float deltaTime, InputClass* m_Input)
{
	static double accumulator = 0;
	static double prevTime = GetTime();
	accumulator += GetTime() - prevTime;

	while (accumulator >= deltaTime)
	{
		accumulator -= deltaTime;
		m_paddle->Update(m_Input);
		m_paddle1->Update(m_Input);
		prevTime = GetTime();
	}
}

void Scene1::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shader, XMMATRIX projectionMatrix)
{
	
	
	m_paddle->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);

	m_ball->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);

	m_paddle1->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);

	m_bar0->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);
	
	m_bar1->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);
}

void Scene1::Shutdown()
{
	if (m_paddle)
	{
		m_paddle->Shutdown();
		delete m_paddle;
		m_paddle = 0;
	}

	if (m_paddle1)
	{
		m_paddle1->Shutdown();
		delete m_paddle1;
		m_paddle1 = 0;
	}

	if (m_ball)
	{
		m_ball->Shutdown();
		delete m_ball;
		m_ball = 0;
	}

	if (m_bar0)
	{
		m_bar0->Shutdown();
		delete m_bar0;
		m_bar0 = 0;
	}

	if (m_bar1)
	{
		m_bar1->Shutdown();
		delete m_bar1;
		m_bar1 = 0;
	}

	Scene::Shutdown();
}