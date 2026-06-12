#pragma once

class GameMap;
class GameState;

class Player
{
public:
	enum class Dir
	{
		Idle, Left, Right
	};

private:
	GameMap* gameMap;
	GameState* gameState;

	int PlayerY = 0;
	int PlayerX;
	Dir PlayerDir = Dir::Idle;
public:
	void PlayerInit(GameMap* gM, GameState* gS);
	void MoveHuman(Dir dir);	// 입력을 받고 다음 위치 저장
	bool bGameOverCheck();	// 게임 오버 체크

	Dir GetPlayerDir() const { return PlayerDir; }
	void SetPlayerDir(Dir InputDir) { PlayerDir = InputDir; }
	int GetPlayerY() const { return PlayerY; }
	void SetPlayerY(int InputY) { PlayerY = InputY; }
	int GetPlayerX() const { return PlayerX; }
	void SetPlayerX(int InputX) { PlayerX = InputX; }
};