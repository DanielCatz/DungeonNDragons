/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "ItemPouch.h"
using namespace std;

// default constructor: item pouch type = (A)ll items
ItemPouch::ItemPouch()
{
	pouchType = 'A';
}

// constructor that sets the item pouch for Inventory or Equips
ItemPouch::ItemPouch(char t, string name)
{
	pouchType = t;
	
	// all item slots start off empty (NULL)
	for (int l = 0; l < getPouchSize(); l++)
		items[l] = NULL;

	loadFromFile(name);
}

// constructor that sets the item pouch for Chests
ItemPouch::ItemPouch(int l)
{
	pouchType = 'C';
	
	for (int k = 0; k < getPouchSize(); k++)
		items[k] = NULL;

	loadChest(l);
}

bool ItemPouch::isEmpty()
{
	for (int i = 0; i < getPouchSize(); i++)
	{
		if (items[i] != NULL)	
			return false;	// there's at least 1 slot that's not empty
	}
	return true;
}

bool ItemPouch::isFull()
{
	for (int i = 0; i < getPouchSize(); i++)
	{
		if (items[i] == NULL)
			return false;	// there's at least 1 empty slot
	}
	return true;
}

// inserts into the next available slot, given the item's details
int ItemPouch::add(int slot, string n, char cl, char t, char ca, char w, string i, string s)
{
	//cout << "adding!" << endl;
	if (pouchType == 'I' && isFull())
	{
		cout << "No slots are available!" << endl;
		return -1;
	}
	else
	{
		//if not given, find next empty slot in the inventory
		int ind = 0;
		if (slot == -1)
		{
			for (ind; ind < getPouchSize(); ind++)
			{
				if (items[ind] == NULL)
					break;
			}
		}
		else
			ind = slot;
	
		//create the item obj & put it into the empty slot
		switch (cl)
		{
		case 'E':
			items[ind] = new Equipment(n, t, w, i, s);
			break;
		case 'W':
			items[ind] = new Weapon(n, t, ca, i, s);
			break;
		default:
			break;
		}

		return ind;
	}
}

// inserts the given item at the given slot number
void ItemPouch::add(int index, Item* item)
{
	if (pouchType == 'I' && isFull())
		cout << "Slot " << index << " is not available!" << endl;
	else
	{
		// if type = Inventory: find the next empty slot
		if (pouchType == 'I' && index == -1)
		{
			for (int i = 0 ; i < getPouchSize() ; i++)
			{
				if (items[i] == NULL)
				{
					index = i;
					break;
				}
			}
		}

		if (index >= 0 && index <= getPouchSize())
			items[index] = item;
	}
}

string ItemPouch::toString()
{
	if (isEmpty())
		return "This item pouch is empty..\n";
	else
	{
		string invStr = "";
		for (int i = 0; i < getPouchSize(); i++)
		{
			if (items[i] != NULL)
			{
				invStr += "[" + to_string(i+1) + "] " + items[i]->getItemName();
				if (i < getPouchSize() - 1)
					invStr += "\n";
			}
		}
		return invStr;
	}
}

//returns a pointer to the array items
Item** ItemPouch::getItems()
{
	return items;
}

int ItemPouch::getPouchSize()
{
	switch(pouchType)
	{
	case 'C':
		return CHEST_SIZE;
	case 'E':
		return EQ_SIZE;
	case 'I':
		return INV_SIZE;
	case 'M':
		return MERCH_SIZE;
	default:
		return MAX_SIZE;
	}
}

void ItemPouch::clearSlot(int n)
{
	items[n] = NULL;
}

// saves the contents of the item pouch in a text file
void ItemPouch::saveToFile(string charName)
{
	ofstream outFile;
	
	// set the file name to save to
	string fileName = charName + "/";

	switch(pouchType)
	{
	case 'I':
		fileName += "inventory.txt";
		break;
	case 'E':
		fileName += "equipped.txt";
		break;
	}
	
	outFile.open(fileName, ios::trunc);
	
	// write to the file, for each item in the item pouch
	if (outFile.is_open())
	{
		for (int index = 0; index < getPouchSize(); index++)
		{
			if (items[index] != NULL)
			{
				// items are written to the file in the format:
				// slot#, name, class(E/W), item type (A/B/C/D/E/F), item category (L/O/T/X), weight(L/M/H), img filepath, stats
				switch(items[index]->getItemClass())
				{
				case 'E':
				{
					Equipment* myEqp = dynamic_cast<Equipment*>(items[index]);
					outFile <<	index << "," <<
								myEqp->getItemName() << "," << 
								myEqp->getItemClass() << "," << 
								myEqp->getEquipType() << "," <<
								"X" << "," <<		// weapon category => not needed for equipment
								myEqp->getEquipWeight().at(0) << "," << 
								myEqp->getItemImage() << "," << 
								myEqp->getStatsString(false) << endl;
					//delete myEqp;
					break;
				}
				case 'W':
				{
					Weapon* myWpn = dynamic_cast<Weapon*>(items[index]);
					outFile <<	index << "," <<
								myWpn->getItemName() << "," << 
								myWpn->getItemClass() << "," << 
								myWpn->getWeaponType() << "," <<
								myWpn->getWeaponCategory() << "," <<
								"X" << "," <<		// armor weight => not needed for weapons
								myWpn->getItemImage() << "," << 
								myWpn->getStatsString(false) << endl;
					//delete myWpn;
					break;
				}
				}
			}
		}
		outFile.close();
	}
}

