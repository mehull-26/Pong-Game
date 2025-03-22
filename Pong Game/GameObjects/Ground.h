
#pragma once

#include "GameObject.h"
#include "InputClass.h"

class Ground : public GameObject
{
public:
    Ground();
    ~Ground();

    bool Initialize(ID3D11Device* device, ID3D11DeviceContext*) override;
	bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) override { return true; }
    bool GroundRender(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float paddle1X, float paddle2X, XMFLOAT3 ballXYZ) override;
    void Update(InputClass* m_Input, bool);
    void Shutdown() override;

private:
	void Blink(bool);
};
