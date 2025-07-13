#include "AnimationController.h"

void AnimationController::SetClip(const AnimationClip* clip)
{
	m_clip = clip;
	m_elapsed = 0.f;
}

void AnimationController::SetLooping(bool loop)
{
	m_loop = loop;
}

void AnimationController::SetElapsed(float elapsedTime)
{
	m_elapsed = elapsedTime;
}

const Frame& AnimationController::GetCurrentFrame() const
{
	static Frame dummy{ {0, 0, 0, 0}, 0.f };

	if (!m_clip || m_clip->GetFrames().empty())
	{
		return dummy;
	}

	float accum = 0.f;
	for (auto& frame : m_clip->GetFrames())
	{
		accum += frame.duration;

		if (m_elapsed < accum)
			return frame;
	}

	return m_clip->GetFrames().back();
}

void AnimationController::Update(float deltaTime)
{
	if (!m_clip) return;
	m_elapsed += deltaTime;

	float total = m_clip->GetTotalDuration();

	if (m_loop)
	{
		if (m_elapsed >= total)
		{
			m_elapsed = std::fmod(m_elapsed, total);
		}
	}
	else
	{
		if (m_elapsed > total)
		{
			m_elapsed = total;
		}
	}
}

void AnimationController::OnEvent(const std::string& evt)
{

}