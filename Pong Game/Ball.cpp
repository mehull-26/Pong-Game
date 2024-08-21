#include "Ball.h"
#include <chrono>

double GetTime()
{
	using namespace std::chrono;
	return duration<double>(steady_clock::now().time_since_epoch()).count();
}

Ball::Ball()
{

}

Ball::~Ball()
{
}

bool Ball::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;
	char modelFilename[128];

	m_collider = new Collider();
	m_speed = { 1.0f, 0.0f, 1.0f };
	m_direction = { 1.0f, 0.0f, 1.0f };

	strcpy_s(modelFilename, "data/Ball.txt");
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	result = InitializeBuffers(device, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Ball::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;
	RenderBuffers(deviceContext);

	result = shaderManager->RenderColorShader(deviceContext, m_indexCount, m_worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

void Ball::Update(InputClass* m_Input, int Collision)
{
	XMFLOAT3 static pos = m_collider->GetPosition();

	static int count = 0;
	static double accumulator = 0;
	static double prevTime = GetTime();
	accumulator += GetTime() - prevTime;

	//if (m_position.z < -67)
	//{
	//	P1Lose();
	//}
	//else if (m_position.z > 47)
	//{
	//	P2Lose();
	//}

	static float startTime = GetTime();
	while (accumulator >= 5 && m_speed.z < 5)
	{
		accumulator -= 5;
		m_speed.z += log10(1 + (GetTime() - startTime) * 0.001);
		startTime = GetTime();
	}
	prevTime = GetTime();

		if (Collision == 1)
		{
			if (m_position.z < -62.5 || m_position.z > 42.5)
			{
				m_direction.z *= -1;
				m_direction.x *= -1;
			}
			else
			{
				m_direction.z *= -1;
			}
		}
		if (Collision == 2)
		{
			m_direction.x *= -1;
		}
		m_position.z -= m_speed.z * m_direction.z * 0.05f;
		m_position.x -= m_speed.x * m_direction.x * 0.05f;
		pos.z -= m_speed.z * m_direction.z * 0.05f;
		pos.x -= m_speed.x * m_direction.x * 0.05f;
	m_collider->SetPosition(pos.x, pos.y, pos.z);
	UpdateWorldMatrix();

}
void Ball::Shutdown()
{
	ShutdownBuffers();
}

void Ball::SetVelocity(float x, float y, float z)
{
	m_speed = { x, y, z };
}

//void Ball::P1Lose()
//{
//	m_position = { 0.0f, 0.0f, -10.0f };
//	m_collider->SetPosition(0, 0, -10);
//	m_speed = { 0.0f, 0.0f, 0.0f };
//}
//
//void Ball::P2Lose()
//{
//	m_position = { 0.0f, 0.0f, -10.0f };
//	m_collider->SetPosition(0, 0, -10);
//	m_speed = { 0.0f, 0.0f, 0.0f };
//}