#include "GameManager.h"

void GameManager::Init()
{
    scoreManager.ScoreManagerInit(&gameState);
    timerManager.TimeManagerInit(&gameState);
    renderer.ScreenInit(&gameMap, &gameState, &mapGenerator, &player);
    mapGenerator.MapGeneratorInit(&gameState, &renderer, &gameMap);
    renderer.SetTerminalSizeVT(FullWidth, FullHeight + 1); // 원하는 가로, 세로
    player.PlayerInit(&gameMap, &gameState);

    gameState.LastStairX = mapGenerator.GetFirstStairX();

    player.SetPlayerY(0);
    player.SetPlayerX(gameState.LastStairX - BlockSize);

    mapGenerator.SetRandomeEngine();
    
    gameState.CurrentTime = gameState.LevelTime;

    player.SetPlayerDir(Player::Dir::Idle);
    mapGenerator.CreateFirstMap();
}

void GameManager::Run()
{
    Init();
    //renderer.PrintTitle();
    //renderer.PrintCountdown();
    Update();
}

void GameManager::Update()
{
    while (!gameState.IsGameOver)
    {
        renderer.ScreenClear();
        renderer.SaveMapToBuffer();

        if (gameState.KeyPressTime != gameState.TimeCmp)
        {
            timerManager.UpdateCurrentTime();
            gameState.IsGameOver = timerManager.IsTimeOver(); // 마지막에 누른 시간과 현재 시간 비교
        }
        if (gameState.IsGameOver)
            break;

        Player::Dir dir = inputManager.GetInputDir();

        if (dir != Player::Dir::Idle)
        {
            renderer.StartScreenShake();
            timerManager.StartTimer();

            renderer.ClearPlayerPosition(player.GetPlayerY(), player.GetPlayerX());
            player.MoveHuman(dir);

            if (gameState.IsGameOver)
                break;

            if (timerManager.IsTimeOver())
            {
                gameState.IsGameOver = true;
                break;
            }

            gameState.Count++;
            mapGenerator.UpdateMap();
            renderer.SavePlayerToBuffer();

            scoreManager.AddScore();

            if (gameState.Count % LevelCount == 0)
                scoreManager.IncreaseLevel();
        }
        else
        {
            renderer.StopScreenShake();
        }
        renderer.ScreenFlipping();
    }
    GameOver();

    renderer.ScreenRelease();
}

void GameManager::GameOver()
{
    renderer.PrintGameOver(gameState.Level, gameState.Score);
}