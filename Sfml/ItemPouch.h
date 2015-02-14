/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once

#include <string>
#include "Equipment.h"
#include "Weapon.h"
using namespace std;

class ItemPouch
{
public:
	ItemPouch();
	ItemPouch(char, string);
	ItemPouch(int);
	bool isEmpty();
	bool isFull();
	int add(int, string, char, char, char, char, string, string);
	void add(int, Item*);
	string toString();
	Item** getItems();
	int getPouchSize();
	void clearSlot(int);
	void saveToFile(string);
	void loadFromFile(string);
	void loadChest(int);
private:
	const static int INV_SIZE = 24;
	const static int EQ_SIZE = 8;
	const static int MERCH_SIZE = 20;
	const static int CHEST_SIZE = 5;
	const static int MAX_SIZE = (INV_SIZE + EQ_SIZE);
	char pouchType;	// (A)ll items; (I)nventory; (E)quips; (C)hest; (M)erchant
	Item* items[MAX_SIZE];	// array of pointers to Items
};