#include "Player.h"
#include "GameManager.h"

void Player::PlayerInit(GameMap* gM, GameState* gS)
{
    gameMap = gM;
    gameState = gS;
}

void Player::MoveHuman(Dir dir)
{
    if (dir == Dir::Left)
    {
        SetPlayerDir(Dir::Left);
        SetPlayerY(GameManager::HumanHeight + 1);
        SetPlayerX(GetPlayerX() - GameManager::BlockSize);
    }
    else if (dir == Dir::Right)
    {
        SetPlayerDir(Dir::Right);
        SetPlayerY(GameManager::HumanHeight + 1);
        SetPlayerX(GetPlayerX() + GameManager::BlockSize);
    }
    gameState->IsGameOver = bGameOverCheck();
}

bool Player::bGameOverCheck()
{
    bool bReturn;

    if (PlayerX == gameMap->GetStairXPositions()[gameState->Count])
        bReturn = false;
    else
        bReturn = true;

    return bReturn;
}