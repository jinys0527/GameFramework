#pragma once

enum class EventType
{
	//Input
	KeyDown,
	KeyUp,
	MouseClick,

	//UI
	ButtonPressed,
	SliderMoved,

	//Collision
	CollisionEnter,
	CollisionStay,
	CollisionExit,

	//Game
};

class IEventListener
{
public:
	virtual ~IEventListener() = default;
	virtual void OnEvent(EventType type, const void* data) = 0;
};
