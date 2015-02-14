/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include "IPController.h"
#include <string>

// inventory panel: [0] = size; [1] = position;
static int panel[2][2] = {{721, 361}, {0, 0}};

// x & y sizes of the different areas in the inventory panel
const static int areaCoords[4][2] = {   {5, 5},		// eqpArea
										{260, 5},	// invArea
										{260, 211},	// detArea
										{566, 5}	// statsArea
								   };

// x & y sizes of the different areas in the panel
const static int areaSize[5][2] = { {250, 351},	// eqpArea
									{301, 201},	// invArea
									{301, 145},	// detArea
									{150, 351},	// statsArea
									{129, 179}	// chestArea
								   };

// x & y coordinates of the item slots in the background image of the equipped area
const static int eCoords[8][2] = {	{101, 19},	// helmet
									{20, 48},	// ring
									{183, 48},	// bracers
									{101, 108},	// armor
									{35, 145},	// weapon
									{167, 145},	// shield
									{101, 172},	// belt
									{101, 281}	// boots
								 };

// chest panel: [0] = size; [1] = position;
static int cPanel[2][2] = {{445, 361}, {0, 0}};

// x & y coordinates of the different areas in the chest panel
const static int cAreaCoords[3][2] = {  {5, 5},		// invArea
										{5, 211},	// detArea
										{311, 82}	// chestArea
									 };

// x & y coordinates of the item slots in the background image of the chest area
const static int cCoords[5][2] = {  {40, 15},	// top
									{15, 65},	// mid-left
									{65, 65},	// mid-right
									{15, 115},	// bottom-left
									{65, 115}	// bottom-right
								 };

IPController::IPController()
{
	xCoord = 0;
	yCoord = 0;
}

IPController::IPController(sf::RenderWindow& invWin, Character& NPC){
	window = &invWin;
	characterName = NPC.getName();
	model = new IPModel(characterName);
	view = new IPView(model, invWin, NPC);
	panel[1][0] = (window->getPosition().x + window->getSize().x - panel[0][0]) / 2;
	panel[1][1] = (window->getPosition().y + window->getSize().y - panel[0][1]) / 2;

	start(invWin);


}

IPController::IPController(sf::RenderWindow& invWin, string charName, int charLvl, char charGend)
{
	window = &invWin;
	characterName = charName;

	model = new IPModel(charName);
	view = new IPView(model, invWin, charName, charLvl, charGend);

	panel[1][0] = (window->getPosition().x + window->getSize().x - panel[0][0]) / 2;
	panel[1][1] = (window->getPosition().y + window->getSize().y - panel[0][1]) / 2;

	start(invWin);
}

IPController::IPController(sf::RenderWindow& mapWind, string name, int lvl, int xPoint, int yPoint)
{
	window = &mapWind;
	setXCoord(xPoint);
	setYCoord(yPoint);
	characterName = name;

	model = new IPModel(name, lvl);
	view = new IPView(model, mapWind, lvl);

	cPanel[1][0] = (window->getPosition().x + window->getSize().x - cPanel[0][0]) / 2;
	cPanel[1][1] = (window->getPosition().y + window->getSize().y - cPanel[0][1]) / 2;

	startChest(mapWind);
}

int IPController::getXCoord()
{
	return xCoord;
}

void IPController::setXCoord(int xPoint)
{
	xCoord = xPoint;
}

int IPController::getYCoord()
{
	return yCoord;
}

void IPController::setYCoord(int yPoint)
{
	yCoord = yPoint;
}

// returns the equipped slot number that the user clicked on
int IPController::getEquipSlotNum(float x, float y)
{
	//cout << "x=" << x << "; y=" << y << endl;
	int slotSize = 49;
	
	for (int j = 0; j < 8; j++)
	{
		int lowerX = panel[1][0] + areaCoords[0][0] + eCoords[j][0];
		int upperX = lowerX + slotSize;

		int lowerY = panel[1][1] + areaCoords[0][1] + eCoords[j][1];
		int upperY = lowerY + slotSize;
		if ((x >= lowerX && x <= upperX) && (y >= lowerY && y <= upperY))
			return j;
	}
	return -1;
}

// returns the inventory slot number that the user clicked on
int IPController::getInvSlotNum(float x, float y)
{
	int row = floor(y/50);
	int col = floor(x/50);
	//cout << "x=" << x << "; y=" << y << "; row=" << row << "; col=" << col << "; slotNum=" << ((col % 6) + (row * 6)) << endl;
	return ((col % 6) + (row * 6));
}

