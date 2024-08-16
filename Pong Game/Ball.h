#pragma once

#include "GameObject.h"
#include "InputClass.h"

class Ball : public GameObject
{
public:
    Ball();
    ~Ball();

    bool Initialize(ID3D11Device* device) override;
    bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) override;
    void Update(InputClass* m_Input);
    void Shutdown() override;

private:
};
