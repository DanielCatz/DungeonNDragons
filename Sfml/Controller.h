#pragma once
#include <iostream>
#include "stdafx.h"
#include "Character.h"
#include "IPController.h"
#include <SFML/Graphics.hpp>
#include <windows.h>


using namespace std;

class Controller
{
public:
	Character* enemyArray [10];
	void updateFormulatedStatsForLevel(Character& NPC);
	void UpdateStatsEx(Character& NPC, int difference);
	void returnString();
	void Controller::HealthBar(sf::RenderWindow& window, int CurrentHP, Character& NPC);
	int Dice();
	int Dice1d8();
	int Dice4d6();
	int Dice1d10();
	virtual string retrieveName(Character& NPC);
	virtual void createGenericCharacter();
	virtual string nameGenerator();
	virtual void Update(Character& NPC, sf::RenderWindow& window, bool output);
	virtual void save(Character& NPC);
	virtual bool load();
	virtual string retrieveInput();
	virtual void InitialMenu(sf::RenderWindow&);
	virtual void ExplainMenu(sf::RenderWindow&);
	virtual bool createCharacter(int value, sf::RenderWindow& window);
	virtual std::string Display(Character& NPC, sf::RenderWindow& window, bool output);
	virtual void UpdateStats(Character& NPC, int difference);
	virtual void levelUp (Character& NPC);
	virtual void updateFormulatedStats(Character& NPC);
	virtual void Damage(Character& NPC, int damage);
	virtual void useMP(Character& NPC);
	virtual void ExpGain (Character& NPC, int exp);
	virtual Character generateEnemies(sf::RenderWindow& window, Character& NPC);
	virtual Character CharacterReturn(sf::RenderWindow&);
	virtual void loadItems(sf::RenderWindow&, Character& NPC);
	//virtual void showInventory(sf::RenderWindow&);
	void BaseStats(Character& NPC);
	void LevelUpBaseStats();
	
private:
	IPController items;
	int array[14];
	sf::Sprite Background;
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
};