// returns the chest slot number that the user clicked on
int IPController::getChestSlotNum(float x, float y)
{
	//cout << "x=" << x << "; y=" << y << endl;
	for (int g = 0; g < sizeof(cCoords)/sizeof(int); g++)
	{
		if (x >= cCoords[g][0] && x <= (cCoords[g][0] + 49) && y >= cCoords[g][1] && y <= (cCoords[g][1] + 49))
			return g;
	}

	return -1;
}

void IPController::start(sf::RenderWindow& invWin)
{
	view->draw(invWin);
	eventsHandler(invWin);
}

void IPController::startChest(sf::RenderWindow& mapWind)
{
	view->drawChest(mapWind);
	eventsHandlerChest(mapWind);
}

void IPController::eventsHandler(sf::RenderWindow& wind)
{
	window = &wind;
	sf::Event event;
	bool closeWindow = false;

	while (window->isOpen() && !(closeWindow))
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					// save item pouch contents
					model->getIP('E')->saveToFile(characterName);
					model->getIP('I')->saveToFile(characterName);

					//give control back to MEController.cpp
					closeWindow = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.x >= (panel[1][0] + areaCoords[0][0]) && event.mouseButton.x <= (panel[1][0] + areaCoords[0][0] + areaSize[0][0]) && 
					event.mouseButton.y >= (panel[1][1] + areaCoords[0][1]) && event.mouseButton.y <= (panel[1][1] + areaCoords[0][1] + areaSize[0][1]))
				{
					//cout << "Clicked in the Equipment area." << endl;
					
					int i = getEquipSlotNum(event.mouseButton.x, event.mouseButton.y);
					
					if (i != -1)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							// calculate where the mouse button was released + display item info
							if (model->getIP('E')->getItems()[i] != NULL)
								view->setItemDetails(model->getIP('E')->getItems()[i]->toString());
							else
								view->setItemDetails("");
							view->update(wind);
						}
						else if (event.mouseButton.button == sf::Mouse::Right)
						{
							// unequip the item => move item to inventory
							if (model->getIP('E')->getItems()[i] != NULL)
							{
								cout << "Un-equipped " << model->getIP('E')->getItems()[i]->getItemName() << "." << endl;
								model->getIP('I')->add(-1, model->getIP('E')->getItems()[i]);
								model->getIP('E')->clearSlot(i);
								view->setItemDetails("");
								view->update(wind);
							}
						}
					}
					// otherwise, user clicked in the equip area, but not in a slot => do nothing
				}
				else if (event.mouseButton.x >= (panel[1][0] + areaCoords[1][0]) && event.mouseButton.x <= (panel[1][0] + areaCoords[1][0] + areaSize[1][0]) && 
						 event.mouseButton.y >= (panel[1][1] + areaCoords[1][1]) && event.mouseButton.y <= (panel[1][1] + areaCoords[1][1] + areaSize[1][1]))
				{
					//cout << "Clicked in the Inventory area." << endl;
					
					int i = getInvSlotNum(event.mouseButton.x - (panel[1][0] + areaCoords[1][0]), event.mouseButton.y - (panel[1][1] + areaCoords[1][1]));

					if (event.mouseButton.button == sf::Mouse::Left)
					{
						// calculate where the mouse button was released + display item info
						if (model->getIP('I')->getItems()[i] != NULL)
							view->setItemDetails(model->getIP('I')->getItems()[i]->toString());
						else
							view->setItemDetails("");
						view->update(wind);
					}
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (model->getIP('I')->getItems()[i] != NULL)
						{
							// equip the item => move item from inventory to appropriate equip slots
							int eSlot;

							// find corresponding equips slot
							if (model->getIP('I')->getItems()[i]->getItemClass() == 'W')
								eSlot = 4;
							else
							{
								Equipment *e = dynamic_cast<Equipment*>(model->getIP('I')->getItems()[i]);
								switch(e->getEquipType())
								{
									case 'A':	// helmet
										eSlot = 0;  	
										break;
									case 'B':	// armor
										eSlot = 3;
										break;
									case 'C':	// belt
										eSlot = 6;
										break;
									case 'D':	// boots 
										eSlot = 7;
										break;
									case 'E':	// ring
										eSlot = 1;
										break;
									case 'F':	// shield
										eSlot = 5;
										break;
									case 'G':	// bracers
										eSlot = 2;
										break;
								}	// end switch
								//delete e;
							}	// end else to determine eSlot

							
							// swap between equips + inventory
							Item* toEquip = model->getIP('I')->getItems()[i];
							model->getIP('I')->add(i, model->getIP('E')->getItems()[eSlot]);
							model->getIP('E')->add(eSlot, toEquip);

							cout << "Equipped " << toEquip->getItemName() << "." << endl;

							//delete tempEquipped;
							view->setItemDetails("");
							view->update(wind);
						}	// end else to equip the item
					}
				}
				break;
			}
		}
	}
}

