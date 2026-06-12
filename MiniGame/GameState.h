#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <random>

class GameState
{
public:
    int Score = 0;
    int Level = 1;
    int Count = 0;
    int LastStairX; // 생성된 제일 꼭대기 계단의 중간값
    float LevelTime = 5.f; // 레벨에 따른 정지허용시간
    float CurrentTime; // 현재 남은 정지허용시간
    bool IsGameOver = false;

    std::chrono::system_clock::time_point KeyPressTime;
    const std::chrono::system_clock::time_point TimeCmp;      // KeyPressTime이 빈 값인지 비교하기 위한 빈 변수
};

