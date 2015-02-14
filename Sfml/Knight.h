#pragma once
#include <iostream>
#include "Character.h"
#include "Controller.h"
using namespace std;

class Knight: public Character
{
private:
	int ExtraPoints;
	Controller ctl;
public:
    Knight();
    Knight(string Name, string gender);
	Knight(int strength, int Constitution, int Wisdom, int Intelligence, int Dexterity, int luck,
		int MP, int Charisma, int Level);
	void notify(Knight& NPC);
    void displayStats(Knight& NPC);
    void setExtraPoints(Knight& NPC);
};


