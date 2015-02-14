#pragma once
#include "stdafx.h"
#include "Controller.h"
#include "Fighter.h"
#include "Archer.h"
#include "Knight.h"
#include "Sorcerer.h"
#include "Builder.h"
#include "FighterBullyConcreteBuilder.h"
#include "FighterNimbleConcreteBuilder.h"
#include "FighterTankConcreteBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

static int value = 0;
static string Type = "";
static string Name = "";
static string Gender = "";
static int counter = 0;

void Controller::HealthBar(sf::RenderWindow& window, int CurrentHP, Character& NPC)
{
	float HP = (float) NPC.getHP();
	float AHP = (float) CurrentHP;
	float Damage = AHP/HP;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("fonts/triforce.ttf");
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(20);
	string test = NPC.getName();
	test += static_cast<char> (CurrentHP/100 +48); test += static_cast<char> ((CurrentHP%100)/10 +48); test += static_cast<char> ((CurrentHP%100)%10 +48);
	test += "/";
	test += static_cast<char> (NPC.getHP()/100 +48); test += static_cast<char> ((NPC.getHP()%100)/10 +48); test += static_cast<char> ((NPC.getHP()%100)%10 +48);
	text.setString(test);
	text.setPosition(600,10);
	sf::RectangleShape CurrentHealth(sf::Vector2f(200*(Damage), 20));
	CurrentHealth.setPosition(600, 15);
	CurrentHealth.setOutlineColor(sf::Color::Black);
	CurrentHealth.setOutlineThickness(2);
	CurrentHealth.setFillColor(sf::Color::Green);
	window.draw(CurrentHealth);
	window.draw(text);
	//window.display();

}

string Controller::retrieveName(Character& NPC)
{
	return NPC.getName();
}

Character Controller::CharacterReturn(sf::RenderWindow& window)
{

	Controller ctl;
	int number;
	string FileName;
	string line;
	Character NPC;
	if(counter == 0)
	{
		Sleep(100);	
		Name = NPC.retrieveName(window);
	}
	/*FileName = Name;
	FileName += "/";*/
	FileName += Name;
	FileName += ".txt";
	ifstream file (FileName);
	if(!file.is_open())
	{
		cout << "FileNotFoundOrSomethingLikeThat\n";
	}
	file >> number;
		
	if (number == 1)
	{
		int temp [16];
		int index = 0;
		while(file >> number)
		{
			temp[index] = number;
			index++;
		}
		Fighter user(temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8], temp[9]);
		user.setName(Name);
		if(counter == 0)
		{
			Gender = user.retrieveGender(window);
			user.setGender(Gender);
		}
		user.setGender(Gender);
		counter++;
		return user;
	}
		file.close();
}

void Controller::Update(Character& NPC, sf::RenderWindow& window, bool output)
{
	Controller ctl;
	ctl.Display(NPC, window, output);
}

std::string Controller::Display(Character& NPC, sf::RenderWindow& window, bool output)
{
	/*bool condition = false;
	while(!condition)
	{*/
		//NPC.displayStats(NPC, window);
		/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			condition = true;
		else
			condition = false;
	}*/
		return NPC.displayStats(NPC, window, output);
}

void Controller::InitialMenu(sf::RenderWindow& window)
{
	bool condition = false;
	Controller ctl;
	while(!condition)
	{
		font.loadFromFile("fonts/Triforce.ttf");
		text.setFont(font);
		text.setCharacterSize(25);
		text.setColor(sf::Color(218,165,32));
		text.setPosition(5, 5);
		text.setString( "Please create your Character\nThe Character created will be saved and available to play the next time\nit's Stats have been radomly generated\nEnjoy!!\n");
		sf::RectangleShape rectangle(sf::Vector2f(sf::VideoMode::getDesktopMode().width -105, sf::VideoMode::getDesktopMode().height -105));
		rectangle.setPosition(3, 3);
		rectangle.setOutlineColor(sf::Color(218,165,32));
		rectangle.setOutlineThickness(10);
		rectangle.setFillColor(sf::Color(0,0,0,0));
		texture.loadFromFile("fonts/Picture2.jpg");
		Background.setTexture(texture);
		window.draw(Background);
		window.draw(rectangle);
		window.draw(text);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			condition = true;
			Sleep(100);
		}
		else
			condition = false;
	}
}

