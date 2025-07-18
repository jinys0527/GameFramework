#pragma once
#include "Component.h"
#include "TMHelper.h"
#include <vector>


enum class PivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

class TransformComponent : public Component
{
public:
	using Vec2F = Math::Vector2F;
	using Matrix3X2F = D2D1::Matrix3x2F;

	TransformComponent() : m_position{ 0, 0 }, m_rotation(0.0f), m_scale{ 1.0f, 1.0f }, m_isDirty(false), m_parent(nullptr)
	{
		m_localMatrix = D2D1::Matrix3x2F::Identity();
		m_worldMatrix = D2D1::Matrix3x2F::Identity();
	}

	virtual ~TransformComponent()
	{
		for (auto* child : m_children)
		{
			child->m_parent = nullptr;
		}
	}

	TransformComponent* GetParent() const { return m_parent; }

	void SetParent(TransformComponent* newParent);
	void DetachFromParent();

	void AddChild(TransformComponent* child);
	void RemoveChild(TransformComponent* child);

	void SetPosition(const Vec2F& pos) { m_position = pos; SetDirty(); }
	void SetRotation(const float deg) { m_rotation = deg; SetDirty(); }
	void SetScale(const Vec2F& scale) { m_scale = scale; SetDirty(); }

	const Vec2F& GetPosition() const { return m_position; }
	float GetRotation() const { return m_rotation; }
	const Vec2F& GetScale() const { return m_scale; }

	void Translate(const Vec2F& delta);
	void Translate(const float x, const float y);

	void Rotate(float deg);

	Vec2F GetForward() const;

	const Matrix3X2F& GetWorldMatrix();
	const Matrix3X2F& GetLocalMatrix();

	Matrix3X2F GetInverseWorldMatrix();

	void SetPivotPreset(PivotPreset preset, const D2D1_SIZE_F& size);
	D2D1_POINT_2F GetPivotPoint() const { return m_pivot; }

private:
	void SetDirty()
	{
		m_isDirty = true;
		for (auto* child : m_children)
		{
			child->SetDirty();
		}
	}

	void UpdateMatrices();

private:
	Vec2F m_position;
	float m_rotation = 0.0f;
	Vec2F m_scale = { 1.0f, 1.0f };

	D2D1_POINT_2F m_pivot = { 0.0f, 0.0f };

	TransformComponent* m_parent = nullptr;
	std::vector<TransformComponent*> m_children;

	Matrix3X2F m_localMatrix;
	Matrix3X2F m_worldMatrix;

	bool m_isDirty = true;

	int zOrder = 0;
};

	