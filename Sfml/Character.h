#pragma once
#include "stdafx.h"
#include "ItemPouch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>


using namespace std;

class Character
{
private:
		//variables
		int Strength;
        int Constitution;
        int Wisdom;
        int Intelligence;
        int Dexterity;
        int Luck;
        int HP;
        int MP;
        int Charisma;
        int Level;
        int nextLevel;
        int DamageBonus;
        int AttackBonus;
        int ArmorClass;
        int Attack;
		int x;
		int y;
		int AttackingPhase;
        bool equipWeapon;
        bool equipArmor;
        bool equipBelt;
        bool equipHelmet;
        bool equipShield;
        bool equipBoots;
		bool enemyAI;
        int equipRing;
		int Class;
        string Name;
        string gender;
		Character* List [10];

public:
	
		//methods
		Character();
		Character(string Name, string gender);
		void notify(Character& NPC);
		void attach(Character* NPC);
		void detach(Character* NPC);
		string toString(int value);
		int getStrength();
		int getHP();
		void setStrength(int value);
		void setHP(int value);
		int getMP();
		int getAttackPerTurn();
		void setAttackPerTurn(int value);
		void setMP(int value);
		bool isEquipWeapon(ItemPouch* eqps);
		bool isEquipArmor(ItemPouch* eqps);
		bool isEquipShield(ItemPouch* eqps);
		bool isEquipRing(ItemPouch* eqps);
		bool isEquipHelmet(ItemPouch* eqps);
		bool isEquipBoots(ItemPouch* eqps);
		bool isEquipBelt(ItemPouch* eqps);
		int getConstitution();
		void setConstitution(int value);
		int getWisdom();
		void setWisdom(int value);
		int getIntelligence();
		void setIntelligence(int value);
		int getDexterity();
		void setDexterity(int value);
		int getLuck();
		void setLuck(int value);
		int getCharisma();
		void setCharisma(int value);
		int getLevel();
		void retrieveLevel();
		void setLevel(int value);
		int getNextLevel();
		void setNextLevel(int value);
		int getAttack();
		void setAttack(int value);
		void retrieveNextLevel();
		int getAttackBonus();
		void setAttackBonus(int value);
		int getDamageBonus();
		void setDamageBonus(int value);
		int getArmorClass();
		void setArmorClass(int value);
		string getName();
		string retrieveName(sf::RenderWindow&);
		void setName(string userName);
		void setGender(string userGender);
		void displayNameAndGender(sf::RenderWindow& window);
		std::string displayStats(Character& NPC, sf::RenderWindow& window, bool output);
		string getGender();
		void setAI(bool AI);
		string retrieveGender(sf::RenderWindow&);
		bool getAI();
		void setX(int value);
		void setY(int value);
		int getX();
		int getY();
		int getClass();
		void setClass(int value);
};

