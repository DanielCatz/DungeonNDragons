/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once

#include "Item.h"
#include <string>

class Equipment: public Item
{
public:
	Equipment(string, char, char, string, string);
	Equipment(string, char, char, string);
	char getEquipType();
	string getEquipTypeString();
	string getEquipWeight();
	string toString();
private:
	char type;		// A=Helmet ; B=Armor ; C=Belt ; D=Boots ; E=Ring ; F=Shield ; G=Bracers
	char weight;	// L=Light ; M=Medium ; H=Heavy ; C=Cloak ; X=Not applicable (when type != B)
};