void IPController::eventsHandlerChest(sf::RenderWindow& mapWind)
{
	window = &mapWind;

	sf::Event event;
	bool closeWindow = false;

	while (window->isOpen() && !(closeWindow))
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					// save item pouch contents
					model->getIP('I')->saveToFile(characterName);

					// give control back to MEController.cpp
					closeWindow = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.x >= (cPanel[1][0] + cAreaCoords[0][0]) && event.mouseButton.x <= (cPanel[1][0] + cAreaCoords[0][0] + areaSize[1][0]) && 
						 event.mouseButton.y >= (cPanel[1][1] + cAreaCoords[0][1]) && event.mouseButton.y <= (cPanel[1][1] + cAreaCoords[0][1] + areaSize[1][1]))
				{
					//cout << "Clicked in the Inventory area." << endl;
					
					int i = getInvSlotNum(event.mouseButton.x - (cPanel[1][0] + cAreaCoords[0][0]), event.mouseButton.y - (cPanel[1][1] + cAreaCoords[0][1]));

					if (event.mouseButton.button == sf::Mouse::Left)
					{
						// calculate where the mouse button was released + display item info
						if (model->getIP('I')->getItems()[i] != NULL)
							view->setItemDetails(model->getIP('I')->getItems()[i]->toString());
						else
							view->setItemDetails("");
						view->updateChest(*window);
					}
				}
				else if (event.mouseButton.x >= (cPanel[1][0] + cAreaCoords[2][0]) && event.mouseButton.x <= (cPanel[1][0] + cAreaCoords[2][0] + areaSize[4][0]) && 
						 event.mouseButton.y >= (cPanel[1][1] + cAreaCoords[2][1]) && event.mouseButton.y <= (cPanel[1][1] + cAreaCoords[2][1] + areaSize[4][1]))
				{
					//cout << "Clicked in the Chest area." << endl;

					int k = getChestSlotNum(event.mouseButton.x - (cPanel[1][0] + cAreaCoords[2][0]), event.mouseButton.y - (cPanel[1][1] + cAreaCoords[2][1]));

					if (k != -1)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							// calculate where the mouse button was released + display item info
							if (model->getIP('C')->getItems()[k] != NULL)
								view->setItemDetails(model->getIP('C')->getItems()[k]->toString());
							else
								view->setItemDetails("");

							view->updateChest(*window);
						}
						else if (event.mouseButton.button == sf::Mouse::Right)
						{
							// move item from chest to inventory
							if (model->getIP('C')->getItems()[k] != NULL)
							{
								cout << "Received " << model->getIP('C')->getItems()[k]->getItemName() << "." << endl;
								model->getIP('I')->add(-1, model->getIP('C')->getItems()[k]);
								model->getIP('C')->clearSlot(k);
								view->updateChest(*window);
							}
						}
					}
				}
				break;
			}
		}
	}
}

vector<int> IPController::updateStats()
{
	vector<int> newStats(11);
	for (int x = 0; x < 11; x++)
		newStats[x] = 0;

	if (!model->getIP('E')->isEmpty())
	{
		// for each equip slot..
		Item** e = model->getIP('E')->getItems();
		for (int x = 0; x < 8; x++)
		{
			if (e[x] != NULL)	// ..that is NOT null..
			{
				int* stats = e[x]->getItemStats();
				// ..accumulate the stats to add to the player's base stats
				for (int y = 0; y < 11; y++)
					newStats[y] += stats[y];
			}
		}
	}
	return newStats;
}

string IPController::toString()
{
	string s = "Chest contains:\n";
	for (int i = 0; i < model->getIP('C')->getPouchSize(); i++)
	{
		if (model->getIP('C')->getItems()[i] != NULL)
			s += "[" + to_string(i + 1) + "] " + model->getIP('C')->getItems()[i]->toString() + "\n";
	}
	return s;
}