// GameObject.cpp
#include "GameObject.h"

GameObject::GameObject()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_worldMatrix = XMMatrixIdentity();
    m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_model = 0;
    UpdateWorldMatrix();
}

GameObject::~GameObject()
{
}

bool GameObject::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* modelFilename, char* textureFilename, char* normalMapFilename, char* specularMapFilename)
{
    bool result;

	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

    result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

    return true;
}

void GameObject::Shutdown()
{
    if (m_vertexBuffer)
    {
        m_vertexBuffer->Release();
        m_vertexBuffer = nullptr;
    }

    if (m_indexBuffer)
    {
        m_indexBuffer->Release();
        m_indexBuffer = nullptr;
    }
    
    ShutdownBuffers();
}

bool GameObject::LoadModel(const char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

bool GameObject::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices = new VertexType[m_vertexCount];
	D3D11_BUFFER_DESC vertexBufferDesc;
	unsigned long* indices = new unsigned long[m_indexCount];

	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
		indices[i] = i;
	}

	// Set up vertex buffer description
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}



	// Set up index buffer description
	D3D11_BUFFER_DESC indexBufferDesc ;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void GameObject::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void GameObject::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
}

void GameObject::UpdateWorldMatrix()
{
    // Create transformation matrices
    XMMATRIX scaleMatrix = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
    XMMATRIX translationMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

    // Combine transformations
    m_worldMatrix = scaleMatrix * translationMatrix * rotationMatrix;
}

void GameObject::SetPosition(float x, float y, float z)
{
    m_position = XMFLOAT3(x, y, z);
    UpdateWorldMatrix();
}

void GameObject::SetScale(float x, float y, float z)
{
    m_scale = XMFLOAT3(x, y, z);
    UpdateWorldMatrix();
}
\
void GameObject::SetRotation(float x, float y, float z)
{
    m_rotation = XMFLOAT3(x, y, z);
    UpdateWorldMatrix();
}

XMFLOAT3 GameObject::GetPosition() const
{
    return m_position;
}

XMFLOAT3 GameObject::GetScale() const
{
    return m_scale;
}

XMFLOAT3 GameObject::GetRotation() const
{
    return m_rotation;
}

void GameObject::Update(float deltaTime)
{
    // Update logic for the game object
}