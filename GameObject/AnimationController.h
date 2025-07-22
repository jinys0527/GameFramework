#pragma once
#include "Component.h"
#include "AnimationClip.h"

class AnimationController : public Component
{
public:
	virtual ~AnimationController() = default;

	bool IsValid() const { return m_clip != nullptr; }

	void SetClip(const AnimationClip* clip);
	const AnimationClip* GetClip() const { return m_clip; }

	void SetLooping(bool loop);

	float GetElapsed() const { return m_elapsed; }
	void SetElapsed(float elapsedTime);

	const Frame& GetCurrentFrame() const;

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
private:
	const AnimationClip* m_clip = nullptr;
	float m_elapsed = 0.f;
	bool m_loop = true;
};