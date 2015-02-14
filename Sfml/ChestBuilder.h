/*
COMP 345/2 section N - Assignment 3 - Part 3: Chest Builder
Author: Celina Taing (6784151)
Date: November 22, 2013
*/

#pragma once

#include <iostream>
#include "ItemPouch.h"

class ChestBuilder
{
public:
    ItemPouch* getChest()
    {
        return chest;
    }

    void createNewChest(int x)
    {
        chest = new ItemPouch(x);
    }

	virtual void buildChest(int) = 0;
protected:
    ItemPouch* chest;
};