// loads the items from a text file, and inserts them into the item pouch
void ItemPouch::loadFromFile(string charName)
{
	ifstream inFile;
	
	// set the file name to load from
	string fileName = charName + "/";
	switch(pouchType)
	{
	case 'I':
		fileName += "inventory.txt";
		break;
	case 'E':
		fileName += "equipped.txt";
		break;
	}
	
	inFile.open(fileName);

	// if inventory.txt can't be found for this character, load from the default file
	if (!(inFile.is_open()) && pouchType == 'I')
	{
		//cout << "cannot find inventory.txt" << endl;
		inFile.close();
		inFile.open("defaultInvItemsList.txt");
	}

	// for each line in the text file: 
	// - get the values needed to create an Equipment/Weapon object
	// - insert the item into the item pouch
	if (inFile.is_open())
	{
		string itemLine;
		string itemDetails[7];
		//cout << "file is open!" << endl;
		while (getline(inFile, itemLine))
		{
			string iString = itemLine;
			//cout << "got line:" << itemLine << endl;
			int start = 0;
			int stop = iString.find(",");

			// get the slot number to store the item in
			int slot = stoi(iString.substr(0, stop));
			start = stop + 1;
			iString = iString.substr(start, iString.npos);
			
			// get the details of the item (delimited by ',')
			for (int i = 0; i < 7; i++)
			{
				stop = iString.find(",");
				itemDetails[i] = iString.substr(0, stop);
				start = stop + 1;
				iString = iString.substr(start, iString.npos);
			}

			add(slot,
				itemDetails[0],			// name
				itemDetails[1].at(0),	// class(E/W)
				itemDetails[2].at(0),	// item type (A/B/C/D/E/F)
				itemDetails[3].at(0),	// item category (L/O/T/X)
				itemDetails[4].at(0),	// weight(L/M/H/X)
				itemDetails[5],			// img filepath
				itemDetails[6]			// stats
			   );
		}
		inFile.close();
	}
}

void ItemPouch::loadChest(int l)
{
	ifstream inFile;
	inFile.open("chestItemsList.txt");

	if (inFile.is_open())
	{
		for (int k = 0; k < getPouchSize(); k++)
			items[k] = NULL;

		// random # of items in chest = [1, 5]
		int numItems = (rand() % getPouchSize()) + 1;
		
		for (int z = 0; z < numItems; z++)
		{
			// generate random number (x) & read item at line x
			int x = (rand() % 36) + 1;	// 36 lines in chestItemsList.txt => 1 item per item
		
			int i = 1;
			string itemLine;
			string itemDetails[7];
			do
			{	
				getline(inFile, itemLine);
				if (i == x)
				{
					string iString = itemLine;
					int start = 0;
					int stop = 0;

					// get the details of the item (delimited by ',')
					for (int j = 0; j < 6; j++)
					{
						stop = iString.find(",");
						itemDetails[j] = iString.substr(0, stop);
						start = stop + 1;
						iString = iString.substr(start, iString.npos);
					}

					// generate random stats (depending on whether the chest is random or lvl-dependent
					if (itemDetails[1].at(0) != 'C')
					{
						Item* tempI;
						if (itemDetails[1].at(0) == 'E')
							tempI = new Equipment(itemDetails[0], itemDetails[2].at(0), itemDetails[4].at(0), itemDetails[5]);
						else
							tempI = new Weapon(itemDetails[0], itemDetails[2].at(0), itemDetails[3].at(0), itemDetails[5]);

						itemDetails[6] = tempI->generateStats(l);
					}

					add(-1,
						itemDetails[0],			// name
						itemDetails[1].at(0),	// class(E/W)
						itemDetails[2].at(0),	// item type (A/B/C/D/E/F)
						itemDetails[3].at(0),	// item category (L/O/T/X)
						itemDetails[4].at(0),	// weight(L/M/H/X)
						itemDetails[5],			// img filepath
						itemDetails[6]			// stats
					   );
					break;
				}
				i++;
			} while (i <= x);

			//reset the file reader cursor at the top
			inFile.clear();
			inFile.seekg(0, ios::beg);
		}
		inFile.close();
	}
}