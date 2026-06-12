#include "TimerManager.h"
#include "GameState.h"
#include <chrono>

void TimerManager::TimeManagerInit(GameState* gs)
{
    gameState = gs;
}

void TimerManager::StartTimer()
{
    gameState->KeyPressTime = std::chrono::system_clock::now();
}

void TimerManager::ResetTimer()
{
    gameState->KeyPressTime = std::chrono::system_clock::now();
}

void TimerManager::UpdateCurrentTime()
{   
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    diff = now - gameState->KeyPressTime;

    gameState->CurrentTime = gameState->LevelTime - diff.count();
}

bool TimerManager::IsTimeOver()
{
    UpdateCurrentTime();
    return gameState->CurrentTime <= 0.f;
}