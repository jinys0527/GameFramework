#pragma once

#include <string>
#include <vector>
#include <memory>
#include "CoreTypes.h"

class Component;

class GameObject
{
public:
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		auto comp = std::make_unique<T>(std::forward<Args>(args)...);

		comp->SetOwner(this);

		T* ptr = comp.get();

		m_Components.emplace_back(std::move(comp));

		return ptr;
	}


	template<typename T>
	T* GetComponent() const 
	{
		for (auto& comp : m_Components)
		{
			if (auto ptr = dynamic_cast<T*>(comp.get()))
			{
				return ptr;
			}
		}

		return nullptr;
	}

	void Update(float deltaTime);

	void SendMessage(const myCore::MessageID msg, void* data = nullptr);
	
	void SendEvent(const std::string& evt);
protected:
	std::vector<std::unique_ptr<Component>> m_Components;
};

