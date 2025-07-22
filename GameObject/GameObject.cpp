#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

GameObject::GameObject(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher)
{
	TransformComponent* trans = AddComponent<TransformComponent>();
}

void GameObject::Update(float deltaTime)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Update(deltaTime);
	}
}

TransformComponent* GameObject::RenderPosition()
{
	SpriteRenderer* sr = GetComponent<SpriteRenderer>();
	if (sr != nullptr)
	{
		//sr->Render();
		auto it = m_Components.find(typeid(TransformComponent));
		if (it != m_Components.end()) {
			return dynamic_cast<TransformComponent*>(it->second.get());
		}
	}
	return nullptr;
}

SpriteRenderer* GameObject::RenderTexture()
{
	auto it = m_Components.find(typeid(SpriteRenderer));
	if (it != m_Components.end())
	{
		return dynamic_cast<SpriteRenderer*>(it->second.get());
	}
	return nullptr;
}



void GameObject::SendMessages(const myCore::MessageID msg, void* data /* = nullptr */)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->HandleMessage(msg, data);
	}
}


void GameObject::SendEvent(const std::string& evt)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		//it->second->OnEvent(evt);
	}
}