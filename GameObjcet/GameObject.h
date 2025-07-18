#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "CoreTypes.h"

class Component;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		auto comp = std::make_unique<T>(std::forward<Args>(args)...);

		comp->SetOwner(this);

		T* ptr = comp.get();

		m_Components[typeid(T)] = comp;

		return ptr;
	}


	template<typename T>
	T* GetComponent() const 
	{
		auto it = m_Components.find(typeid(T));
		if (it != m_Components.end())
		{
			return static_cast<T*>(it->second.get());
		}

		return nullptr;
	}

	void Update(float deltaTime);

	void SendMessages(const myCore::MessageID msg, void* data = nullptr);
	
	void SendEvent(const std::string& evt);
protected:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
};

