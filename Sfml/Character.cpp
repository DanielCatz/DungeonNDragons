#pragma once
#include "stdafx.h"
#include <iostream>
#include "Character.h"
#include "Controller.h"
#include "ItemPouch.h"
#include <string>
using namespace std;

sf::Sprite Background;
sf::Texture texture;
sf::RectangleShape rectangle(sf::Vector2f(490, 490));
sf::Font font;
sf::Text text;

    //default constructor
    Character::Character()
    {
        Strength = 0;
        Constitution = 0;
        Wisdom = 0;
        Intelligence = 0;
        Dexterity = 0;
        Luck = 0;
        MP = 0;
        Charisma = 0;
        Level = 1;
        nextLevel = 40;
        Name = "hello";
        gender = "female";
        AttackBonus = 0;
        DamageBonus = 0;
        Attack = 0;
        HP = 0;
        ArmorClass = 0;
		x = 0;
		y = 0;
		Class = 0;
		AttackingPhase = 0;
    }
    //parametrized constructor
    Character::Character(string Name, string gender)
    {
        Strength = 0;
        Constitution = 0;
        Wisdom = 0;
        Intelligence = 0;
        Dexterity = 0;
        Luck = 0;
        MP = 0;
        Charisma = 0;
        Level = 1;
        nextLevel = 40;
        Name = gender;
        gender = Name;
        AttackBonus = 0;
        DamageBonus = 0;
        Attack = 0;
        HP = 0;
        ArmorClass = 0;
		x = 0;
		y = 0;
		Class = 0;
		AttackingPhase = 0;
    }

	std::string Character::displayStats(Character& NPC, sf::RenderWindow& window, bool output)
	{
		sf::Font Font;
		sf::Text text("Begin", Font);
		texture.loadFromFile("fonts/Picture2.jpg");
		sf::RectangleShape rectangle(sf::Vector2f(sf::VideoMode::getDesktopMode().width -105, sf::VideoMode::getDesktopMode().height -105));
		rectangle.setPosition(3, 3);
		rectangle.setOutlineColor(sf::Color(218,165,32));
		rectangle.setOutlineThickness(10);
		rectangle.setFillColor(sf::Color(0,0,0,0));
		Background.setTexture(texture);
		Font.loadFromFile("fonts/Triforce.ttf");
		text.setCharacterSize(25);
		text.setColor(sf::Color(218,165,32));
		text.setPosition(5,5);
		
		string test = "\n-Name: " + NPC.getName();
		test += "\n-Gender: " + NPC.getGender();
		test += "\n-Strength: "; test += static_cast<char> (NPC.getStrength()/10 +48); test += static_cast<char> (NPC.getStrength()%10 +48); 
		test += "\n-Constitution: "; test += static_cast<char> (NPC.getConstitution()/10 + 48); test += static_cast<char> (NPC.getConstitution()%10 + 48);
		test += "\n-Wisdom: "; test += static_cast<char>(NPC.getWisdom()/10 + 48); test += static_cast<char>(NPC.getWisdom()%10 + 48); 
		test += "\n-Intelligence: "; test += static_cast<char>(NPC.getIntelligence()/10 + 48); test += static_cast<char>(NPC.getIntelligence()%10 + 48);
		test +=  "\n-Dexterity: "; test += static_cast<char>(NPC.getDexterity()/10 + 48); test += static_cast<char>(NPC.getDexterity()%10 + 48);
		test += "\n-Luck: "; test += static_cast<char> (NPC.getLuck()/10 + 48); test += static_cast<char> (NPC.getLuck()%10 + 48); 
		if(NPC.getHP() <= 0)
		{
			test += "\n-HP: 0";
		}
		else
		{
			test += "\n-HP: "; test += static_cast<char> (NPC.getHP()/100 +48); test += static_cast<char> ((NPC.getHP()%100)/10 +48); test += static_cast<char> ((NPC.getHP()%100)%10 +48);
		}
		test += "\n-MP: "; test += static_cast<char>(NPC.getMP()/10 +48); test += static_cast<char> (NPC.getMP()%10 +48); 
		test += "\n-Attack Bonus: "; test += static_cast<char> (NPC.getAttackBonus()/10 + 48);  test += static_cast<char> (NPC.getAttackBonus()%10 + 48);
		test += "\n-Damage Bonus: "; test += static_cast<char>(NPC.getDamageBonus()/10 + 48); test += static_cast<char>(NPC.getDamageBonus()%10 + 48);
		test += "\n-Attack: "; test += static_cast<char>(NPC.getAttack()/100 +48);  test += static_cast<char>((NPC.getAttack()%100)/10 +48); test += static_cast<char>((NPC.getAttack()%100)%10 +48);
		test += "\n-Armor Class: "; test += static_cast<char> (NPC.getArmorClass()/10 +48); test += static_cast<char> (NPC.getArmorClass()%10 +48);
		test +="\n-Class: "; test += NPC.toString(NPC.getClass()); test+= "\n-Level: "; test += static_cast<char>(NPC.getLevel()/10 +48);
		test += static_cast<char>(NPC.getLevel()%10 +48);
		test +="\n"; 
		text.setString(test);
		if(output)
		{
			window.clear();
			window.draw(Background);
			window.draw(rectangle);
			window.draw(text);
			window.display();
			Sleep(2000);
			return test;		
		}
		else
		{
			return test;
		}
	}

	void Character::notify(Character& NPC)
	{
		//Controller ctl;
		//ctl.Update(NPC);
	}

	void Character::attach(Character* NPC)
	{
		bool condition = false;
		int index = 0;
		while(!condition)
		{
			if((List [index]) == 0)
			{
				List [index] = 0;
				condition = true;
			}
		}
		List [index] = NPC;
	}
	
	void Character::detach(Character* NPC)
	{
		bool condition = false;
		int index2 = 0;
		while(!condition)
		{
			if(NPC == (List [index2]))
			{
				List [index2] = 0;
				condition = true;
			}
		}
	}

	string Character::toString(int value)
	{
		if(value == 1)
			return "Fighter";
		else if(value == 2)
			return "Archer";
		else if(value == 3)
			return "Knight";
		else if(value == 4)
			return "Sorcerer";
		else
			return "12345";
	}

	void Character::setAI(bool AI)
	{
		enemyAI = AI;
	}

	bool Character::getAI()
	{
		return enemyAI;
	}

	int Character::getX()
	{
		return x;
	}

	int Character::getY()
	{
		return y;
	}

	void Character::setX(int value)
	{
		x = value;
	}

	void Character::setY(int value)
	{
		y = value;
	}

    //retrieve strength
    int Character::getStrength()
    {
        return Strength;
    }
	void Character::setStrength(int value)
	{
		Strength = value;
	}

	int Character::getHP()
	{
		return HP;
	}

	void Character::setHP(int value)
	{
		HP = value;
	}

	int Character::getMP()
	{
		return MP;
	}

	void Character::setMP(int value)
	{
		MP = value;
	}

	int Character::getAttackPerTurn()
	{
		return AttackingPhase;
	}
	
	void Character::setAttackPerTurn(int value)
	{
		AttackingPhase = value;
	}


    //check if weapon is equipped
    bool Character::isEquipWeapon(ItemPouch* eqps)
    {
        //if weapon equipped return true, else false
        return (eqps->getItems()[4] != NULL);
    }

    //check if armor is equipped
    bool Character::isEquipArmor(ItemPouch* eqps)
    {
        //if armor is equipped return true, else false
        return (eqps->getItems()[3] != NULL);
    }

    //check if Shield is equipped
    bool Character::isEquipShield(ItemPouch* eqps)
    {
        //if Shield equipped return true, else false
        return (eqps->getItems()[5] != NULL);
    }

    //check if weapon is equipped
    bool Character::isEquipRing(ItemPouch* eqps)
    {
        //if weapon equipped return true, else false
        return (eqps->getItems()[1] != NULL || eqps->getItems()[2] != NULL);
    }

    //check if Helmet is equipped
    bool Character::isEquipHelmet(ItemPouch* eqps)
    {
        //if Helmet is equipped return true, else false
        return (eqps->getItems()[0] != NULL);
    }

    //check if Helmet is equipped
    bool Character::isEquipBoots(ItemPouch* eqps)
    {
        //if Helmet is equipped return true, else false
        return (eqps->getItems()[7] != NULL);
    }

    //check if belt is equipped
    bool Character::isEquipBelt(ItemPouch* eqps)
    {
        //if belt is equipped return true, else false
        return (eqps->getItems()[6] != NULL);
    }

    //retrieve Constitution
    int Character::getConstitution()
    {
        return Constitution;
    }

	void Character::setConstitution(int value)
	{
		Constitution = value;
	}

    //retrieve Wisdom
    int Character::getWisdom()
    {
        return Wisdom;
    }

	void Character::setWisdom(int value)
	{
		Wisdom = value;
	}

    //retrieve intelligence
    int Character::getIntelligence()
    {
        return Intelligence;
    }

	void Character::setIntelligence(int value)
	{
		Intelligence = value;
	}


    //retrieve dexterity
    int Character::getDexterity()
    {
        return Dexterity;
    }

	void Character::setDexterity(int value)
	{
		Dexterity = value;
	}

    //retrieve luck
    int Character::getLuck()
    {
        return Luck;
    }

	void Character::setLuck(int value)
	{
		Luck = value;
	}

    //retrieve charisma
    int Character::getCharisma()
    {
        return Charisma;
    }

	void Character::setCharisma(int value)
	{
		Charisma = value;
	}

    //retrieve level
    void Character::retrieveLevel()
    {
        cout << "You are Level" << Level <<"\n";
    }

	int Character::getLevel()
	{
		return Level;
	}

	void Character::setLevel(int value)
	{
		Level = value;
	}

	int Character::getNextLevel()
	{
		return nextLevel;
	}

	void Character::setNextLevel(int value)
	{
		nextLevel = value;
	}

	int Character::getAttack()
	{
		return Attack;
	}

	void Character::setAttack(int value)
	{
		Attack = value;
	}

	int Character::getAttackBonus()
	{
		return AttackBonus;
	}

	void Character::setAttackBonus(int value)
	{
		AttackBonus = value;
	}

	int Character::getDamageBonus()
	{
		return DamageBonus;
	}

	void Character::setDamageBonus(int value)
	{
		DamageBonus = value;
	}
	
	int Character::getArmorClass()
	{
		return ArmorClass;
	}

	void Character::setArmorClass(int value)
	{
		ArmorClass = value;
	}
    //retrieve how much exp points needed to level up
    void Character::retrieveNextLevel()
    {
        cout << "To reach the next Level, you need:" << getNextLevel() << "\n";
    }

   int Character::getClass()
   {
	   return Class;
   }

   void Character::setClass(int value)
   {
	   Class = value;
   }
	
	//retrieve the name of the character and return it
    string Character::getName()
    {
        return Name;
    }

	string Character::retrieveName(sf::RenderWindow& window)
    {
        Name = "";
		bool condition = false;
		font.loadFromFile("fonts/Triforce.ttf");
		sf::Text text2;
		text2.setColor(sf::Color(218,165,32));
		text2.setFont(font);
		text2.setString("");
		while(!condition)
		{
			sf::Event event;
			text.setFont(font);
			text.setCharacterSize(25);
			text.setColor(sf::Color(218,165,32));
			text.setPosition(5, 5);
			text.setString( "Please enter the name of your character\n");
			sf::RectangleShape rectangle(sf::Vector2f(sf::VideoMode::getDesktopMode().width -105, sf::VideoMode::getDesktopMode().height -105));
			rectangle.setPosition(3, 3);
			rectangle.setOutlineColor(sf::Color(218,165,32));
			rectangle.setOutlineThickness(10);
			rectangle.setFillColor(sf::Color(0,0,0,0));
			texture.loadFromFile("fonts/Picture2.jpg");
			Background.setTexture(texture);
			window.clear();
			window.draw(Background);
			window.draw(rectangle);
			window.draw(text);
			window.draw(text2);
			window.display();

				
		
			while (window.pollEvent(event))
			{
				if(event.type == sf::Event::TextEntered)
				{
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						condition = true;
						return Name;
					}
					else if (event.text.unicode < 128 && !isspace(event.text.unicode))				
					{
						Name += static_cast<char>(event.text.unicode);
						text2.setString(Name);
						text2.setPosition(5,25);
					}
				}
			}

			
		}
	    return Name;
    }

    //setting the user name
    void Character::setName(string userName)
    {
        Name = userName;
    }
	//settting the user gender
    void Character::setGender(string userGender)
    {
        gender = userGender;
    }

    //display gender and name
    void Character::displayNameAndGender(sf::RenderWindow& window)
    {
		/*bool condition = false;
		sf::Text text;
		font.loadFromFile("fonts/Triforce.ttf");
		text.setColor(sf::Color(218,165,32));
		text.setFont(font);
		text.setCharacterSize(25);
		text.setPosition(5,25);
		string output = "-Name: " + Name + "\n-Gender: " + gender;
		text.setString(output);
		window.draw(text);
		window.display();*/
    }

	
	string Character::getGender()
    {
        return gender;
    }

	//retrieve the gender of the character and return it
    string Character::retrieveGender(sf::RenderWindow& window)
    {
        //variables
        bool a = false;
		bool condition = false;
		gender = "";
		font.loadFromFile("fonts/Triforce.ttf");
		sf::Text text2;
		text2.setColor(sf::Color(218,165,32));
		text2.setFont(font);

        //loops until we have an actual gender for the character
        while (a==false)
        {
			while(!condition)
			{
				sf::Event event;
				text.setFont(font);
				text.setCharacterSize(25);
				text.setColor(sf::Color(218,165,32));
				text.setPosition(5, 5);
				text.setString( "Please enter your gender\n");
				sf::RectangleShape rectangle(sf::Vector2f(sf::VideoMode::getDesktopMode().width -105, sf::VideoMode::getDesktopMode().height -105));
				rectangle.setPosition(3, 3);
				rectangle.setOutlineColor(sf::Color(218,165,32));
				rectangle.setOutlineThickness(10);
				rectangle.setFillColor(sf::Color(0,0,0,0));
				texture.loadFromFile("fonts/Picture2.jpg");
				Background.setTexture(texture);
				window.clear();
				window.draw(Background);
				window.draw(rectangle);
				window.draw(text);
				window.draw(text2);
				window.display();
		
				while (window.pollEvent(event))
				{
					if(event.type == sf::Event::TextEntered)
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						condition = true;
						return gender;						
					}else if (event.text.unicode < 128)
						{
							gender += static_cast<char>(event.text.unicode);
							text2.setString(gender);
							text2.setPosition(5,25);
							if(gender == "Male" || gender == "male" || gender == "M" || gender == "m")
							{
								gender = "male";
								a = true;
							}

							//if user is female then set gender as female and return it
							else if(gender == "Female" || gender == "female" || gender == "F" || gender == "f")
							{
								gender = "female";
								a = true;
							}
						}
							
						}
				}
				
			}
		}
        return "";

    }
