#ifndef _LTCshader_H_
#define _LTCshader_H_


#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;



class LTCshader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT3 Intensity;
		float PaddingI;
		XMFLOAT3 Color;
		float PaddingC;
	};

	struct LightPointType
	{
		XMFLOAT3 AreaLightPoint0InWorld;
		float LightPad2;
		XMFLOAT3 AreaLightPoint1InWorld;
		float LightPad3;
		XMFLOAT3 AreaLightPoint2InWorld;
		float LightPad4;
		XMFLOAT3 AreaLightPoint3InWorld;
		float LightPad5;
	};

	struct MaterialBufferType
	{
		XMFLOAT3 BaseColor;
		float Roughness;
		XMFLOAT3 CameraPosition;
		float Metallic;
	};


public:
	LTCshader();
	LTCshader(const LTCshader&);
	~LTCshader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_lightPointBuffer;
	ID3D11Buffer* m_materialBuffer;
	ID3D11SamplerState* m_sampleState;

};

#endif