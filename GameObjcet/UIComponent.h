#pragma once
#include "Component.h"
#include <vector>

class RectTransformComponent;

class UIComponent : public Component
{
public:
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
protected:
	RectTransformComponent* m_RectTransform = nullptr;

	enum class UIInteractionState {None, Hovered, Pressed, Released};
	UIInteractionState m_State = UIInteractionState::None;

	bool m_bVisible = true;
	int m_ZOrder = 0;
	float m_Opacity = 1.0f;
};

