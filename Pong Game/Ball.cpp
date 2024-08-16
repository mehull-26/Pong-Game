#include "Ball.h"

Ball::Ball()
{
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
}
void Ball::Shutdown()
{
	ShutdownBuffers();
}