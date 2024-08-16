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

	m_paddle = new Paddle();
	result = m_paddle->Initialize(device);
	if (!result)
	{
		return false;
	}
	m_paddle1 = new Paddle();
	result = m_paddle1->Initialize(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void Scene1::Update(float deltaTime)
{
}

void Scene1::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shader, XMMATRIX projectionMatrix)
{
	m_paddle->SetPosition(0, 2, 0);
	m_paddle->SetScale(2, 0.1, 0.2);
	m_paddle->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);

	m_paddle1->SetScale(2, 0.1, 0.2);
	m_paddle1->SetPosition(0, -2, 0);
	m_paddle1->Render(deviceContext, shader, m_viewMatrix, projectionMatrix);
}