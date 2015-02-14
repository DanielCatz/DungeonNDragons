/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once
#include "ObservableIP.h"
#include "ItemPouch.h"
#include "ChestMaker.h"
#include "LevelChestBuilder.h"
#include <string>

class IPModel : public ObservableIP
{
public:
	IPModel(string);
	IPModel(string, int);
	void attach(Observer* o);
	void detach(Observer* o);
	void notify();
	ItemPouch* getIP(char);
	void newChest(char, int);
private:
	ItemPouch* inv;
	ItemPouch* eqp;
	ItemPouch* chest;
	ChestMaker cMaker;
	ChestBuilder* lcBuilder;
};