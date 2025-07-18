#include "CameraObject.h"
#include "CameraComponent.h"

CameraObject::CameraObject(float width, float height)
{
	AddComponent<CameraComponent>();
	auto* camera = GetComponent<CameraComponent>();
	camera->width = width;
	camera->height = height;
}
