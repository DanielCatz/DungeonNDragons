#pragma once
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapBuilder.h"
#include "ArenaMapBuilder.h"
#include <vector>


class Contractor //Director
{
  public:
    void setMapBuilder(MapBuilder* mb) 
      {                                    
         mapBuilder = mb;             
      }

    Map* getmap()                     
      {
         return mapBuilder->getMap();
      }
    void constructMap(){                                     
         mapBuilder->createMapProduct(); 
		 mapBuilder->buildBaseMap();
         mapBuilder->buildWalls();
         mapBuilder->buildTreasure();
         mapBuilder->buildEntrance();
		 mapBuilder->buildExit();
		 mapBuilder->buildOpponents();
		
	}
  private:
    MapBuilder* mapBuilder;
};