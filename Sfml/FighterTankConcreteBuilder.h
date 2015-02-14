#pragma once
#include "Builder.h"
#include "Controller.h"
#include <string>

class FighterTankConcreteBuilder: public Builder
{
public:
	virtual void buildFighter(sf::RenderWindow& window);
	virtual Character getCharacter() {return NPC; }
};
