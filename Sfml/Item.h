/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once

#include <iostream>
#include <string>
using namespace std;

class Item
{
public:
	string getItemName();
	string getItemImage();
	string getEquippedItemImage();
	char getItemClass();
	int* getItemStats();
	void setItemName(string);
	void setItemImage(string);
	void setItemClass(char);
	void setItemStats(string);
	string getStatsString(bool);
	virtual string toString();
	void setStatConstraints(char);
	string generateStats(int);
private:
	string iName;		// name of the item
	string iImg;		// filepath of the img file
	char iClass;
	int iStats[11];		// array of enchantment bonuses
	bool statConstraints[11];
	// array to keep track of which stats are allowerd to be modified by this item
};