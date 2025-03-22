#include "shadermanager.h"

ShaderManagerClass::ShaderManagerClass()
{
    m_ColorShader = 0;
	m_MyShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
    bool result;

    // Create and initialize the texture shader object.
    m_ColorShader = new ColorShaderClass;

    result = m_ColorShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }


	m_MyShader = new MyShader;
	result = m_MyShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

    return true;
}

void ShaderManagerClass::Shutdown()
{
    // Release the texture shader object.
    if (m_ColorShader)
    {
        m_ColorShader->Shutdown();
        delete m_ColorShader;
        m_ColorShader = 0;
    }


	if (m_MyShader)
	{
		m_MyShader->Shutdown();
		delete m_MyShader;
		m_MyShader = 0;
	}
    return;
}

bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
    bool result;


    result = m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
    if (!result)
    {
        return false;
    }

    return true;
}


bool ShaderManagerClass::RenderMyShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float paddle1X, float paddle2X, XMFLOAT3 ballXYZ, XMFLOAT4 color)
{
    bool result;
	m_MyShader->m_lightColor = color;
    result = m_MyShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix,paddle1X, paddle2X, ballXYZ);
    if (!result)
    {
        return false;
    }

    return true;
}