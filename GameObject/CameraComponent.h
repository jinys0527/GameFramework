#pragma once
#include "Component.h"
#include "CameraObject.h"

class CameraComponent : public Component
{
	friend class CameraObject;
public:
	virtual ~CameraComponent() = default;
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
protected:
	float width;
	float height;
};

