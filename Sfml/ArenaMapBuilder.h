#pragma once
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapBuilder.h"
#include "ArenaMapBuilder.h"
#include <vector>
using namespace std;

class ArenaMapBuilder: public MapBuilder{
public:	

	ArenaMapBuilder(int charLevel){level =charLevel;}

virtual void buildBaseMap(){
	map = std::vector <std::vector <std::string > > (11, std::vector<std::string>(11,"r"));
	gameMap->setLevel(level);
	gameMap->setBase(map);
}

virtual void buildgameMap(){cout<<"these are words";}

virtual void buildWalls(){
	cout<<endl<<"build Walls";
	for(int i = 0 ; i <11; i++){
	map[1][i]="w";
	map[9][i]="w";
	map[i][1]="w";
	map[i][9]="w";
	
}
	for(int i = 0 ; i <11; i++){
	map[0][i]="q";
	map[10][i]="q";
	map[i][0]="q";
	map[i][10]="q";
	
}
		
gameMap->setWalls(map);
//displayMap();
}

virtual void buildTreasure(){//set treasure
	cout<<endl<<"build chest";
	map[5][5]= "t";
gameMap->setTreasure(map);
///displayMap();
 }

virtual void buildEntrance(){
	cout<<endl<<"build Entrance";
	map[5][1]= "e";
gameMap->setEntrance(map);
//displayMap();
}

virtual void buildExit(){
	cout<<endl<<"build exit";
	map[5][9]= "g";
	gameMap->setExit(map);
//displayMap();
}

virtual void buildOpponents(){
 cout<<endl<<"build enemy";
	map[5][8]= "o";
 gameMap->setOpponents(map);
//displayMap();
}

virtual void buildMerchants(){
	//map[5][8]= "m";
gameMap->setMerchants(map);
//displayMap();
}


void displayMap(){
	cout<<endl;
	for(int i = 0 ; i < map[0].size(); i++){
			 for(int j = 0 ; j <  map.size(); j++){
			cout<<map[j][i];
			}	 
		cout<<endl;
		}
system("pause");
}


private:
	int level;
	std::vector <std::vector <std::string > > map;
	//gamemap exist in base
};