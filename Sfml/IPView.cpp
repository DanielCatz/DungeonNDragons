/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/
#pragma once
#include "stdafx.h"
#include "IPView.h"
#include "Controller.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

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

const static string statNames[11] = {"HP", "MP", "STRENGTH", "CONSTITUTION", "WISDOM", "INTELLIGENCE", "DEXTERITY", "CHARISMA",
									 "ARMOR CLASS", "ATTACK BONUS", "DAMAGE BONUS"};

IPView::IPView()
{
}

IPView::IPView(IPModel* ipmod, sf::RenderWindow& wind, string name, int lvl, char gender)
{
	ipmod->attach(this);
	window = &wind;
	inv = ipmod->getIP('I');
	eqps = ipmod->getIP('E');

	characterName = name;
	characterLevel = lvl;
	characterGender = gender;

	panel[1][0] = (window->getPosition().x + window->getSize().x - panel[0][0]) / 2;
	panel[1][1] = (window->getPosition().y + window->getSize().y - panel[0][1]) / 2;
}

IPView::IPView(IPModel* ipmod, sf::RenderWindow& wind, Character& NPC)
{
	ipmod->attach(this);
	window = &wind;
	inv = ipmod->getIP('I');
	eqps = ipmod->getIP('E');
	Controller ctl;

	characterName = NPC.getName();
	characterLevel = NPC.getLevel();
	characterGender = NPC.getGender()[0];
	charHP = NPC.getHP();
	charMP = NPC.getMP();
	charStr = NPC.getStrength();
	charConst = NPC.getConstitution();
	charWisdom = NPC.getWisdom();
	charIntellint = NPC.getIntelligence();
	charDex = NPC.getDexterity();
	charCharisma = NPC.getCharisma();
	charArmorclass = NPC.getArmorClass();
	charAttackbonus = NPC.getAttackBonus();
	charDamagebonus = NPC.getDamageBonus();
	charHP = NPC.getHP();


	panel[1][0] = (window->getPosition().x + window->getSize().x - panel[0][0]) / 2;
	panel[1][1] = (window->getPosition().y + window->getSize().y - panel[0][1]) / 2;

}

IPView::IPView(IPModel* cmod, sf::RenderWindow& mapWind, int lvl)
{
	cmod->attach(this);
	window = &mapWind;
	inv = cmod->getIP('I');
	chest = cmod->getIP('C');
	characterLevel = lvl;

	cPanel[1][0] = (window->getPosition().x + window->getSize().x - cPanel[0][0]) / 2;
	cPanel[1][1] = (window->getPosition().y + window->getSize().y - cPanel[0][1]) / 2;
}

