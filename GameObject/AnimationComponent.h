#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>
#include "AnimationController.h"

class AnimationClip;

class AnimationComponent : public Component
{
public:
	void AddClip(const std::string& name, const AnimationClip* clip)
	{
		m_Clips[name] = clip;
	}

	void Play(const std::string& name, bool loop = true);

	void Update(float deltaTime) override;

	void OnEvent(EventType type, const void* data) override;

private:
	using AnimationMap = std::unordered_map<std::string, const AnimationClip*>;

	AnimationMap m_Clips;
	AnimationController m_AnimationController;
	std::string m_CurrentClipName;
};
