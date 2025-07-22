#include "CameraObject.h"
#include "CameraComponent.h"

CameraObject::CameraObject(EventDispatcher eventDispatcher, float width, float height) : GameObject(eventDispatcher)
{
	AddComponent<CameraComponent>();
	auto* camera = GetComponent<CameraComponent>();
	camera->width = width;
	camera->height = height;
}
