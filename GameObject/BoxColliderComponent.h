#pragma once
#include "ColliderComponent.h"
#include "SimpleMathHelper.h"
#include <iostream>

class BoxColliderComponent : public ColliderComponent
{
	using Vec2F = Math::Vector2F;
	friend class CircleColliderComponent;
public:
	virtual ~BoxColliderComponent() { OnDestroy(); }
	void Start() override;
	bool BoxVsBox(const BoxColliderComponent& other) const;
	void SetSize(const Vec2F& size) {
		Size = size;
	}

	const Vec2F& GetSize() const {
		return Size;
	}
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	void OnDestroy() override;
protected:
	Vec2F Size;
	void OnCollisionEnter(const CollisionInfo* info) override { std::cout << "enter" << std::endl; }
	void OnCollisionStay(const CollisionInfo* info) override { std::cout << "stay" << std::endl; }
	void OnCollisionExit(const CollisionInfo* info) override { std::cout << "exit" << std::endl; }
};

