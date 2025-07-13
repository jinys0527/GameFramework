#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"
#include <vector>

class TransformComponent : public Component
{
	using Vector2F = Math::Vector2F;
	using Matrix3X2F = D2D1_MATRIX_3X2_F;
private:
	Vector2F position;
	float rotation = 0.0f;
	Vector2F scale = { 1.0f, 1.0f };

	Vector2F pivot = { 0.5f, 0.5f };

	TransformComponent* parent = nullptr;
	std::vector<TransformComponent*> children;

	Matrix3X2F localMatrix;
	Matrix3X2F worldMatrix;

	bool isDirty = true;

	int zOrder = 0;
};

