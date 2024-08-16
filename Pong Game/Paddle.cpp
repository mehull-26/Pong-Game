#include "Paddle.h"

Paddle::Paddle(int ID)
{
	m_ID = ID;
}                  

Paddle::~Paddle()
{
}

bool Paddle::Initialize(ID3D11Device* device) 
{
    bool result;
	char modelFilename[128];

	strcpy_s(modelFilename, "data/paddle.txt");
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
	switch (m_ID)
	{
	case 1:
		if (m_Input->IsKeyDown('A'))
		{
			m_position.x -= 0.1f;
		}
		if (m_Input->IsKeyDown('D'))
		{
			m_position.x += 0.1f;
		}
		break;

	case 2:
		if (m_Input->IsKeyDown(37))
		{
			m_position.x -= 0.1f;
		}
		if (m_Input->IsKeyDown(39))
		{
			m_position.x += 0.1f;
		}
		break;
	}
	UpdateWorldMatrix();
}
void Paddle::Shutdown()
{
	ShutdownBuffers();
}