#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>

void BoxColliderComponent::Start()
{
	GetEventDispatcher().AddListener(EventType::CollisionEnter, this);
	GetEventDispatcher().AddListener(EventType::CollisionStay, this);
	GetEventDispatcher().AddListener(EventType::CollisionExit, this);
}

bool BoxColliderComponent::BoxVsBox(const BoxColliderComponent& other) const
{
    Vec2F thisMin = center - Size / 2;
    Vec2F thisMax = center + Size / 2;;
    Vec2F otherMin = other.center - other.Size / 2;
    Vec2F otherMax = other.center + other.Size / 2;

    return (thisMax.x >= otherMin.x && thisMin.x <= otherMax.x) &&
           (thisMax.y >= otherMin.y && thisMin.y <= otherMax.y);
}

void BoxColliderComponent::Update(float deltaTime)
{
	auto* transform = m_owner->GetComponent<TransformComponent>();
	if (transform)
	{
		center = transform->GetPosition();
	}
}

void BoxColliderComponent::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::CollisionEnter:
		OnCollisionEnter(static_cast<const CollisionInfo*>(data));
		break;
	case EventType::CollisionStay:
		OnCollisionStay(static_cast<const CollisionInfo*>(data));
		break;
	case EventType::CollisionExit:
		OnCollisionExit(static_cast<const CollisionInfo*>(data));
		break;
	}
}

void BoxColliderComponent::OnDestroy()
{
	GetEventDispatcher().RemoveListener(EventType::CollisionEnter, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionStay, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionExit, this);
}
