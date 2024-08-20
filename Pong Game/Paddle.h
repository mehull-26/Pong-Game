
#pragma once

#include "GameObject.h"
#include "InputClass.h"

class Paddle : public GameObject
{
public:
    Paddle(int ID);
    ~Paddle();

    bool Initialize(ID3D11Device* device, ID3D11DeviceContext*) override;
    bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) override;
    bool GroundRender(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float , float, XMFLOAT3) override { return true; };
    void Update(InputClass* m_Input);
    void Shutdown() override;

private:
	int m_ID;
};
