#pragma once
#include "Component.h"
#include "FSM.h"
#include <string>

class FSMComponent : public Component
{
public:
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

private:
	FSM fsm;
};

