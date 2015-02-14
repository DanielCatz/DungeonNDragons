#pragma once
#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <vector>
using namespace std;

//map.cpp
void Map::setBase(std::vector <std::vector <std::string > > field){base = field;}

void Map::setWalls(std::vector <std::vector <std::string > > wall){	walls=wall;}

 void Map::setTreasure(std::vector <std::vector <std::string > > chest){chests=chest;}

 void Map::setEntrance(std::vector <std::vector <std::string > > start){entry= start;}

 void Map::setExit(std::vector <std::vector <std::string > > exit){goal = exit;}

 void Map::setOpponents(std::vector <std::vector <std::string > > enemy){enemies = enemy;}

 void Map::setMerchants(std::vector <std::vector <std::string > > merchant){merchants = merchant;}




 std::vector <std::vector <std::string > > Map::getChest(){}
 std::vector <std::vector <std::string > > Map::getWalls(){}
 std::vector <std::vector <std::string > > Map::getMap(){ return enemies;}
 std::vector <std::vector <std::string > > Map::getEnemies(){}