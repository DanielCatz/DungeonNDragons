#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "MEView.h"
#include "MEModel.h"
using namespace std;


MEView::MEView(MEModel* model, sf::RenderWindow& target){

	model->attach(this);

	window = new sf::RenderWindow();
	window= &target;

	if (!exit.loadFromFile("map/exit.png")||
		!wall.loadFromFile("map/wall.png")||
		!chest.loadFromFile("map/chest.png")||
		!entry.loadFromFile("map/entry.png")||
		!merchant.loadFromFile("map/merchant.png")||
		!sidepanel.loadFromFile("map/panel.png")||
		!enemy.loadFromFile("map/enemy.png")||
		!player.loadFromFile("map/player.png")||
		!road.loadFromFile("map/road.png"))
	{

	}

	enemy.setSmooth(true);
	player.setSmooth(true);
	merchant.setSmooth(true);
	wall.setSmooth(true);
	chest.setSmooth(true);
	entry.setSmooth(true);
	exit.setSmooth(true);
	road.setSmooth(true);
	sidepanel.setSmooth(true);

	inventory.setTexture(sidepanel);
	inventory.setPosition(sf::Vector2f(window->getSize().x-200,0 ));

	answerxString="10";
	answeryString=" x 10";
	answerx.setColor(sf::Color::Green);
	answery.setColor(sf::Color::White);

}

int* MEView::showFirstScreen(){
	float wide = window->getSize().x;
	float deep= window->getSize().y;

	int size[2];
	size[0]=10;
	size[1]=10;

	//load font
	if (!font.loadFromFile("map/prstart.ttf"))
	{
		cout<<"why god whyyyyyyy!?";
	}


	sfConsole.setFont(font); 
	info="		What size map would you like?\n	  Use arrow keys to change numbers,\n				 then hit return";
	sfConsole.setString(info);
	sfConsole.setCharacterSize(24); // in pixels, not points! will be useful for scaling?
	sfConsole.setColor(sf::Color::Red);
	sfConsole.setPosition(window->getSize().x-window->getSize().x*0.8,floor(deep/4));
	sfConsole.setStyle(sf::Text::Bold);
	answerx.setFont(font);	
	answerx.setCharacterSize(24); 

	answerx.setPosition((floor(wide/2))-30,(floor(deep/2)) +20);
	answery.setFont(font); 	
	answery.setCharacterSize(24);

	answery.setPosition((floor(wide/2)),(floor(deep/2)) +20);
	answerx.setString(answerxString);
	answery.setString(answeryString);


	window->clear(); //clear old pixels
	window->draw(sfConsole);
	window->draw(answerx);
	window->draw(answery);
	window->display();
	return size;
}

void MEView::editMap(int x,int y){

	x+=2;
	y+=2;
	float wide = window->getSize().x;
	float deep= window->getSize().y;
	int entryx= 1;
	int entryy=1;
	int exitx=x-2;
	int exity= 1;   
	int spaceright;
	int spacedown;




	float newscale;
	float dewscale;
	newscale= (deep)/(y*80);
	dewscale= (wide- wide*0.10)/(x*101);
	if(dewscale<newscale){
		newscale= dewscale;
	}		 
	spaceright = newscale*101;
	spacedown = newscale*80;

	float wscale = (float)spaceright/100;
	float dscale = (float)spacedown/100;






	rsprite = std::vector< std::vector<sf::Sprite> > (x, std::vector<sf::Sprite>(y));

	/*rsprite = new sf::Sprite*[x];
	for(int i=0; i<x; i++) {
	rsprite[i] = new sf::Sprite[y];}*/



	// sprite settings
	int moveAcross=0;
	int moveDown=-dscale;
	//create map boarder
	for(int i = 0;i<y;i++){
		for(int j = 0;j<x;j++){
			if (i== 0 || j == 0||i== y-1 || j == x-1){
				//ts
				//rsprite[j][i].setTexture(wall);

				rsprite[j][i].setScale(sf::Vector2f(newscale, newscale));
				rsprite[j][i].setPosition(sf::Vector2f(moveAcross,moveDown ));
			}
			else{		
				rsprite[j][i].setTexture(road);				
				rsprite[j][i].setScale(sf::Vector2f(newscale, newscale));
				rsprite[j][i].setPosition(sf::Vector2f(moveAcross,moveDown ));
			}
			moveAcross+=spaceright;
		}

		moveDown+=spacedown;
		moveAcross=0;
	}
	//setup starting point and end point
	int posx = 1;
	int posy= 1;	
	rsprite[entryx][entryy].setTexture(entry);
	rsprite[exitx][exity].setTexture(exit);
	rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));


	//text settings with oldschool letters



	update();




}




