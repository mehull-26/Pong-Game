#include "Paddle.h"
#include <string>

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
				m_position.x -= 0.1f * sensitivity0;
				pos.x -= 0.1f * sensitivity0;
			}
			if (m_Input->IsKeyDown('D'))
			{
				m_position.x += 0.1f * sensitivity0;
				pos.x += 0.1f * sensitivity0;
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
				m_position.x -= 0.1f * sensitivity1;
				pos.x -= 0.1f * sensitivity1;
			}
			if (m_Input->IsKeyDown(39))
			{
				m_position.x += 0.1f * sensitivity1;
				pos.x += 0.1f * sensitivity1;
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

void Paddle::IncSensitivity(float s, int ID)
{
	OutputDebugString(L"ID: ");
	OutputDebugStringA(const_cast<char*>(std::to_string(ID).c_str()));
	OutputDebugStringA(" senstivity; ");
	if (ID == 0)
	{
		sensitivity0 += s;
		OutputDebugStringA(const_cast<char*>(std::to_string(sensitivity0).c_str()));
	}
	else if (ID == 1 && sensitivity1 > 0.08)
	{
		sensitivity1 += s;
		OutputDebugStringA(const_cast<char*>(std::to_string(sensitivity1).c_str()));
	}
	sensitivity0 = sensitivity0 < 0.1 ? 0.1 : sensitivity0;
	sensitivity1 = sensitivity1 < 0.1 ? 0.1 : sensitivity1;
	OutputDebugStringA("\n");
}