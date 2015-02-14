/*
COMP 345/2 section N - Assignment 3 - Part 3: Chest Builder
Author: Celina Taing (6784151)
Date: November 22, 2013
*/

#pragma once

#include "ChestBuilder.h"

class LevelChestBuilder : public ChestBuilder
{
public:
	virtual void buildChest(int lvl)
	{
		chest->loadChest(lvl);
	}
};