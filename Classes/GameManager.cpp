#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
        instance = new GameManager();
	return instance;
}

void GameManager::clear()
{
	enemyVector.clear();
	bulletVector.clear();
	//towerVector.clear();
	groupVector.clear();
}

void GameManager::setTowerInfo()
{
	InfoHandle handle;
	towerInfo[0] = handle.getTowerInfo("arrowtower");
	towerInfo[1] = handle.getTowerInfo("slowtower");
	towerInfo[2] = handle.getTowerInfo("poisontower");
	towerInfo[3] = handle.getTowerInfo("turrettower");
	towerInfo[4] = handle.getTowerInfo("multitower");
	towerInfo[5] = handle.getTowerInfo("frozentower");
	towerInfo[6] = handle.getTowerInfo("burntower");
	towerInfo[7] = handle.getTowerInfo("cannontower");
}
