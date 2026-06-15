#pragma once
#include <string>
#include <vector>

class GameMap
{
private:
	std::vector<std::pair<std::string,int>> GameMap;
	std::vector<int> StairXPositions;      // 계단 위치 저장용 벡터

public:
	const std::vector<std::pair<std::string, int>>& GetGameMap() const { return GameMap; }
	void PushBackGameMap(std::string Input, int n) { GameMap.push_back({ Input, n }); }
	void EraseGameMap(int EraseRange);
	void SetGameMap(int y, int x, char c) { GameMap[y].first[x] = c; }

	const std::vector<int>& GetStairXPositions() const { return StairXPositions; }
	void PushBackStairXPositions(int Input) { StairXPositions.push_back(Input); }

};

