#include "MapGenerator.h"
#include "GameManager.h"
#include <random>

void MapGenerator::MapGeneratorInit(GameState* gS, Renderer* ren, GameMap* gM)
{
    gameState = gS;
    renderer = ren;
    gameMap = gM;
}

void MapGenerator::CreateFirstMap()
{
    gameMap->PushBackStairXPositions(FirstStairX);

    for (int i = 0; i < GameManager::Height; i++)
    {
        std::string CurrentFloor;

        if ((i - 3) % 4 == 0 && i > 2)
        {
            int StairStart = gameState->LastStairX - 2;
            int StairEnd = gameState->LastStairX + 2;
            for (int j = 0; j <= StairStart; j++)
                CurrentFloor += GameManager::Blank;
            CurrentFloor += GameManager::ABlock;
            for (int j = StairEnd; j < GameManager::Width; j++)
                CurrentFloor += GameManager::Blank;

            PlaceNextStairs();
        }
        else
        {
            for (int i = 0; i < GameManager::Width; i++)
                CurrentFloor += GameManager::Blank;
        }
        gameMap->PushBackGameMap(CurrentFloor);
    }
    renderer->SavePlayerToBuffer();
}

void MapGenerator::UpdateMap()
{
    if (gameState->Count != 1)
    {
        gameMap->EraseGameMap(GameManager::StairGap);
        for (int i = 0; i < GameManager::StairGap; i++)
        {
            std::string CurrentFloor;

            if (i % 4 == 0)
            {
                int StairStart = gameState->LastStairX - 1;
                int StairEnd = gameState->LastStairX + 2;
                for (int j = 0; j < StairStart; j++)
                    CurrentFloor += GameManager::Blank;
                CurrentFloor += GameManager::ABlock;
                for (int j = StairEnd; j < GameManager::Width; j++)
                    CurrentFloor += GameManager::Blank;
                PlaceNextStairs();
            }
            else
            {
                for (int j = 0; j < GameManager::Width; j++)
                    CurrentFloor += GameManager::Blank;
            }
            gameMap->PushBackGameMap(CurrentFloor);
        }
    }
}

void MapGenerator::PlaceNextStairs()
{
    int NextStairX;
    if (gameState->LastStairX == 2)
        NextStairX = gameState->LastStairX + GameManager::BlockSize;
    else if (gameState->LastStairX == 20)
        NextStairX = gameState->LastStairX - GameManager::BlockSize;
    else
    {
        std::uniform_int_distribution<int> dis(0, 1);

        NextStairX = (dis(RandomEngine) == 0 ? gameState->LastStairX - GameManager::BlockSize : gameState->LastStairX + GameManager::BlockSize);
    }

    gameState->LastStairX = NextStairX;
    gameMap->PushBackStairXPositions(gameState->LastStairX);
}