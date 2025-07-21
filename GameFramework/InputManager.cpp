#include "pch.h"
#include "InputManager.h"
#include "EventDispatcher.h"
#include "Event.h"
#include <iostream>

InputManager::InputManager(EventDispatcher& dispatcher) : m_EventDispatcher(dispatcher)
{

}

void InputManager::Update()
{
	for (const auto& key : keysDown)
	{
		if (!keysDownPrev.contains(key))
		{
			Events::KeyEvent e{ key };
			m_EventDispatcher.Dispatch(EventType::KeyDown, &e);
		}
	}

	for (const auto& key : keysDownPrev)
	{
		if (!keysDown.contains(key))
		{
			Events::KeyEvent e{ key };
			m_EventDispatcher.Dispatch(EventType::KeyUp, &e);
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

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)
	{

	case WM_KEYDOWN:
	{
		OnKeyDown(static_cast<char>(msg.wParam));
	}
	break;

	case WM_KEYUP:
	{
		OnKeyUp(static_cast<char>(msg.wParam));
	}
	break;

	//case WM_MOUSEMOVE:
	//case WM_LBUTTONDOWN:
	//case WM_LBUTTONUP:
	//case WM_RBUTTONDOWN:
	//case WM_RBUTTONUP:
	//{
	//	HandleMsgMouse(msg);
	//}
	//break;

	default:
		return false; // Unhandled message
	}

	return true;
}