// draws the different areas onto the window
void IPView::draw(sf::RenderWindow& wind)
{
	window = &wind;

	// light yellow color
	lightYlw.r = 239;
	lightYlw.g = 228;
	lightYlw.b = 176;
	lightYlw.a = 255;

	// pale brown color
	paleBrn.r = 208;
	paleBrn.g = 167;
	paleBrn.b = 145;
	paleBrn.a = 255;

	f.loadFromFile("fonts/Rock.ttf");

	//window background
	windowBg.setSize(sf::Vector2f(panel[0][0], panel[0][1]));
	windowBg.setPosition(panel[1][0], panel[1][1]);
	windowBg.setFillColor(paleBrn);

	//equipment area
	eqp.loadFromFile("images/ui/eqpArea.png");

	eqpArea.setSize(sf::Vector2f(areaSize[0][0], areaSize[0][1]));
	eqpArea.setPosition(panel[1][0] + areaCoords[0][0], panel[1][1] + areaCoords[0][1]);
	eqpArea.setTexture(&eqp);

	// inventory area
	invArea.setSize(sf::Vector2f(areaSize[1][0], areaSize[1][1]));
	invArea.setPosition(panel[1][0] + areaCoords[1][0], panel[1][1] + areaCoords[1][1]);
	invArea.setFillColor(lightYlw);

	// item details area
	detT.loadFromFile("images/ui/detArea.png");
	detArea.setSize(sf::Vector2f(areaSize[2][0], areaSize[2][1]));
	detArea.setPosition(panel[1][0] + areaCoords[2][0], panel[1][1] + areaCoords[2][1]);
	detArea.setTexture(&detT);

	itemDetails.setFont(f);
	itemDetails.setColor(lightYlw);
	itemDetails.setPosition(detArea.getPosition().x + 6, detArea.getPosition().y + 6);
	itemDetails.setCharacterSize(14);

	// stats area
	statsT.loadFromFile("images/ui/statsArea.png");
	statsArea.setSize(sf::Vector2f(areaSize[3][0], areaSize[3][1]));
	statsArea.setPosition(panel[1][0] + areaCoords[3][0], panel[1][1] + areaCoords[3][1]);
	statsArea.setTexture(&statsT);

	stats.setFont(f);
	stats.setColor(lightYlw);
	stats.setPosition(statsArea.getPosition().x + 6, statsArea.getPosition().y + 6);
	stats.setCharacterSize(14);

	//window->clear();

	//cout << "drawing windowBg" << endl;
	window->draw(windowBg);
	
	//cout << "drawing eqpArea" << endl;
	window->draw(eqpArea);
	for (int m = 0; m < eqps->getPouchSize(); m++)
	{
		// setting the texture (image)
		if (eqps->getItems()[m] != NULL)
		{
			eT.loadFromFile(eqps->getItems()[m]->getEquippedItemImage());
			eSlot.setTexture(eT);

			// setting the position of the slot
			eSlot.setPosition(eqpArea.getPosition().x + eCoords[m][0], eqpArea.getPosition().y + eCoords[m][1]);
			window->draw(eSlot);
		}
	}
	
	//cout << "drawing statsArea" << endl;
	//format stats string
	playerStats = updateStats();
	string s = "Player: " + characterName + "\nGender: " + (char)toupper(characterGender) + "\nLevel: " + to_string(characterLevel) + "\n\n";
	for (int x = 0; x < 11; x++)
	{
		
		s += statNames[x] + ": " + to_string(playerStats[x]);

		if (x != 10)
			s += "\n";
	}
	stats.setString(s);

	window->draw(statsArea);
	window->draw(stats);

	//cout << "drawing detArea" << endl;
	window->draw(detArea);
	window->draw(itemDetails);

	//cout << "drawing invArea" << endl;
	window->draw(invArea);
	for (int i = 0; i < inv->getPouchSize(); i++)
	{
		// setting the texture (image)
		if (inv->getItems()[i] == NULL)
			iT.loadFromFile("images/emptyslot.png");
		else if (!iT.loadFromFile(inv->getItems()[i]->getItemImage()))
			iT.loadFromFile("images/dummyslot.png");

		iSlot.setTexture(iT);

		// setting the position of the slot
		float x = ((i % 6) * 50) + 1 + invArea.getPosition().x;
		float y = (floor(i/6) * 50) + 1 + invArea.getPosition().y;
		iSlot.setPosition(x, y);
		window->draw(iSlot);
	}

	window->display();
}

