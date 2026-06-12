#include <iostream>
#include <windows.h> // 콘솔 화면 초기화
#include <conio.h> // 방향키 입력
#include <format>
#include <random>
#include <algorithm>
#include "GameManager.h"

int main() // 무한의계단
{  
    std::ios_base::sync_with_stdio(false);

    GameManager game;
    game.Run();

    return 0;
}