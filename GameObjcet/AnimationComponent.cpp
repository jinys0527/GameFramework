#include "AnimationComponent.h"

void AnimationComponent::Play(const std::string& name, bool loop /*= true*/)
{
	if (m_currentClipName == name) return;

	m_animationController.SetClip(m_clips[name]);
	m_animationController.SetLooping(loop);
	m_animationController.SetElapsed(0.f);
	m_currentClipName = name;
}

void AnimationComponent::Update(float deltaTime)
{
	m_animationController.Update(deltaTime);

	const Frame& frame = m_animationController.GetCurrentFrame();
}

void AnimationComponent::OnEvent(const std::string& evt)
{

}
