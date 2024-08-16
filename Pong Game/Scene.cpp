#include "Scene.h"
#include <chrono>
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
	m_camera->SetPosition(8.0f,10.0f, -7.0f);
	m_camera->SetRotation(40.0f, -30.0f, 0.0f);

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

double Scene::GetTime() 
{
	using namespace std::chrono;
	return duration<double>(steady_clock::now().time_since_epoch()).count();
}