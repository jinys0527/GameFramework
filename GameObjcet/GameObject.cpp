#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"

GameObject::GameObject()
{
	AddComponent<TransformComponent>();
}

void GameObject::Update(float deltaTime)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Update(deltaTime);
	}
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
		it->second->OnEvent(evt);
	}
}