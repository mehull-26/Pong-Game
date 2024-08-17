#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Collider
{
public:
    Collider();
    ~Collider();

    void SetPosition(float x, float y, float z);
    XMFLOAT3 GetPosition() const;

    void SetSize(float width, float height, float depth);
    XMFLOAT3 GetSize() const;

    bool CheckCollision(const Collider& other) const;

private:
    XMFLOAT3 m_position;
    XMFLOAT3 m_size;
};
