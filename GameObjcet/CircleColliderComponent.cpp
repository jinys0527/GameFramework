#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"

bool CircleColliderComponent::CircleVsCircle(const CircleColliderComponent& other) const
{
	float distSq = (this->center - other.center).LengthSquared();
	float radiusSum = this->radius + other.radius;

	return distSq <= radiusSum * radiusSum;
}

bool CircleColliderComponent::CircleVsBox(const BoxColliderComponent& other) const
{
	Vec2F boxMin = other.center - other.Size / 2;
	Vec2F boxMax = other.center + other.Size / 2;  
	Vec2F closest = Clamp(this->center, boxMin,  boxMax);

	float distSq = (this->center - closest).LengthSquared();

	return distSq <= this->radius * this->radius;
}
