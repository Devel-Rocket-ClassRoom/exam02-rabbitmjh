#include "GameMap.h"

void GameMap::EraseGameMap(int EraseRange)
{
	GameMap.erase(GameMap.begin(), GameMap.begin() + EraseRange);
}