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
	result = m_paddle->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_paddle->GetCollider().SetPosition(0, 0, -65);
	m_paddle->GetCollider().SetSize(20, 4, 2);
	m_paddle->SetPosition(0, 0, -65);
	m_paddle->SetScale(10, 2, 1);
	
	m_ball = new Ball();
	result = m_ball->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_ball->GetCollider().SetPosition(0, 0, -10);
	m_ball->GetCollider().SetSize(4, 4, 4);
	m_ball->SetPosition(0, 0, -10);
	m_ball->SetScale(2, 2, 2);


	m_paddle1 = new Paddle(2);
	result = m_paddle1->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_paddle1->GetCollider().SetPosition(0, 0, 45);
	m_paddle1->GetCollider().SetSize(20, 4, 2);
	m_paddle1->SetPosition(0, 0, 45);
	m_paddle1->SetScale(10, 2, 1);

	m_bar0 = new Paddle(3);
	m_bar0->SetPosition(-40, 0, 0);
	m_bar0->SetScale(2, 2, 85);
	result = m_bar0->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_bar1 = new Paddle(4);
	m_bar1->SetPosition(40, 0, 0);
	m_bar1->SetScale(2, 2, 85);
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
		m_ball->Update(m_Input);
		prevTime = GetTime();
	}
	static bool collision;
	collision =  m_ball->GetCollider().CheckCollision(m_paddle->GetCollider());
	if (collision)
	{
		OutputDebugString(L"collided");
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