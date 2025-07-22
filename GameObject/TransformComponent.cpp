#include "TransformComponent.h"
#include "Event.h"
#include <cassert>
#include <iostream>

void TransformComponent::SetParent(TransformComponent* newParent)
{
	assert(newParent != this);
	assert(m_parent == nullptr);

	m_parent = newParent;
	m_parent->AddChild(this);

	SetDirty();
}

void TransformComponent::DetachFromParent()
{
	if (m_parent == nullptr) return;

	m_parent->RemoveChild(this);

	m_parent = nullptr;

	SetDirty();
}

void TransformComponent::AddChild(TransformComponent* child)
{
	Matrix3X2F childLocalTM = child->GetLocalMatrix();
	childLocalTM = childLocalTM * GetInverseWorldMatrix();

	auto m_noPivot = TM::RemovePivot(childLocalTM, child->GetPivotPoint());
	TM::DecomposeMatrix3X2(m_noPivot, child->m_position, child->m_rotation, child->m_scale);

	m_children.push_back(child);
}

void TransformComponent::RemoveChild(TransformComponent* child)
{
	Matrix3X2F childLocalTM = child->GetLocalMatrix();
	childLocalTM = childLocalTM * GetWorldMatrix();

	auto m_noPivot = TM::RemovePivot(childLocalTM, child->GetPivotPoint());
	TM::DecomposeMatrix3X2(m_noPivot, child->m_position, child->m_rotation, child->m_scale);

	m_children.erase(
		std::remove(m_children.begin(), m_children.end(), child),
		m_children.end()
	);
}

void TransformComponent::Translate(const Vec2F& delta)
{
	m_position.x += delta.x;
	m_position.y += delta.y;
	SetDirty();
}

void TransformComponent::Translate(const float x, const float y)
{
	m_position.x += x;
	m_position.y += y;
	SetDirty();
}

void TransformComponent::Rotate(float deg)
{
	m_rotation += deg;
	SetDirty();
}

TransformComponent::Vec2F TransformComponent::GetForward() const
{
	float radian = Math::DegToRad(m_rotation);
	return { std::cosf(radian), std::sinf(radian) };
}

const TransformComponent::Matrix3X2F& TransformComponent::GetWorldMatrix()
{
	if (m_isDirty) UpdateMatrices();
	return m_worldMatrix;
}

const TransformComponent::Matrix3X2F& TransformComponent::GetLocalMatrix()
{
	if (m_isDirty) UpdateMatrices();
	return m_localMatrix;
}

TransformComponent::Matrix3X2F TransformComponent::GetInverseWorldMatrix()
{
	Matrix3X2F inv = GetWorldMatrix();
	inv.Invert();
	return inv;
}

void TransformComponent::SetPivotPreset(PivotPreset preset, const D2D1_SIZE_F& size)
{
	switch (preset)
	{
	case PivotPreset::TopLeft:
		m_pivot = { 0.0f, 0.0f };
		break;
	case PivotPreset::TopRight:
		m_pivot = { size.width, 0.0f };
		break;
	case PivotPreset::BottomLeft:
		m_pivot = { 0.0f, size.height };
		break;
	case PivotPreset::BottomRight:
		m_pivot = { size.width, size.height };
		break;
	case PivotPreset::Center:
		m_pivot = { size.width * 0.5f, size.height * 0.5f };
		break;
	}
}

void TransformComponent::Update(float deltaTime)
{
	std::cout << 1 << std::endl;
	constexpr float moveSpeed = 100.0f; // 초당 이동 속도
	D2D1_POINT_2F delta = { 0.0f, 0.0f };

	if (m_IsWPressed) delta.y -= moveSpeed * deltaTime;
	if (m_IsAPressed) delta.x -= moveSpeed * deltaTime;
	if (m_IsSPressed) delta.y += moveSpeed * deltaTime;
	if (m_IsDPressed) delta.x += moveSpeed * deltaTime;
	std::cout << 2 << std::endl;
	m_position.x += delta.x;
	m_position.y += delta.y;

	if (delta.x != 0 || delta.y != 0)
		SetDirty();
}

void TransformComponent::OnEvent(EventType type, const void* data)
{
	if (type == EventType::KeyDown)
	{
		auto keyData = static_cast<const Events::KeyEvent*>(data);
		if (!keyData) return;

		bool isDown = (type == EventType::KeyDown);

		switch (keyData->key)
		{
		case 'W': m_IsWPressed = isDown; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressed = isDown; break;
		case 'D': m_IsDPressed = isDown; break;
		default: break;
		}
	}
	else
	{
		auto keyData = static_cast<const Events::KeyEvent*>(data);
		if (!keyData) return;

		bool isDown = (type == EventType::KeyDown);

		switch (keyData->key)
		{
		case 'W': m_IsWPressed = isDown; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressed = isDown; break;
		case 'D': m_IsDPressed = isDown; break;
		default: break;
		}
	}
}

void TransformComponent::UpdateMatrices()
{
	auto mat_scale = Matrix3X2F::Scale(m_scale.x, m_scale.y, D2D1::Point2F(m_pivot.x, m_pivot.y));

	auto mat_rot = Matrix3X2F::Rotation(m_rotation, D2D1::Point2F(m_pivot.x, m_pivot.y));

	auto mat_trans = Matrix3X2F::Translation(m_position.x, m_position.y);

	m_localMatrix = mat_scale * mat_rot * mat_trans;

	if (m_parent)
	{
		m_worldMatrix = m_localMatrix * m_parent->GetWorldMatrix();
	}
	else
	{
		m_worldMatrix = m_localMatrix;
	}

	m_isDirty = false;
}
