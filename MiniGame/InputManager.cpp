#include <conio.h>
#include "InputManager.h"
#include "GameManager.h"

Player::Dir InputManager::GetInputDir()
{
    if (!_kbhit())
        return Player::Dir::Idle;

    int input = _getch();

    if (input != 224)
        return Player::Dir::Idle;

    input = _getch();

    if (input == GameManager::LeftInput)
        return Player::Dir::Left;

    if (input == GameManager::RightInput)
        return Player::Dir::Right;

    return Player::Dir::Idle;
}
