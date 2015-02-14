
#pragma once
#include <iostream>
#include "Character.h"
#include "Controller.h"
using namespace std;

class Sorcerer: public Character
{
private:
	int ExtraPoints;
	Controller ctl;
public:
    Sorcerer();
    Sorcerer(string Name, string gender);
	Sorcerer(int strength, int Constitution, int Wisdom, int Intelligence, int Dexterity, int luck,
		int MP, int Charisma, int Level);
	void notify(Sorcerer& NPC);
    void displayStats(Sorcerer& NPC);
    void setExtraPoints(Sorcerer& NPC);
};

