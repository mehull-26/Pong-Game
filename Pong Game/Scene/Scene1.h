#pragma once

#include "Scene.h"


class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext*) override;
	void Update(float deltaTime, InputClass*) override;
	void Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* shaderc, XMMATRIX projectionMatrix) override;
	void Shutdown() override;
private:
	Paddle* m_paddle;
	Paddle* m_paddle1;
	Ball* m_ball;

	Paddle* m_bar0;
	Paddle* m_bar1;

	Ground* m_ground;

};

