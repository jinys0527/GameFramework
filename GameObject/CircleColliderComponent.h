#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent;

class CircleColliderComponent : public ColliderComponent
{
public:
	virtual ~CircleColliderComponent() = default;
	bool CircleVsCircle(const CircleColliderComponent& other) const;
	bool CircleVsBox(const BoxColliderComponent& other) const;
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
protected:
	float radius;
};

