#include "ScoreManager.h"
#include "GameManager.h"
#include <cmath>

void ScoreManager::ScoreManagerInit(GameState* gS)
{
	gameState = gS;
}
void ScoreManager::AddScore()
{
	gameState->Score += gameState->Level;
}

void ScoreManager::IncreaseLevel()
{
	gameState->Level++;
	UpdateLevelTime();
}

void ScoreManager::UpdateLevelTime()
{
	gameState->LevelTime = std::max<float>(
		GameManager::MinLevelTime,
		5.f- static_cast<float>(gameState->Level - 1) * GameManager::LevelMinusTime
	);
}