void Controller::ExplainMenu(sf::RenderWindow& window)
{
	bool condition = false;
	Controller ctl;
	while(!condition)
	{
		font.loadFromFile("fonts/Triforce.ttf");
		text.setFont(font);
		text.setCharacterSize(25);
		text.setColor(sf::Color(218,165,32));
		text.setPosition(5,25);
		text.setString("The Character created will be saved and available to play the next time\n");
		text2.setFont(font);
		text2.setCharacterSize(25);
		text2.setColor(sf::Color(218,165,32));
		text2.setPosition(5,50);
		text2.setString("it's Stats have been radomly generated\nEnjoy!!\n");
		window.draw(text);
		window.draw(text2);
		window.display();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			condition = true;
			Sleep(20);
		}
		else
			condition = false;
	}
}


bool Controller::createCharacter(int value, sf::RenderWindow& window)
{
	string decision;
    string decision2;
	string save;
	Controller ctl;
	if(value == 1)
	{
		ctl.InitialMenu(window);
		FighterBullyConcreteBuilder Build1;
		Build1.buildFighter(window);
		ctl.save(Build1.getCharacter());
		ctl.Display(Build1.getCharacter(), window, true);
		return true;
	}
	return false;
}

void Controller::save(Character& NPC)
{
	string save = NPC.getName();
	/*save += "/";
	save += NPC.getName();*/
	save += ".txt";
	ofstream FileOpen(save);
	if(FileOpen.is_open())
	{
		FileOpen << NPC.getClass() << endl;
		FileOpen << NPC.getStrength() << endl;
		FileOpen << NPC.getConstitution() << endl;
		FileOpen << NPC.getWisdom() << endl;
		FileOpen << NPC.getIntelligence() << endl;
		FileOpen << NPC.getDexterity() << endl;
		FileOpen << NPC.getLuck() << endl;
		FileOpen << NPC.getMP() << endl;
		FileOpen << NPC.getCharisma() << endl;
		FileOpen << NPC.getLevel() << endl;
	}
	FileOpen.close();
}

bool Controller::load()
{
	/*cout << "Please Enter your character's name\n";

	Controller ctl;
	int number;
	string FileName;
	string line;	
	string Name = retrieveInput();
	string Gender;
	FileName = Name;
	FileName += ".txt";
	ifstream file (FileName);
	if(!file.is_open())
	{
		cout << "File not found\n";
		file >> number;
		return false;
	}
	file >> number;
		
	if (number == 1)
	{
		int temp [16];
		int index = 0;
		while(file >> number)
		{
			temp[index] = number;
			index++;
		}
		Fighter user(temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8], temp[9]);
		user.setName(Name);
		user.setGender(user.retrieveGender());
		ctl.Update(user);
		
	}

	else if (number == 2)
	{
		int temp [16];
		int index = 0;
		while(file >> number)
		{
			temp[index] = number;
			index++;
		}
		Archer user (temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8]);
		user.setName(Name);
		user.setGender(user.retrieveGender());
		user.displayNameAndGender();
		user.displayStats(user);
		
	}

	else if (number == 3)
	{
		int temp [16];
		int index = 0;
		while(file >> number)
		{
			temp[index] = number;
			index++;
		}
		Knight user (temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8]);
		user.setName(Name);
		user.setGender(user.retrieveGender());
		user.displayNameAndGender();
		user.displayStats(user);
		
	}
	
	else if (number == 4)
	{
		int temp [16];
		int index = 0;
		while(file >> number)
		{
			temp[index] = number;
			index++;
		}
		Sorcerer user (temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8]);
		user.setName(Name);
		user.setGender(user.retrieveGender());
		user.displayNameAndGender();
		user.displayStats(user);
		
	}
		file.close();
		Sleep(3000);*/
		return true;
}


