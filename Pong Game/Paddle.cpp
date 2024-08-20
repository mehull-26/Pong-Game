#include "Paddle.h"

Paddle::Paddle(int ID)
{
	m_ID = ID;
	m_collider = new Collider();
}

Paddle::~Paddle()
{
}

bool Paddle::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
    bool result;
	char modelFilename[128];


	strcpy_s(modelFilename, "data/paddle.txt");
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

bool Paddle::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
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

void Paddle::Update(InputClass* m_Input)
{
	XMFLOAT3 static pos;
	pos = m_collider->GetPosition();
	switch (m_ID)
	{
	case 1:
		if (m_position.x > -33 && m_position.x < 28)
		{
			if (m_Input->IsKeyDown('A'))
			{
				m_position.x -= 0.2f;
				pos.x -= 0.2f;
			}
			if (m_Input->IsKeyDown('D'))
			{
				m_position.x += 0.2f;
				pos.x += 0.2f;
			}
		}
		else
		{
			m_position.x = m_position.x > 0 ? 27.999 : -32.999;
			pos.x = m_position.x > 0 ? 27.999 : -32.999;
		}
		break;

	case 2:
		if (m_position.x > -33 && m_position.x < 28)
		{
			if (m_Input->IsKeyDown(37))
			{
				m_position.x -= 0.2f;
				pos.x -= 0.2f;
			}
			if (m_Input->IsKeyDown(39))
			{
				m_position.x += 0.2f;
				pos.x += 0.2f;
			}
		}
		else
		{
			m_position.x = m_position.x > 0 ? 27.999 : -32.999;
			pos.x = m_position.x > 0 ? 27.999 : -32.999;
		}
		break;
	default:

		break;
	}

	m_collider->SetPosition(pos.x, pos.y, pos.z);
	UpdateWorldMatrix();
}
void Paddle::Shutdown()
{
	ShutdownBuffers();
}