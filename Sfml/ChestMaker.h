/*
COMP 345/2 section N - Assignment 3 - Part 3: Chest Builder
Author: Celina Taing (6784151)
Date: November 22, 2013
*/

#pragma once

#include "ChestBuilder.h"

class ChestMaker // Director of the Builder pattern
{
public:
	void setChestBuilder(ChestBuilder* pb)
	{
		cBuilder = pb;
	}

	ItemPouch* getChest()
	{
		return cBuilder->getChest();
	}

	void constructChest(int x)
	{
		cBuilder->createNewChest(x);
	}
private:
	ChestBuilder* cBuilder;
};