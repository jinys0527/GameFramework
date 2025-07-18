#pragma once
#include "ColliderComponent.h"
#include "SimpleMathHelper.h"

class BoxColliderComponent : public ColliderComponent
{
	using Vec2F = Math::Vector2F;
	friend class CircleColliderComponent;
public:
	virtual ~BoxColliderComponent() = default;
	bool BoxVsBox(const BoxColliderComponent& other) const;
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
protected:
	Vec2F Size;
};

