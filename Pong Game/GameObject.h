// GameObject.h
#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include "ShaderManager.h"

using namespace DirectX;

class GameObject
{
protected:
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    struct ModelType
    {
        float x, y, z;
        float tu, tv;
        float nx, ny, nz;
    };

public:
    GameObject();
    virtual ~GameObject();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*, char*);
    void Shutdown();

    // Setters
    void SetPosition(float x, float y, float z);
    void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);

    // Getters
    XMFLOAT3 GetPosition() const;
    XMFLOAT3 GetScale() const;
	XMFLOAT3 GetRotation() const;

    // Update and Render methods
    virtual void Update(float deltaTime);
    virtual bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass *shaderManager, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) = 0;

protected:
    XMFLOAT3 m_position;
    XMFLOAT3 m_scale;
    XMFLOAT3 m_rotation;
    XMMATRIX m_worldMatrix;

    void UpdateWorldMatrix();
	bool LoadModel(const char* modelFilename);
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

    // Buffers
    ID3D11Buffer* m_vertexBuffer;
    ID3D11Buffer* m_indexBuffer;
	ModelType* m_model;
    int m_indexCount;
    int m_vertexCount;
};

