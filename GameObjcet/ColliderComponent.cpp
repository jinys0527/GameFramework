#include "ColliderComponent.h"
#include "EventDispatcher.h"

void ColliderComponent::Start()
{
	m_EventDispatcher.AddListener(EventType::CollisionEnter, this);
	m_EventDispatcher.AddListener(EventType::CollisionStay, this);
	m_EventDispatcher.AddListener(EventType::CollisionExit, this);
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
	m_EventDispatcher.RemoveListener(EventType::CollisionEnter, this);
	m_EventDispatcher.RemoveListener(EventType::CollisionStay, this);
	m_EventDispatcher.RemoveListener(EventType::CollisionExit, this);
}
