/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include "Equipment.h"
using namespace std;


// default constructor
Equipment::Equipment(string n, char t, char w, string i, string s)
{
	setItemName(n);
	setItemImage(i);
	setItemClass('E');
	setItemStats(s);
	setStatConstraints(t);
	type = t;
	weight = w;
}

Equipment::Equipment(string n, char t, char w, string i)
{
	setItemName(n);
	setItemImage(i);
	setItemClass('E');
	setStatConstraints(t);
	type = t;
	weight = w;
}

char Equipment::getEquipType()
{
	return type;
}

string Equipment::getEquipTypeString()
{
	switch(type)
	{
		case 'A':
			return "Helmet";
		case 'B':
			return "Armor";
		case 'C':
			return "Belt";
		case 'D':
			return "Boots";
		case 'E':
			return "Ring";
		case 'F':
			return "Shield";
		case 'G':
			return "Bracers";
		default:
			return "Unknown";
	}
}

string Equipment::getEquipWeight()
{
	switch(weight)
	{
	case 'L':
		return "Light";
	case 'M':
		return "Medium";
	case 'H':
		return "Heavy";
	case 'C':
		return "Cloak";
	default:
		return "X";
	}
}

string Equipment::toString()
{
	return "Name: " + Item::getItemName() + "\n" +
		   "Type: " + getEquipTypeString() + (getEquipWeight() != "X" ? " - " + getEquipWeight() : "") + "\n" +
		   "Stats: \n" + Item::getStatsString(true) + "\n";
}