#pragma once
#include <vector>
#include "CameraObject.h"

class NzWndBase;
class GameObject;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();
	virtual void Initialize(NzWndBase* pWnd) = 0;
	virtual void Finalize() = 0;

	virtual void Enter() = 0;
	virtual void Leave() = 0;

	virtual void FixedUpdate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hDC) = 0;

protected:
	std::vector<GameObject*> m_GameObjects;
	CameraObject m_Camera;
private:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;
};
