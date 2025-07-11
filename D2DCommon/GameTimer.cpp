#include "pch.h"
#include "GameTimer.h"

GameTimer::GameTimer() 
{
	Reset();
}

float GameTimer::TotalTime() const
{
	if (mStopped)
	{
		return std::chrono::duration<float>(mStopTime - mStartTime - mPausedDuration).count();
	}
	else
	{
		return std::chrono::duration<float>(Clock::now() - mStartTime - mPausedDuration).count();
	}
}

float GameTimer::DeltaTime() const
{
	return mDeltaTime.count();
}

float GameTimer::DeltaTimeMs() const
{
	return mDeltaTime.count() * 1000.0f;
}

void GameTimer::Reset()
{
	mStartTime = Clock::now();
	mPrevTime = mStartTime;
	mPausedDuration = Duration::zero();
	mStopped = false;
}

void GameTimer::Start()
{
	if (mStopped)
	{
		auto startAgain = Clock::now();
		mPausedDuration += startAgain - mStopTime;
		mPrevTime = startAgain;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!mStopped)
	{
		mStopTime = Clock::now();
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = Duration::zero();
		return;
	}

	mCurrTime = Clock::now();
	mDeltaTime = mCurrTime - mPrevTime;
	mPrevTime = mCurrTime;

	if (mDeltaTime.count() < 0.0f)
	{
		mDeltaTime = Duration::zero();
	}
}
