/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once

#include "Item.h"
#include <string>

class Weapon: public Item
{
public:
	Weapon(string, char, char, string, string);
	Weapon(string, char, char, string);
	string getWeaponDesc();
	char getWeaponType();
	char getWeaponCategory();
	string toString();
private:
	char type;		// A=Melee ; B=Ranged ; C=Magic
	char category;	// L=Light ; O=One-handed ; T=Two-handed ; X=Not applicable (when type != A)
};