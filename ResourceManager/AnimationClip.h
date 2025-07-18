#pragma once

#include "d2d1helper.h"
#include <string>
#include <vector>

struct Frame
{
	D2D1_RECT_U srcRect;
	float		duration;

	float Width() const { return (float)srcRect.right - srcRect.left; }
	float Height() const { return (float)srcRect.bottom - srcRect.top; }

	D2D1_RECT_F ToRectF() const
	{
		return D2D1::RectF(
			static_cast<float>(srcRect.left),
			static_cast<float>(srcRect.top),
			static_cast<float>(srcRect.right),
			static_cast<float>(srcRect.bottom)
		);
	}
};


struct Tag
{
	std::string m_name;
	int m_from;
	int m_to;
	std::string m_direction;
};

class AnimationClip
{
public:
	AnimationClip() = default;
	~AnimationClip() = default;

	void AddFrame(const Frame& frame)
	{
		m_frames.emplace_back(frame);
		m_totalDuration += frame.duration;
	}

	void SetTextureKey(std::wstring key)
	{
		m_textureKey = key;
	}
	Frame& GetFrame(int index) { return m_frames[index]; }

	const std::vector<Frame>& GetFrames() const { return m_frames; }
	float GetTotalDuration() const { return m_totalDuration; }
	const std::wstring GetTextureKey() const { return m_textureKey; }

private:
	std::vector<Frame> m_frames;
	float m_totalDuration = 0.f;
	std::wstring m_textureKey;
};

