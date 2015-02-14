/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include "Weapon.h"
using namespace std;

// default constructor
Weapon::Weapon(string n, char t, char c, string i ,string s)
{
	setItemName(n);
	setItemImage(i);
	setItemClass('W');
	setItemStats(s);
	setStatConstraints(t);
	type = t;
	category = c;
}

Weapon::Weapon(string n, char t, char c, string i)
{
	setItemName(n);
	setItemImage(i);
	setItemClass('W');
	setStatConstraints(t);
	type = t;
	category = c;
}

string Weapon::getWeaponDesc()
{
	string w = "Weapon -";

	switch(category)
	{
	case 'L':
		w += " Light";
		break;
	case 'O':
		w += " 1-handed";
		break;
	case 'T':
		w += " 2-handed";
		break;
	default:
		break;
	}

	switch(type)
	{
		case 'A':
			return w + " Melee";
		case 'B':
			return w + " Ranged";
		case 'C':
			return w + " Magic";
		default:
			return w + " Unknown";
	}
}

char Weapon::getWeaponType()
{
	return type;
}

char Weapon::getWeaponCategory()
{
	return category;
}

string Weapon::toString()
{
	return "Name: " + Item::getItemName() + "\n" +
		   "Type: " + getWeaponDesc() + "\n" +
		   "Stats: \n" + Item::getStatsString(true) + "\n";
}
/*
void Weapon::toggleWeapon()
{
	int* itemStats = getItemStats();
	if (!isEquipped())
	{
		equipped = true;

		//apply stat boosts
		while (itemStats != NULL)
		{
			//char* s = strtok(itemStats[i].c_str(), " ");
		}
	}
	else
	{
		equipped = false;

		//remove stat boosts
		while (itemStats != NULL)
		{
			//char* s = strtok(itemStats[i].c_str(), " ");
		}
	}
}*/
