#pragma once

#include <vector>

#include "InputClass.h"
#include "Camera.h"
#include "Paddle.h"
#include "Ball.h"
#include "Ground.h"
#include "GameObject.h"

class Scene
{
public:
    Scene();
    ~Scene();

    // Scene lifecycle methods
    virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
    virtual void Update(float deltaTime, InputClass* m_Input) = 0;
    virtual void Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shader, XMMATRIX projectionMatrix) = 0;
	virtual void Shutdown();
	double GetTime();
protected:
	CameraClass* m_camera;
	XMMATRIX m_viewMatrix;

};
