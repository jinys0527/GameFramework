#pragma once

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "CoreTypes.h"

class GameObject;

class Component
{
public:
	virtual ~Component() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void OnEvent(const std::string& evt) abstract;

	void HandleMessage(myCore::MessageID msg, void* data)
	{
		auto it = m_MessageHandlers.find(msg);
		if (it != m_MessageHandlers.end())
		{
			for (auto& handler : it->second)
			{
				handler(data);
			}
		}
	}

	using HandlerType = std::function<void(void*)>;
	void RegisterMessageHandler(myCore::MessageID msg, HandlerType handler)
	{
		m_MessageHandlers[msg].emplace_back(std::move(handler));
	}

	void SetOwner(GameObject* owner) { m_owner = owner; }

protected:
	GameObject* m_owner = nullptr;
	std::unordered_map<myCore::MessageID, std::vector<HandlerType>> m_MessageHandlers;
};