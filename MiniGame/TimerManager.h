#pragma once
#include<chrono>

class GameState;

class TimerManager
{
private:
	std::chrono::duration<float> diff;
	GameState* gameState;
public:
	void TimeManagerInit(GameState* gs);
	void StartTimer();
	void ResetTimer();
	void UpdateCurrentTime();
	bool IsTimeOver();
};