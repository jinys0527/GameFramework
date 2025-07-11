#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <chrono>

class GameTimer
{
public:
	GameTimer();

	float TotalTime() const;
	float DeltaTime() const;
	float DeltaTimeMs() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	TimePoint mStartTime;
	TimePoint mStopTime;
	TimePoint mPrevTime;
	TimePoint mCurrTime;
	Duration mPausedDuration;

	Duration mDeltaTime;
	bool mStopped = false;
};

#endif // GAMETIMER_H

