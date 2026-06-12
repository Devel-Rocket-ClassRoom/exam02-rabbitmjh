#pragma once

class GameState;

class ScoreManager
{
private:
	GameState* gameState;
public:
	void ScoreManagerInit(GameState* gS);
	void AddScore();
	void IncreaseLevel();
	void UpdateLevelTime();
};