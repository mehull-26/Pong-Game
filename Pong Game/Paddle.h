#pragma once
// Paddle.h
#pragma once

#include "GameObject.h"

class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle();

    bool Initialize(ID3D11Device* device);
    bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) override;
    void Shutdown();
};
