#pragma once

#include "Scene.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();
	bool Initialize(ID3D11Device* device) override;
	void Update(float deltaTime) override;
	void Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderc, XMMATRIX projectionMatrix) override;
private:
	Paddle* m_paddle;
	Paddle* m_paddle1;

};

