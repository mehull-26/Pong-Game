#pragma once

#include "GameObject.h"
#include "InputClass.h"
<<<<<<< HEAD
=======

>>>>>>> 40ba415732d1938f446a97c226694130a2f9f3a5

class Ball : public GameObject
{
public:
    Ball();
    ~Ball();

    bool Initialize(ID3D11Device* device, ID3D11DeviceContext*) override;
    bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) override;
    bool GroundRender(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float, float, XMFLOAT3) override { return true; };
    void Update(InputClass* m_Input, int Collision);
    void Shutdown() override;
    void SetVelocity(float x, float y, float z);

private:
	XMFLOAT3 m_speed;
    XMFLOAT3 m_direction;
    bool PLAY;
	void P1Lose();
	void P2Lose();
};
