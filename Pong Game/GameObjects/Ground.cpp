#include "Ground.h"
#include <chrono>

double GetTimeG()
{
	using namespace std::chrono;
	return duration<double>(steady_clock::now().time_since_epoch()).count();
}

Ground::Ground()
{
	m_color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
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

	result = shaderManager->RenderMyShader(deviceContext, m_indexCount, m_worldMatrix, viewMatrix, projectionMatrix, paddle1X, paddle2X, ballXYZ,m_color);
	if (!result)
	{
		return false;
	}
	return true;
}

void Ground::Update(InputClass* m_Input, bool PLAY)
{
	if (!PLAY)
	{
		static double accumulator = 0;
		static double PrevTime = GetTimeG();
		accumulator += GetTimeG() - PrevTime;
		if (accumulator < 0.5)
		{
			m_color = XMFLOAT4(1.0f, 0.3f, 0.3f, 1.0f);
		}
		else if (accumulator >= 0.8)
		{
			accumulator = 0;
		}
		else if (accumulator >= 0.5)
		{
			m_color = XMFLOAT4(1.0f, 1.0f, 1.2f, 1.0f);
		}
		PrevTime = GetTimeG();
	}
	else m_color = XMFLOAT4(0.0f, 1.0f, 0.8f, 1.0f);
	UpdateWorldMatrix();
}
void Ground::Shutdown()
{
	ShutdownBuffers();
}

void Ground::Blink(bool PLAY)
{

}