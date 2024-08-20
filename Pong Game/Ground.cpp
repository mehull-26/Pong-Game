#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

bool Ground::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;
	char modelFilename[128];


	strcpy_s(modelFilename, "data/ground.txt");
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

bool Ground::GroundRender(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float paddle1X, float paddle2X, XMFLOAT3 ballXYZ)
{
	bool result;
	RenderBuffers(deviceContext);

	result = shaderManager->RenderMyShader(deviceContext, m_indexCount, m_worldMatrix, viewMatrix, projectionMatrix, paddle1X, paddle2X, ballXYZ);
	if (!result)
	{
		return false;
	}
	return true;
}

void Ground::Update(InputClass* m_Input)
{
	UpdateWorldMatrix();
}
void Ground::Shutdown()
{
	ShutdownBuffers();
}