#pragma once
#include "Character.h"
#include "Fighter.h"
#include <SFML/Graphics.hpp>

class Builder
{
public:
    Character getCharacter(){ return Character(); }
    //build a generic Fighter
    void CreateNewFighter(){ Fighter NPC; }
    //create each part of the Product according to subtypes
    virtual void buildFighter(sf::RenderWindow& window) = 0;
  public:
    Character NPC;

};

