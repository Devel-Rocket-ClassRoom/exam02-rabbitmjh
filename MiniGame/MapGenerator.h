#pragma once
#include <random>
#include "GameMap.h"

class GameState;
class Renderer;
class GameMap;

class MapGenerator
{
private:
	const int FirstStairX = 11;          // 최초 계단의 X값
	int StairCount = 1;

	GameState* gameState;
	Renderer* renderer;
	GameMap* gameMap;

	std::mt19937 RandomEngine;
	std::random_device rd;

public:
	void MapGeneratorInit(GameState* gS, Renderer* ren, GameMap* gM);
	void CreateFirstMap();
	void UpdateMap();
	void PlaceNextStairs(); // 다음 생성할 계단 알고리즘

	int GetFirstStairX() const { return FirstStairX; }
	void SetRandomeEngine() { RandomEngine = std::mt19937(rd()); }
};