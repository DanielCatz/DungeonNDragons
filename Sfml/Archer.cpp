#pragma once
#include "stdafx.h"
#include <iostream>
#include "Archer.h"
#include <string>

    //archer defautl constructor
    Archer::Archer()
    {
        setStrength(6);
        setConstitution(6);
        setWisdom(3);
        setIntelligence(4);
        setDexterity(7);
        setLuck(4);
        setMP(5);
        setCharisma(2);
        ExtraPoints = 3;
        setLevel(1);
        setNextLevel(40);
        setName("none");
        setGender("none");
        setAttackBonus(int (getLevel() * (getStrength() + getDexterity())/4));
        setDamageBonus(int(getStrength()/4));
        setAttack(getStrength() +  getDamageBonus() + getAttackBonus());
        setHP ((getConstitution() + getStrength() + getDexterity())*5);
        setArmorClass(getDexterity()/2);
		setClass(2);
		setX(0);
		setY(0);
    }
    //parametrized constructor
    Archer::Archer (string Name, string gender)
    {
        setStrength(6);
        setConstitution(6);
        setWisdom(3);
        setIntelligence(4);
        setDexterity(7);
        setLuck(4);
        setMP(5);
        setCharisma(2);
        ExtraPoints = 3;
        setLevel(1);
        setNextLevel(40);
        setName(Name);
        setGender(gender);
        setAttackBonus(int (getLevel() * (getStrength() + getDexterity())/4));
        setDamageBonus(int(getStrength()/4));
        setAttack(getStrength() +  getDamageBonus() + getAttackBonus());
        setHP ((getConstitution() + getStrength() + getDexterity())*5);
        setArmorClass(getDexterity()/2);
		setClass(2);
		setX(0);
		setY(0);
    }

	Archer::Archer(int str, int Cst, int Wis, int Int, int Dex, int lck, int MP, int Cha, int Lvl)
	{
		setStrength(str);
        setConstitution(Cst);
        setWisdom(Wis);
        setIntelligence(Int);
        setDexterity(Dex);
        setLuck(lck);
        setMP(MP);
        setCharisma(Cha);
        ExtraPoints = 0;
        setLevel(Lvl);
        setNextLevel(40);
        setName("");
        setGender("");
        setAttackBonus(int (getLevel() * (getStrength() + getDexterity())/4));
        setDamageBonus(int(getStrength()/4));
        setAttack(getStrength() +  getDamageBonus() + getAttackBonus());
        setHP ((getConstitution() + getStrength() + getDexterity())*5);
        setArmorClass(getDexterity()/2);
		setX(0);
		setY(0);
		setClass(2);
	}
	void Archer::notify(Archer& NPC)
	{
		//ctl.Update(NPC);
	}

    //Disply archer stats
    void Archer::displayStats (Archer& NPC)
    {
        cout << "-Strength: " << NPC.getStrength() << "\n-Constitution: " << NPC.getConstitution() << "\n-Wisdom: " 
			<< NPC.getWisdom() << "\n-Intelligence: " << NPC.getIntelligence() << "\n-Dexterity: " << NPC.getDexterity() 
			<<"\n-Luck: " << NPC.getLuck() << "\n-HP: " << NPC.getHP() << "\n-MP: " << NPC.getMP() << "\n-Attack Bonus: " 
			<< NPC.getAttackBonus() << "\n-Damage Bonus: " << NPC.getDamageBonus() << "\n-Attack: "<< getAttack() 
			<< "\n-Armor Class: " << getArmorClass()  << "\n-ExtraPoints: " << ExtraPoints << "\n-Class: Sorcerer \n-Level: " 
			<< NPC.getLevel() << "\n-Next Level: "<< NPC.getNextLevel() << "\n" ;
    }

    //enables user to set the extra Points to personalize his character
    void Archer::setExtraPoints (Archer& NPC)
    {
        while(ExtraPoints != 0)
        {
            //Display message and retrieve the user's input
            string choice;
            cout << "You have: " << ExtraPoints << "\nWhat would you like to improve\n";
            cout << "-To improve Strength, please enter Strength, strength, Str or str\n";
            cout << "-To improve Constitution, please enter Constitution, constitution, Cst or cst\n";
            cout << "-To improve Wisdom, please enter Wisdom, wisdom, Wis or wis\n";
            cout << "-To improve Intelligence, please enter Intelligence, intelligence, Int or int\n";
            cout << "-To improve Dexterity, please enter Dexterity, Dexterity, Dex or dex\n";
            cout << "-To improve Luck, please enter Luck, luck, Lck or lck\n";
            cout << "-We cannot change the Level, class, next Level, charisma, HP and MP with extra points\n";
            choice = ctl.retrieveInput();

             //if user whishes to improve strength
            if(choice == "Strength" || choice == "strength" || choice == "Str" || choice == "str")
            {
                NPC.setStrength(NPC.getStrength()+1);
                ExtraPoints--;
                cout << "Strength: " << NPC.getStrength() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if user whishes to improve Constitution
            else if(choice == "Constitution" || choice == "constitution" || choice == "Cst" || choice == "cst")
            {
                NPC.setConstitution(NPC.getConstitution()+1);
                ExtraPoints--;
                cout << "Constitution: " << NPC.getConstitution() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if user whishes to improve Wisdom
            else if(choice == "Wisdom" || choice == "wisdom" || choice == "Wis" || choice == "wis")
            {
                NPC.setWisdom(NPC.getWisdom()+1);
                ExtraPoints--;
                cout << "Wisdom: " << NPC.getWisdom() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if user whishes to improve Intelligence
            else if(choice == "Intelligence" || choice == "intelligence" || choice == "Int" || choice == "int")
            {
                NPC.setIntelligence(NPC.getIntelligence()+1);
                ExtraPoints--;
                cout << "Intelligence: " << NPC.getIntelligence() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if user whishes to improve Dexterity
            else if(choice == "Dexterity" || choice == "Dexterity" || choice == "Dex" || choice == "dex")
            {
                NPC.setDexterity(NPC.getDexterity()+1);
                ExtraPoints--;
                cout << "Dexterity: " << NPC.getDexterity() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if user whishes to improve Luck
            else if(choice == "Luck" || choice == "luck" || choice == "lck" || choice == "Lck")
            {
                NPC.setLuck(NPC.getLuck()+1);
                ExtraPoints--;
                cout << "Luck: " << NPC.getLuck() << "\n";
                ctl.UpdateStatsEx(NPC, 0);
            }

            //if no specific bonus has been entered then display error and loop again
            else
            {
                cout << "Error, We couldn't take your input/nPlease try Again";
            }
        }
		if (!NPC.getAI())
			ctl.BaseStats(NPC);
    }