string Controller::retrieveInput()
{
	string input;
	cin >> input; 
	return input;
}

void Controller::UpdateStatsEx(Character& NPC, int difference)
{
	NPC.setStrength(NPC.getStrength());
	NPC.setWisdom(NPC.getWisdom());
	NPC.setIntelligence(NPC.getIntelligence());
	NPC.setConstitution(NPC.getConstitution());
	NPC.setDexterity(NPC.getDexterity());
	NPC.setCharisma(NPC.getCharisma());
	NPC.setMP(NPC.getMP());
	updateFormulatedStatsForLevel(NPC);
}

void Controller::UpdateStats(Character& NPC, int difference)
{
	vector<int> equippedStats = items.updateStats();

	NPC.setStrength(NPC.getStrength()+equippedStats[2]);
	NPC.setWisdom(NPC.getWisdom()+equippedStats[4]);
	NPC.setIntelligence(NPC.getIntelligence()+equippedStats[5]);
	NPC.setConstitution(NPC.getConstitution()+equippedStats[3]);
	NPC.setDexterity(NPC.getDexterity()+equippedStats[6]);
	NPC.setCharisma(NPC.getCharisma()+equippedStats[7]);
	NPC.setMP(NPC.getMP()+equippedStats[1]);
	updateFormulatedStatsForLevel(NPC);
	//updateFormulatedStats(NPC);
}

void Controller::levelUp(Character& NPC)
{
	NPC.setStrength(NPC.getStrength()+2);
	NPC.setWisdom(NPC.getWisdom()+2);
	NPC.setIntelligence(NPC.getIntelligence()+2);
	NPC.setConstitution(NPC.getConstitution()+2);
	NPC.setDexterity(NPC.getDexterity()+2);
	NPC.setCharisma(NPC.getCharisma()+2);
	NPC.setIntelligence(NPC.getIntelligence()+2);
	NPC.setMP(NPC.getMP()+1);
	updateFormulatedStatsForLevel(NPC);
	NPC.setLevel(NPC.getLevel() + 1);
}

void Controller::updateFormulatedStatsForLevel(Character& NPC)
{
	NPC.setAttackBonus ( int (NPC.getLevel()*(NPC.getStrength() + NPC.getDexterity())/4));
	NPC.setDamageBonus ( int ((NPC.getStrength())/4));
    NPC.setHP((NPC.getConstitution() + NPC.getStrength() + NPC.getDexterity())*5);
	NPC.setArmorClass (int ((NPC.getDexterity()/2) ));
	NPC.setAttack ( NPC.getStrength() +  NPC.getDamageBonus() + NPC.getAttackBonus() );
}

void Controller::updateFormulatedStats(Character& NPC)
{
	vector<int> equippedStats = items.updateStats();

	NPC.setAttackBonus ( int (NPC.getLevel()*(NPC.getStrength() + NPC.getDexterity() + equippedStats[9])/4));
	NPC.setDamageBonus ( int ((NPC.getStrength() + equippedStats[10])/4));
    NPC.setHP((NPC.getConstitution() + NPC.getStrength() + NPC.getDexterity())*5);
	NPC.setArmorClass (int ((NPC.getDexterity() + equippedStats[8])/2) );
	NPC.setAttack ( NPC.getStrength() +  NPC.getDamageBonus() + NPC.getAttackBonus() );
}

void Controller::returnString()
{
	cout  << "The Dice type was: "  << Type << " The value was: ";
	cout  << value << endl;
}

int Controller::Dice()
{
	int Dice;
	Controller ctl;
	static const int alphanum[] = {1,2,3,4,5,6};
	Dice = alphanum[rand()%(6)];
	value = Dice;
	Type = "D6";
    return Dice;
}

int Controller::Dice1d8()
{
	int Dice;
	Controller ctl;
	static const int alphanum[] = {1,2,3,4,5,6,7,8};
	Dice = alphanum[rand()%(8)];
	value = Dice;
	Type = "D8";
	returnString();
    return Dice;
}

