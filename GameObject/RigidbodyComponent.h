#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"
#include "GameObject.h"
#include "TransformComponent.h"

class RigidbodyComponent : public Component
{
	using Vec2F = Math::Vector2F;
public:
	RigidbodyComponent(float mass = 1.0f, bool isKinematic = false) : mass(mass), isKinematic(isKinematic), velocity(0, 0), force(0, 0), gravity(0.0f, -9.8f), frictionCoefficient(0.1f)
	{
	}
	
	void Start()
	{
		transform = m_owner->GetComponent<TransformComponent>();
	}

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void AddForce(const Vec2F& f)
	{
		if (!isKinematic)
		{
			force += f;
		}
	}

	void Integrate(float deltaTime);

	void SetVelocity(const Vec2F& vel)
	{
		velocity = vel;
	}

	const Vec2F& GetVelocity() const 
	{
		return velocity;
	}
	
	void SetIsKinematic(bool value)
	{
		isKinematic = value;
	}

	bool IsKinematic() const { return isKinematic; }

	void SetGravity(const Vec2F& g) { gravity = g; }
	void SetFriction(float friction) { frictionCoefficient = friction; }
private:
	float mass;
	bool isKinematic;

	Vec2F velocity;
	Vec2F force;
	Vec2F gravity;
	float frictionCoefficient;

	TransformComponent* transform = nullptr;
};

