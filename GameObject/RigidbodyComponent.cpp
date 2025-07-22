#include "RigidbodyComponent.h"

void RigidbodyComponent::Update(float deltaTime)
{
}

void RigidbodyComponent::OnEvent(EventType type, const void* data)
{
}

void RigidbodyComponent::Integrate(float deltaTime)
{
	if (isKinematic || !transform)
		return;

	//중력 적용
	Vec2F totalForce = force + gravity * mass;

	//마찰력 적용
	if (velocity.LengthSquared() > 0.00001f)
	{
		Vec2F frictionDir = -velocity.Normalized();
		Vec2F friction = frictionDir * frictionCoefficient * mass * 9.8f; // N ? mass * g
		totalForce += friction;
	}

	Vec2F acceleration = (mass > 0.0f) ? (totalForce / mass) : Vec2F(0, 0);
	velocity += acceleration * deltaTime;
	Vec2F newPos =  transform->GetPosition() + velocity * deltaTime;
	transform->SetPosition(newPos);

	// 너무 느리면 정지 (정밀도 오차 방지)
	if (velocity.LengthSquared() < 0.00001f)
		velocity = Vec2F(0, 0);

	force = Vec2F(0, 0);
}
