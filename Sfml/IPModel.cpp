/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include "IPModel.h"

IPModel::IPModel(string name)
{
	inv = new ItemPouch('I', name);
	eqp = new ItemPouch('E', name);
}

IPModel::IPModel(string name, int lvl)
{
	inv = new ItemPouch('I', name);
	
	cMaker = ChestMaker();
	lcBuilder = new LevelChestBuilder;
	cMaker.setChestBuilder(lcBuilder);
	cMaker.constructChest(lvl);
	chest = cMaker.getChest();
}

// returns a pointer to the requested item pouch (E - equipped items; I - inventory)
ItemPouch* IPModel::getIP(char type)
{
	switch(type)
	{
	case 'I':
		return inv;
	case 'E':
		return eqp;
	case 'C':
		return chest;
	}
}

void IPModel::attach(Observer* o)
{
	obs = o;
}

void IPModel::detach(Observer* o)
{
	obs = NULL;
}
	
void IPModel::notify()
{
	obs->update();
}