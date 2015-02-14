#pragma once
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapEditor.h"
#include "ObservableMap.h"
#include "Observer.h"
#include "MEView.h"
#include "MEModel.h"
#include "MEController.h"
#include "Controller.h"
#include "Builder.h"
#include "FighterBullyConcreteBuilder.h"
#include "FighterNimbleConcreteBuilder.h"
#include "FighterTankConcreteBuilder.h"
#include "Character.h"
#include "Fighter.h"
#include "Archer.h"
#include "Knight.h"
#include "Sorcerer.h"
#include "ItemPouch.h"
#include "IPController.h"
#include <tchar.h>
#include <windows.h>
using namespace std;


int main()
{
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width -100, sf::VideoMode::getDesktopMode().height - 100), "The Legend of Taleb");
	window.setPosition(sf::Vector2i(0,0));
	MEController map = MEController(window);
	sf::Font Font;
	sf::Text text("Begin, Press A", Font);
	sf::Text title("The Legend of Taleb", Font);
	Controller ctl;

	//Background
	sf::Sprite Background;
	sf::Texture texture;
	sf::RectangleShape rectangle(sf::Vector2f(sf::VideoMode::getDesktopMode().width -105, sf::VideoMode::getDesktopMode().height -105));
	rectangle.setPosition(3, 3);
	rectangle.setOutlineColor(sf::Color(218,165,32));
	rectangle.setOutlineThickness(10);
	rectangle.setFillColor(sf::Color(0,0,0,0));
	texture.loadFromFile("fonts/Picture2.jpg");
	Background.setTexture(texture);
    
	//text related
	Font.loadFromFile("fonts/Triforce.ttf");
	text.setCharacterSize(50);
	text.setColor(sf::Color(218,165,32));
	text.setPosition(50,500);
	sf::Text text2("Create a Map, Press Z", Font);
	text2.setCharacterSize(50);
	text2.setColor(sf::Color(218,165,32));
	text2.setPosition(50, 550);
	sf::Text text3("Create a character, Press S", Font);
	text3.setCharacterSize(50);
	text3.setColor(sf::Color(218,165,32));
	text3.setPosition(50,600);
	title.setCharacterSize(75);
	title.setColor(sf::Color(218,165,32));
	title.setPosition(120,75);
	window.draw(Background);
	window.draw(title);
	window.draw(rectangle);
	window.draw(text);
	window.draw(text2);
	window.draw(text3);
	window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				window.clear();
				/*text2.setString("The Map editor has been loaded");
				text.setString("Hello");
				text3.setString("Press any key to continue");*/
				window.draw(Background);
				window.draw(rectangle);
				window.draw(title);
				window.draw(text);
				window.draw(text2);
				window.draw(text3);
				window.display();
				map.launchEditor();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				window.clear();
				/*text.setString("Hello");
				text2.setString("The Game has started");
				text3.setString("Press any key to continue");*/
				window.draw(Background);
				window.draw(rectangle);
				window.draw(title);
				window.draw(text);
				window.draw(text2);
				window.draw(text3);
				window.display();
				Character Object = ctl.CharacterReturn(window);
				if(map.launchSelector())
				{
					map.handleGameplay(Object);
				}
			}
			
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				window.clear();
				ctl.createCharacter(1, window);
				window.display();
			}
			else
			{
				window.clear();
				window.draw(Background);
				window.draw(rectangle);
				window.draw(title);
				window.draw(text);
				window.draw(text2);
				window.draw(text3);
				window.display();
			}
    }
		return 0;
}