bool MEView::updateModel(bool mustValidate ,int posx , int posy, std::string code ,std::vector <std::vector <std::string > >& map ){ //update map representation

	if (mustValidate){//check if valid. Thought:make every key validate?stop them from blocking?
		//if(isValidMap(posx,posy,map))
		{
			map[posx][posy]= code;		
			return true;
		}
	}else{
		map[posx][posy]= code;			
		return true;
	}
	//isValid=false;
	return false;
}



void MEView::highlightTile(int x,int y){
	rsprite[x][y].setColor(sf::Color(128, 128, 128, 255));
}
void MEView::dehighlightTile(int x,int y){
	rsprite[x][y].setColor(sf::Color(255, 255, 255, 255));
}
void MEView::changeTile(int x,int y,char code){
	switch ( code )
	{
	case 'w':
		rsprite[x][y].setTexture(wall);   
		break;
	case 'r':
		rsprite[x][y].setTexture(road);  
		break;
	case 'm':
		rsprite[x][y].setTexture(merchant);   
		break;
	case 't':
		rsprite[x][y].setTexture(chest);   
		break;
	case 'o':
		rsprite[x][y].setTexture(enemy);   
		break;
	case 'g':
		rsprite[x][y].setTexture(exit);   
		break;
	case 'e':
		rsprite[x][y].setTexture(entry);   
		break;
	case 'p':
		rsprite[x][y].setTexture(player);   
		break;

	}
}
void MEView::setInfo(std::string input){info=input;}

void MEView::setInfoPos(int mode){

	if (mode == 1)
		sfConsole.setPosition(window->getSize().x-window->getSize().x*0.3,0);
	else if (mode == 2)
		sfConsole.setPosition(window->getSize().x-window->getSize().x*0.7,window->getSize().y-window->getSize().y*0.5);
	else
		sfConsole.setPosition(0,0);
}



void MEView::update(){


	if (!font.loadFromFile("map/prstart.ttf"))
	{
		cout<<"oops i messed up :P";
	}

	//info ="Press return to validate map" ;
	sfConsole.setFont(font); // font is a sf::Font	
	sfConsole.setString(info);
	sfConsole.setCharacterSize(24);
	
	sfConsole.setColor(sf::Color::Red);	
	sfConsole.setStyle(sf::Text::Bold);	
	sfConsole.setString(info);


	answerx.setFont(font); // font is a sf::Font	
	answerx.setCharacterSize(24);
	answery.setFont(font); // font is a sf::Font	
	answery.setCharacterSize(24);






	//OUTPUT TO WINDOW
	window->clear();//clear old pixels

	//begin draw
	for(int i = 0;i < rsprite[0].size();i++){
		for(int j = 0;j < rsprite.size();j++){				
			window->draw(rsprite[j][i]);				
		}
	}

	window->draw(answery);
	window->draw(answerx);
	window->draw(sfConsole);
	window->draw(inventory);
	window->display();

}
void MEView::setMapSize(int x, int y){
	rsprite = std::vector< std::vector<sf::Sprite> > (x, std::vector<sf::Sprite>(y));

}

//stuff for map size picker

void MEView::changeXY(int dif, bool xselected){

	if (xselected){		
		answerxString=std::to_string(dif);
		answerx.setString(answerxString);		
	}else{		
		answeryString=" x " + std::to_string(dif);
		answery.setString(answeryString);
	}}

bool MEView::changePlane(std::string plane){
	if("l"==plane){

		answerx.setColor(sf::Color::Green);
		answery.setColor(sf::Color::White);
		return true;}
	else if("r"==plane){

		answerx.setColor(sf::Color::White);	
		answery.setColor(sf::Color::Green); 
		return false;
	}

}

void MEView::togglePane(bool status){
	if(status){
			inventory.setScale(0,0);
		answery.setString("");
	answerx.setString("");
	}
	else
		inventory.setScale(1,1);
	

}