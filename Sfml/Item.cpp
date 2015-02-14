/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

static const string sNames[11] = {  "HP",
									"MP",
									"STRENGTH",
									"CONSTITUTION",
									"WISDOM",
									"INTELLIGENCE",
									"DEXTERITY",
									"CHARISMA",
									"ARMOR",
									"ATTACK",
									"DAMAGE"
								 };

string Item::getItemName()
{
	return iName;
}

string Item::getItemImage()
{
	return iImg;
}

string Item::getEquippedItemImage()
{
	string fp = iImg;
	return fp.insert(iImg.find(".png"), "-e");
}

char Item::getItemClass()
{
	return iClass;
}

//returns a pointer to the array iStats
int* Item::getItemStats()
{
	return iStats;
}

void Item::setItemName(string in)
{
	iName = in;
}

void Item::setItemImage(string ii)
{
	iImg = ii;
}

void Item::setItemClass(char ic)
{
	iClass = ic;
}

// extract enchantment bonuses from the given string, and insert them in iStats
// NOTE: the given string has to be in the format of:
// ## <enchantment type name in all uppercase>;[## <name>;...]
// example: 5 STRENGTH;2 CONSTITUTION;...
void Item::setItemStats(string is)
{
	// reset the array
	for (int j = 0; j <= 11; j++)
		iStats[j] = 0;

	string s = is;
	int start;
	int stop;
	
	do
	{
		stop = s.find(";");
		if (stop != s.npos)
		{
			string stat = s.substr(0, stop);
			int i;

			// determine the index of iStat at which the enchantment bonus is to be inserted into:
			// O-HP ; 1-MP ; 2-STRENGTH ; 3-CONSTITUTION ; 4-WISDOM ; 5-INTELLIGENCE ; 
			// 6-DEXTERITY ; 7-CHARISMA ; 8-ARMOR		 ; 9-ATTACK ; 10-DAMAGE
			if (stat.find(sNames[0]) != s.npos)
				i = 0;
			else if (stat.find(sNames[1]) != s.npos)
				i = 1;
			else if (stat.find(sNames[2]) != s.npos)
				i = 2;
			else if (stat.find(sNames[3]) != s.npos)
				i = 3;
			else if (stat.find(sNames[4]) != s.npos)
				i = 4;
			else if (stat.find(sNames[5]) != s.npos)
				i = 5;
			else if (stat.find(sNames[6]) != s.npos)
				i = 6;
			else if (stat.find(sNames[7]) != s.npos)
				i = 7;
			else if (stat.find(sNames[8]) != s.npos)
				i = 8;
			else if (stat.find(sNames[9]) != s.npos)
				i = 9;
			else if (stat.find(sNames[10]) != s.npos)
				i = 10;

			iStats[i] = stoi(stat.substr(0, stat.find(" ")));
			start = stop + 1;
			s = s.substr(start, s.npos);
		}
	} while (stop != s.npos);
}

// returns a string of the contents of iStats
// *NOTE: if formatted = true: delimiter = '\n'
//		  else: delimiter = ';'
string Item::getStatsString(bool formatted)
{
	string delim = (formatted ? "\n" : ";"); 
	string stats = "";
	for (int i = 0; i < 11; i++)
	{
		if (iStats[i] > 0)
			stats += to_string(iStats[i]) + " " + sNames[i] + delim;
	}

	return stats;
}

string Item::toString()
{
	return "Name: " + Item::getItemName() + "\n" + 
		   "Stats: \n" + Item::getStatsString(true);
}

void Item::setStatConstraints(char t)
{
	for (int i = 0; i < 11; i++)
		statConstraints[i] = false;
	if (iClass == 'W')
	{
		statConstraints[9] = true;
		statConstraints[10] = true;
	}
	else
	{
		switch(t)
		{
		case 'A':
			statConstraints[4] = true;
			statConstraints[5] = true;
			statConstraints[8] = true;
			break;
		case 'B':
			statConstraints[8] = true;
			break;
		case 'C':
			statConstraints[2] = true;
			statConstraints[3] = true;
			break;
		case 'D':
			statConstraints[6] = true;
			statConstraints[8] = true;
			break;
		case 'E':
			statConstraints[2] = true;
			statConstraints[3] = true;
			statConstraints[4] = true;
			statConstraints[7] = true;
			statConstraints[8] = true;
			break;
		case 'F':
			statConstraints[8] = true;
			break;
		case 'G':
			statConstraints[2] = true;
			statConstraints[8] = true;
			break;
		}
	}
}

string Item::generateStats(int lvl)
{
	// derive formula for higher level => better stats
	string s = "";
	lvl = (lvl >= 1 && lvl <= 5 ? lvl : 5);
	for (int i = 0; i < 11; i++)
	{
		if (statConstraints[i])
		{
			int x = (rand() % lvl) + 1;
			if (x > 0)
				s += to_string(x) + " " + sNames[i] + ";";
		}
	}

	setItemStats(s);
	return getStatsString(false);
}