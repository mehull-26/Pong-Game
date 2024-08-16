#include "Paddle.h"

Paddle::Paddle()
{
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

void Paddle::Shutdown()
{
	ShutdownBuffers();
}