// TO COMPLETE
void IPView::drawChest(sf::RenderWindow& mapWind)
{
	window = &mapWind;

	// light yellow color
	lightYlw.r = 239;
	lightYlw.g = 228;
	lightYlw.b = 176;
	lightYlw.a = 255;

	// pale brown color
	paleBrn.r = 208;
	paleBrn.g = 167;
	paleBrn.b = 145;
	paleBrn.a = 255;

	f.loadFromFile("fonts/Rock.ttf");
	
	// window background
	cWindowBg.setSize(sf::Vector2f(cPanel[0][0], cPanel[0][1]));
	cWindowBg.setPosition(cPanel[1][0], cPanel[1][1]);
	cWindowBg.setFillColor(paleBrn);

	// inventory area
	invArea.setSize(sf::Vector2f(areaSize[1][0], areaSize[1][1]));
	invArea.setPosition(cPanel[1][0] + cAreaCoords[0][0], cPanel[1][1] + cAreaCoords[0][1]);
	invArea.setFillColor(lightYlw);

	// item details area
	detT.loadFromFile("images/ui/detArea.png");
	detArea.setSize(sf::Vector2f(areaSize[2][0], areaSize[2][1]));
	detArea.setPosition(cPanel[1][0] + cAreaCoords[1][0], cPanel[1][1] + cAreaCoords[1][1]);
	detArea.setTexture(&detT);

	itemDetails.setFont(f);
	itemDetails.setColor(lightYlw);
	itemDetails.setPosition(detArea.getPosition().x + 6, detArea.getPosition().y + 6);
	itemDetails.setCharacterSize(14);

	// chest area
	chestT.loadFromFile("images/ui/chestArea.png");
	chestArea.setSize(sf::Vector2f(areaSize[4][0], areaSize[4][1]));
	chestArea.setPosition(cPanel[1][0] + cAreaCoords[2][0], cPanel[1][1] + cAreaCoords[2][1]);
	chestArea.setTexture(&chestT);

	//window->clear();
	
	window->draw(cWindowBg);

	//cout << "drawing invArea" << endl;
	window->draw(invArea);
	for (int i = 0; i < inv->getPouchSize(); i++)
	{
		// setting the texture (image)
		if (inv->getItems()[i] == NULL)
			iT.loadFromFile("images/emptyslot.png");
		else if (!iT.loadFromFile(inv->getItems()[i]->getItemImage()))
			iT.loadFromFile("images/dummyslot.png");

		iSlot.setTexture(iT);

		// setting the position of the slot
		float x = ((i % 6) * 50) + 1 + invArea.getPosition().x;
		float y = (floor(i/6) * 50) + 1 + invArea.getPosition().y;
		iSlot.setPosition(x, y);
		
		window->draw(iSlot);
	}

	//cout << "drawing detArea" << endl;
	window->draw(detArea);
	window->draw(itemDetails);

	//cout << "drawing chestArea" << endl;
	window->draw(chestArea);
	for (int i = 0; i < chest->getPouchSize(); i++)
	{
		// setting the texture (image)
		if (chest->getItems()[i] == NULL)
			cT.loadFromFile("images/emptyslot.png");
		else if (!cT.loadFromFile(chest->getItems()[i]->getItemImage()))
			cT.loadFromFile("images/dummyslot.png");

		cSlot.setTexture(cT);

		// setting the position of the slot
		cSlot.setPosition(chestArea.getPosition().x + cCoords[i][0], chestArea.getPosition().y + cCoords[i][1]);

		window->draw(cSlot);
	}

	window->display();
}

void IPView::update(sf::RenderWindow& invWin)
{
	draw(invWin);
}

void IPView::updateChest(sf::RenderWindow& mapWind)
{
	drawChest(mapWind);
}

// sets the string of the itemDetails object
void IPView::setItemDetails(string str)
{
	sf::Font f;
	f.loadFromFile("fonts/Rock.ttf");
	itemDetails.setPosition(detArea.getPosition().x + 6, detArea.getPosition().y + 6);
	itemDetails.setCharacterSize(14);
	itemDetails.setFont(f);
	itemDetails.setColor(lightYlw);
	itemDetails.setString(str);
}

// updates the player's stats, according to the enhancements of the equipped items
vector<int> IPView::updateStats()
{
	const static int baseStats[11] = {charHP, charMP, charStr, charConst, charWisdom, charIntellint, charDex, charCharisma, charArmorclass, charAttackbonus, charDamagebonus};
	vector<int> newStats(11);
	Controller ctl;


	// initialise newStats to start off at the base stats
	for (int x = 0; x < 11; x++)
		newStats[x] = baseStats[x];

	if (!eqps->isEmpty())	// otherwise, there's no point of adding to the base stats
	{
		// for each item slot..
		Item** e = eqps->getItems();
		for (int x = 0; x < 8; x++)
		{
			if (e[x] != NULL)	// ..that is NOT null..
			{
				int* stats = e[x]->getItemStats();
				// ..accumulate the stats
				for (int y = 0; y < 11; y++)
				{
					newStats[y] += stats[y];
					newStats[0] = (newStats[2]+newStats[3]+newStats[6])*5;
				}
			
			}
		}
	}
	return newStats;
}