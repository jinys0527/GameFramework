#pragma once
#include "GameObject.h"

class CameraObject : public GameObject
{
public:
	CameraObject(float width, float height);
	virtual ~CameraObject() = default;
};

