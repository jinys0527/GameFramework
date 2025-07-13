#include "Component.h"
#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
	for (auto& comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::SendMessage(const myCore::MessageID msg, void* data /* = nullptr */)
{
	for (auto& comp : m_Components)
	{
		comp->HandleMessage(msg, data);
	}
}


void GameObject::SendEvent(const std::string& evt)
{
	for (auto& comp : m_Components)
	{
		comp->OnEvent(evt);
	}
}