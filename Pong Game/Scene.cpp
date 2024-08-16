#include "Scene.h"

Scene::Scene()
{
	m_camera = 0;
}

Scene::~Scene()
{
}

bool Scene::Initialize(ID3D11Device* device)
{
    bool result;

	m_camera = new CameraClass();
	m_camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_camera->Render();

	m_camera->GetViewMatrix(m_viewMatrix);
	

    return true;
}

void Scene::Shutdown()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

}