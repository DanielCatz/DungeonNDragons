#pragma once
#include <iostream>
#include "Character.h"
#include "Controller.h"
using namespace std;

class Fighter: public Character
{
private:
	int ExtraPoints;
	Controller ctl;
	enum FighterType {Bully = 0, Nimble = 1, Tank = 2} type;
public:
    Fighter();
    Fighter(string Name, string gender);
	Fighter(int strength, int Constitution, int Wisdom, int Intelligence, int Dexterity, int luck,
		int MP, int Charisma, int Level, int APT);
	void setType(Fighter& NPC);
	void getType();
	void notify(Fighter& NPC);
    void displayStats(Fighter& NPC);
    void setExtraPoints(Fighter& NPC);
};
