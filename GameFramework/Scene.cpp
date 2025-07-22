#include "pch.h"
#include "Scene.h"

Scene::~Scene()
{
	for (auto gameObject : m_GameObjects)
	{
		delete gameObject;
	}
}
