////////////////////
#ifndef _GRAPHIC_CLASS_
#define _GRAPHIC_CLASS_


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass& other);
	~GraphicsClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	void BeginScene(float, float, float, float);
	void EndScene();





private:
	bool m_vsync_enabled;
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
	D3D11_VIEWPORT m_viewport;
	ID3D11DepthStencilState* m_depthDisabledStencilState;

};

#endif