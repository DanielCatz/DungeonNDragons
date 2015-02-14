#pragma once
#include <iostream>
#include "Character.h"
#include "Controller.h"
using namespace std;

class Archer: public Character
{
private:
	int ExtraPoints;
	Controller ctl;
public:
    Archer();
    Archer(string Name, string gender);
	Archer(int strength, int Constitution, int Wisdom, int Intelligence, int Dexterity, int luck,
		int MP, int Charisma, int Level);
	void notify(Archer& NPC);
    void displayStats(Archer& NPC);
    void setExtraPoints(Archer& NPC);
};
