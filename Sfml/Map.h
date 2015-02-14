#pragma once
#include "stdafx.h"
#include <vector>
class Map{
public:
 void setBase(std::vector <std::vector <std::string > > field);
 void setLevel(int maplevel){level= maplevel;}
 void setWalls(std::vector <std::vector <std::string > > walls);
 void setTreasure(std::vector <std::vector <std::string > > chests);
 void setEntrance(std::vector <std::vector <std::string > > entry);
 void setExit(std::vector <std::vector <std::string > > exit);
 void setOpponents(std::vector <std::vector <std::string > > enemies);
 void setMerchants(std::vector <std::vector <std::string > > merchants);
 int getLevel(){return level;}
 std::vector <std::vector <std::string > > getChest();
 std::vector <std::vector <std::string > > getWalls();
 std::vector <std::vector <std::string > > getMap();
 std::vector <std::vector <std::string > > getEnemies();
 private:
	int level;
	std::vector <std::vector <std::string > > base;
	std::vector <std::vector <std::string > > chests;
	std::vector <std::vector <std::string > > walls;
	std::vector <std::vector <std::string > > goal;
	std::vector <std::vector <std::string > > entry;
	std::vector <std::vector <std::string > > enemies;
	std::vector <std::vector <std::string > > merchants;
	std::vector <std::vector <std::string > > gameMap;
};