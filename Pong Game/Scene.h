#pragma once

#include <vector>

#include "Camera.h"
#include "Paddle.h"
#include "GameObject.h"

class Scene
{
public:
    Scene();
    ~Scene();

    // Scene lifecycle methods
    virtual bool Initialize(ID3D11Device* device);
    virtual void Update(float deltaTime) = 0;
    virtual void Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shader, XMMATRIX projectionMatrix) = 0;
	virtual void Shutdown();
protected:
	CameraClass* m_camera;
	XMMATRIX m_viewMatrix;

};
