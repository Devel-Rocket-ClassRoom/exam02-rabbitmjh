#pragma once
#include <string>
#include <vector>

class GameMap
{
private:
	std::vector<std::string> GameMap;
	std::vector<int> StairXPositions;      // 계단 위치 저장용 벡터

public:
	const std::vector<std::string>& GetGameMap() const { return GameMap; }
	void PushBackGameMap(std::string Input) { GameMap.push_back(Input); }
	void EraseGameMap(int EraseRange);
	void SetGameMap(int y, int x, char c) { GameMap[y][x] = c; }

	const std::vector<int>& GetStairXPositions() const { return StairXPositions; }
	void PushBackStairXPositions(int Input) { StairXPositions.push_back(Input); }

};

