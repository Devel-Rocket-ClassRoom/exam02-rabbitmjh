#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "GameMap.h"
#include "GameState.h"
#include "InputManager.h"
#include "MapGenerator.h"
#include "Player.h"
#include "Renderer.h"
#include "ScoreManager.h"
#include "TimerManager.h"


class GameManager
{
private:
	GameMap gameMap;
	GameState gameState;
	InputManager inputManager;
	MapGenerator mapGenerator;
	Player player;
	Renderer renderer;
	ScoreManager scoreManager;
	TimerManager timerManager;

public:
	GameManager() = default;
	~GameManager() = default;

	static const int LeftInput = 75;
	static const int RightInput = 77;
	static const char Blank = ' ';
	inline static const std::string Block = "███"; // 출력용 블록
	inline static const std::string ABlock = "###";   // 아스키코드용 블록
	static const int BlockSize = 3;		// 블록의 사이즈
	static const int HumanHeight = 3;		// 사람의 키
	static const int StairGap = HumanHeight + 1;     // 계단 사이 거리
	static const int Width = BlockSize * 7;    // 인게임 가로 길이
	static const int ScoreBoardWidth = 15;     //스코어보드 가로 길이
	static const int FullWidth = Width + 3 + ScoreBoardWidth;    // 총 가로 길이

	static const int Height = HumanHeight * 6 + 1;              // 인게임 세로 길이
	static const int FullHeight = Height + 2;  // 총 세로 길이

	static const int LevelCount = 10;	// 레벨이 올라가는데 필요한 계단수
	inline static const float MinLevelTime = 0.5f;  // 최소한의 정지허용시간
	inline static const float LevelMinusTime = 0.5f;// 레벨마다 줄어드는 정지허용시간
	inline static const float FirstLevelTime = 5.f;   // 최초 레벨 정지허용시간

	void Init();
	void Run();
	void Update();
	void GameOver();
};

