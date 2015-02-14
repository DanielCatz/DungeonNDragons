/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once
#include "IPModel.h"
#include "IPView.h"
#include "Character.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class IPController
{
public:
	IPController();
	IPController(sf::RenderWindow&, Character& npc);
	IPController(sf::RenderWindow&, string, int, char);
	IPController(sf::RenderWindow&, string, int, int, int);
	int getEquipSlotNum(float, float);
	int getInvSlotNum(float, float);
	int getChestSlotNum(float, float);
	void start(sf::RenderWindow&);
	void startChest(sf::RenderWindow&);
	void eventsHandler(sf::RenderWindow&);
	void eventsHandlerChest(sf::RenderWindow&);
	int getXCoord();
	void setXCoord(int);
	int getYCoord();
	void setYCoord(int);
	vector<int> updateStats();
	string toString();
private:
	IPModel* model;
	IPView* view;
	sf::RenderWindow* window;
	string characterName;
	int xCoord;
	int yCoord;
};