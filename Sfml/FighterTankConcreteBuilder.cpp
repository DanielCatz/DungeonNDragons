#include "stdafx.h"
#include "FighterTankConcreteBuilder.h"


void FighterTankConcreteBuilder::buildFighter(sf::RenderWindow& window)
{
	Controller ctl;
	NPC.setStrength(6+ctl.Dice4d6());
	NPC.setConstitution(13+ctl.Dice4d6());
    NPC.setWisdom(2+ctl.Dice4d6());
    NPC.setIntelligence(4+ctl.Dice4d6());
    NPC.setDexterity(11+ctl.Dice4d6());
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

	//ctl.Update(NPC, window);
	//cout << "-Type: Tank\n" << endl;
	Sleep(200);
}
