#include "InputManager.h"
#include "EventDispatcher.h"
#include "Event.h"
#include <iostream>

void InputManager::Update()
{
	for (const auto& key : keysDown)
	{
		if (!keysDownPrev.contains(key))
		{
			Events::KeyEvent e{ key };
			EventDispatcher::Instance().Dispatch(EventType::KeyDown, &e);
		}
	}

	for (const auto& key : keysDownPrev)
	{
		if (!keysDown.contains(key))
		{
			Events::KeyEvent e{ key };
			EventDispatcher::Instance().Dispatch(EventType::KeyUp, &e);
		}
	}

	keysDownPrev = keysDown;
}

void InputManager::OnKeyDown(char key)
{
	keysDown.insert(key);
}

void InputManager::OnKeyUp(char key)
{
	keysDown.erase(key);
}

bool InputManager::IsKeyPressed(char key) const
{
	return keysDown.contains(key);
}
