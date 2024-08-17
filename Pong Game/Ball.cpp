#include "Ball.h"

Ball::Ball()
{
	m_collider = new Collider();
}

Ball::~Ball()
{
}

bool Ball::Initialize(ID3D11Device* device)
{
	bool result;
	char modelFilename[128];


	strcpy_s(modelFilename, "data/Ball.txt");
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	result = InitializeBuffers(device);
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

void Ball::Update(InputClass* m_Input)
{
	XMFLOAT3 static pos = m_collider->GetPosition();
	if (m_Input->IsKeyDown('K'))
	{
		m_position.z -= 0.1f;
		pos.z -= 0.1f;
	}
	if (m_Input->IsKeyDown('I'))
	{
		m_position.z += 0.1f;
		pos.z += 0.1f;
	}
	if (m_Input->IsKeyDown('J'))
	{
		m_position.x -= 0.1f;
		pos.x -= 0.1f;
	}
	if (m_Input->IsKeyDown('L'))
	{
		m_position.x += 0.1f;
		pos.x += 0.1f;
	}
	//if (pos.z <= -63) { OutputDebugString(L"collider "); }
	//if (m_position.z <= -63) { OutputDebugString(L"mesh "); }
	m_collider->SetPosition(pos.x, pos.y, pos.z);
	UpdateWorldMatrix();
	
}
void Ball::Shutdown()
{
	ShutdownBuffers();
}