int Controller::Dice1d10()
{
	int Dice;
	Controller ctl;
	static const int alphanum[] = {1,2,3,4,5,6,7,8,9,10};
	Dice = alphanum[rand()%(10)];
	value = Dice;
	Type = "D10";
    return Dice;
}

int Controller::Dice4d6()
{
	int value = 1; 
	int total = 0;
	int current;
	int minimum = 6;
	Controller ctl;
	while(value != 5)
	{
		current = ctl.Dice();
		total += current;
		if(current <= minimum)
		{
			minimum = current;
		}
		value++;
	}
	total -= minimum;
	return total;
}


void Controller::BaseStats(Character& NPC)
{
	array [0] = NPC.getMP();
	array [1] = NPC.getStrength();
	array [2] = NPC.getConstitution();
	array [3] = NPC.getWisdom();
	array [4] = NPC.getIntelligence();
	array [5] = NPC.getDexterity();
	array [6] = NPC.getCharisma();
	array [7] = NPC.getArmorClass();
	array [8] = NPC.getAttackBonus();
	array [9] = NPC.getDamageBonus();
	array [10] = NPC.getLuck();
	array [11] = NPC.getLevel();
}

void Controller::LevelUpBaseStats()
{
	array [0] = array [0] + 1;
	array [1] = array [1] + 2;
	array [2] = array [2] + 2;
	array [3] = array [3] + 2;   
	array [4] = array [4] + 2;
	array [5] = array [5] + 2;
	array [6] = array [6] + 2;
	array [10] = array [10];
	array [11] = array [11] + 1;
}

void Controller::Damage(Character& NPC, int damage)
{
	NPC.setHP(NPC.getHP() - damage);
}

void Controller::useMP(Character& NPC)
{
	NPC.setMP(NPC.getMP() - 1);
}

void Controller::ExpGain (Character& NPC, int exp)
{
	if(NPC.getNextLevel() - exp > 0)
	{
		NPC.setNextLevel(NPC.getNextLevel() - exp);
	}
	else
	{
		levelUp(NPC);
		NPC.setLevel(NPC.getLevel()+1);
		NPC.setNextLevel(100);
	}
		
}

Character Controller::generateEnemies(sf::RenderWindow& window, Character& NPC)
{
	 Controller ctl;
	 bool condition = false;
	 int number = 0;
	 string Monster = Monster;
	 Fighter enemy;
	 enemy.setAI(true);
	 enemy.setExtraPoints(enemy);
	 enemy.setGender("male");
	 Monster = ctl.nameGenerator();
	 enemy.setName(Monster);
	 if (NPC.getLevel() != 1)
	 {
		 number = NPC.getLevel();
		 while(number != 1)
		 {
			 ctl.levelUp(enemy);
			 number--;
		 }
	 }
	 ctl.Update(enemy, window, false);
	 return enemy;
}

string Controller::nameGenerator()
{
	string Name;
	static const string alphanum[] = {"Joey","Skyrim","Milla","Jude","Jade","Sora","Riku"};
    Name = alphanum[rand() % (7)];
    return Name;
}

void Controller::createGenericCharacter()
{
	Controller ctl;
	int number;
	string line;	
	string Gender;
	string FileName = "John.txt";
	ifstream file (FileName);
	if(!file.is_open())
	{
		cout << "File not found, system will not now exit\n";
		file >> number;
		Sleep(10000);
		exit(0);
	}
	file >> number;
		
	int temp [16];
	int index = 0;
	while(file >> number)
	{
		temp[index] = number;
		index++;
	}
	Fighter user(temp[0], temp[1], temp[2], temp[3],temp[4], temp[5], temp[6],temp[7], temp[8], temp[9]);
	user.setName("John");
	user.setGender("male");
	Sleep(100000);
}

void Controller::loadItems(sf::RenderWindow& invWin, Character& NPC)
{
	//items = IPController(invWin, NPC.getName(), NPC.getLevel(), NPC.getGender().at(0));
	items = IPController(invWin, NPC);
}