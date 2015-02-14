/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once
#include "ItemPouch.h"
#include "Observer.h"
#include "IPModel.h"
#include "Character.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class IPView : public Observer
{
public:
	IPView();
	IPView(IPModel*, sf::RenderWindow&, string, int, char);
	IPView(IPModel*, sf::RenderWindow&, int);
	IPView(IPModel*, sf::RenderWindow&, Character&);
	void draw(sf::RenderWindow&);
	void drawChest(sf::RenderWindow&);
	void update(sf::RenderWindow&);
	void updateChest(sf::RenderWindow&);
	void setItemDetails(string);
	vector<int> updateStats();

private:
	sf::RenderWindow* window;
	sf::Color lightYlw;
	sf::Color paleBrn;
	sf::Font f;

	sf::RectangleShape windowBg;
	sf::RectangleShape cWindowBg;

	sf::Texture eqp;
	sf::RectangleShape eqpArea;
	sf::Sprite eSlot;
	sf::Texture eT;

	sf::RectangleShape invArea;
	sf::Sprite iSlot;
	sf::Texture iT;

	sf::Texture detT;
	sf::RectangleShape detArea;
	sf::Text itemDetails;

	sf::Texture statsT;
	sf::RectangleShape statsArea;
	sf::Text stats;

	sf::Event event;

	sf::Texture chestT;
	sf::RectangleShape chestArea;
	sf::Sprite cSlot;
	sf::Texture cT;

	ItemPouch* inv;
	ItemPouch* eqps;
	ItemPouch* chest;

	vector<int> playerStats;	// unsure if needed
	string characterName;
	int characterLevel;
	char characterGender;
	int charHP,charMP,charStr, charConst, charWisdom, charIntellint, charDex, charCharisma, charArmorclass,charAttackbonus,charDamagebonus;

};

