#include "BoxColliderComponent.h"

bool BoxColliderComponent::BoxVsBox(const BoxColliderComponent& other) const
{
    Vec2F thisMin = center - Size / 2;
    Vec2F thisMax = center + Size / 2;;
    Vec2F otherMin = other.center - other.Size / 2;
    Vec2F otherMax = other.center + other.Size / 2;

    return (thisMax.x >= otherMin.x && thisMin.x <= otherMax.x) &&
           (thisMax.y >= otherMin.y && thisMin.y <= otherMax.y);
}
