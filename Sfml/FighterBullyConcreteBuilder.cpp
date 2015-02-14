#include "stdafx.h"
#include "FighterBullyConcreteBuilder.h"


void FighterBullyConcreteBuilder::buildFighter(sf::RenderWindow& window)
{
	Controller ctl;
	NPC.setStrength(16+ctl.Dice4d6());
	NPC.setConstitution(6+ctl.Dice4d6());
    NPC.setWisdom(2+ctl.Dice4d6());
    NPC.setIntelligence(4+ctl.Dice4d6());
    NPC.setDexterity(5+ctl.Dice4d6());
    NPC.setLuck(5+ctl.Dice4d6());
    NPC.setMP(5+ctl.Dice4d6());
    NPC.setCharisma(3+ctl.Dice4d6());
	NPC.setLevel(1);
    NPC.setNextLevel(40);
	NPC.setName(NPC.retrieveName(window));
	NPC.setGender(NPC.retrieveGender(window));
	NPC.setX(0);
	NPC.setY(0);
	NPC.setClass(1);
	NPC.setAI(false);
	NPC.setAttackPerTurn(1);
	ctl.updateFormulatedStatsForLevel(NPC);
	Sleep(200);
	//ctl.Update(NPC, window);
	//cout << "-Type: Bully\n" << endl;
}
