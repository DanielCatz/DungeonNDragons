#pragma once
#include "Map.h"

class MapBuilder{
public:	
	Map* getMap(){return gameMap;}
	void createMapProduct(){ gameMap = new Map;}
	virtual void buildBaseMap()=0;
	virtual void buildWalls()=0;
	virtual void buildTreasure()=0;
	virtual void buildEntrance()=0;
	virtual void buildExit()=0;
	virtual void buildOpponents()=0;
	virtual void buildMerchants()=0;

protected:
	Map* gameMap;
};