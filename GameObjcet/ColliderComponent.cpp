#include "ColliderComponent.h"
#include "EventDispatcher.h"

void ColliderComponent::Start()
{
	EventDispatcher::Instance().AddListener(EventType::CollisionEnter, this);
	EventDispatcher::Instance().AddListener(EventType::CollisionStay, this);
	EventDispatcher::Instance().AddListener(EventType::CollisionExit, this);
}

void ColliderComponent::Update(float deltaTime)
{
}

void ColliderComponent::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::CollisionEnter:
		OnCollisionEnter(static_cast<CollisionInfo*>(data));
		break;
	case EventType::CollisionStay:
		OnCollisionStay(static_cast<CollisionInfo*>(data));
		break;
	case EventType::CollisionExit:
		OnCollisionExit(static_cast<CollisionInfo*>(data));
		break;
	}
}

void ColliderComponent::OnDestroy()
{
	EventDispatcher::Instance().RemoveListener(EventType::CollisionEnter, this);
	EventDispatcher::Instance().RemoveListener(EventType::CollisionStay, this);
	EventDispatcher::Instance().RemoveListener(EventType::CollisionExit, this);
}
