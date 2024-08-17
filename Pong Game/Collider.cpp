#include "Collider.h"

Collider::Collider()
{
    m_position = { 0.0f, 0.0f, 0.0f };
    m_size = {1.0f, 1.0f, 1.0f};
}

Collider::~Collider()
{
}

void Collider::SetPosition(float x, float y, float z)
{
    m_position = XMFLOAT3(x, y, z);
}

XMFLOAT3 Collider::GetPosition() const
{
    return m_position;
}

void Collider::SetSize(float width, float height, float depth)
{
    m_size = XMFLOAT3(width, height, depth);
}

XMFLOAT3 Collider::GetSize() const
{
    return m_size;
}

bool Collider::CheckCollision(const Collider& other) const
{
    // Simple AABB (Axis-Aligned Bounding Box) collision detection
	return (fabs(m_position.x - other.m_position.x) * 2 < (m_size.x + other.m_size.x)) &&
           (fabs(m_position.z - other.m_position.z) * 2 < (m_size.z + other.m_size.z));
}
