#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "MapEditor.h"
using namespace std;


/*
int* MapEditor::showFirstScreen(sf::RenderWindow& window){//allows user to decide map size
	int wide = window.getSize().x;
	int deep= window.getSize().y;
	sf::Font font;
	
	if (!font.loadFromFile("map/prstart.ttf"))
	{
		cout<<"why god whyyyyyyy!?";
	}
	sf::Text question;
	sf::Text answerx;
	sf::Text answery;

	question.setFont(font); 
	question.setString("		What size map would you like?\n	  Use arrow keys to change numbers,\n				 then hit return");
	question.setCharacterSize(24); // in pixels, not points! will be useful for scaling?
	question.setColor(sf::Color::Red);
	question.setPosition((0),deep/4);
	question.setStyle(sf::Text::Bold);
	answerx.setFont(font);	
	answerx.setCharacterSize(24); 
	answerx.setColor(sf::Color::Green);
	answerx.setPosition((wide/2)-30,(deep/2) +20);
	answery.setFont(font); 	
	answery.setCharacterSize(24); 
	answery.setColor(sf::Color::White);
	answery.setPosition((wide/2),(deep/2) +20);
	
	
	int size[2];
	size[0]=10;
	size[1]=10;
	bool isDecided= false;	
	int selector=0;
	
	while (window.isOpen() && !isDecided)//window loop
	{
		//EVENT HANDLING
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){//click on close window
				//place  ask to save  here
				window.close();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//move
			{
				if(size[selector]<32){
				size[selector]+=1;
				}

			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//move
			{
				if(size[selector]>2){
				size[selector]-=1;
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				if(selector>0){
				selector-=1;
				answerx.setColor(sf::Color::Green);
				answery.setColor(sf::Color::White);
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{
				if(selector<1){
				selector+=1;
				answerx.setColor(sf::Color::White);
				answery.setColor(sf::Color::Green);
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//accept input
			{
				isDecided= true;
			}			
		}
		
		answerx.setString(std::to_string(size[0]));		
		answery.setString(" x " + std::to_string(size[1]));	

		window.clear(); //clear old pixels
		window.draw(question);
		window.draw(answerx);
		window.draw(answery);
		window.display();
	}
	return size;
}

void MapEditor::edit(int x,int y,sf::RenderWindow& window){
	
	x+=2;
	y+=2;
	int wide = window.getSize().x;
	int deep= window.getSize().y;
	startx= 1;
	starty=1;
	endx=x-2;
	endy= 1;   
	int spaceright;
	int spacedown;

	
	//scale
	if(x<y){
		spaceright = (wide-200)/y;
		spacedown = (deep)/y;
	}else
	{
		spaceright = (wide-200)/x;
		spacedown = (deep)/x;
	}
	float wscale = (float)spaceright/100;
	float dscale = (float)spacedown/100;

	//sfml texture declarations for images
	sf::Texture wall;
	sf::Texture road;
	sf::Texture entry;
	sf::Texture exit;
	sf::Texture chest;
	sf::Texture enemy;
	sf::Texture sidepanel;
	sf::Texture merchant;


	if (!exit.loadFromFile("map/exit.png")||
		!wall.loadFromFile("map/wall.png")||
		!chest.loadFromFile("map/chest.png")||
		!entry.loadFromFile("map/entry.png")||
		!merchant.loadFromFile("map/merchant.png")||
		!sidepanel.loadFromFile("map/panel.png")||
		!enemy.loadFromFile("map/enemy.png")||
		!road.loadFromFile("map/road.png"))
	{

	}

	enemy.setSmooth(true);
	merchant.setSmooth(true);
	wall.setSmooth(true);
	chest.setSmooth(true);
	entry.setSmooth(true);
	exit.setSmooth(true);
	road.setSmooth(true);
	sidepanel.setSmooth(true);


	

	//createmap
	std::vector <std::vector <std::string > > map (x, vector<string>(y));

	// create sprites
	vector< vector<sf::Sprite> > rsprite(x, vector<sf::Sprite>(y));
	vector< vector<sf::Sprite> > tsprite(x, vector<sf::Sprite>(y));
	sf::Sprite inventory;
	sf::Sprite goal;
	sf::Sprite hero;





	// sprite settings
	int moveAcross=0;
	int moveDown=-dscale;
	//create map boarder
	for(int i = 0;i<y;i++){
		for(int j = 0;j<x;j++){
			if (i== 0 || j == 0||i== y-1 || j == x-1){
				tsprite[j][i].setTexture(wall);
				updateModel(false,j,i,"w",map);
				tsprite[j][i].setScale(sf::Vector2f(wscale, wscale));
				tsprite[j][i].setPosition(sf::Vector2f(moveAcross,moveDown ));

			}
			else{		
				rsprite[j][i].setTexture(road);
				updateModel(false,j,i,"r",map);
				rsprite[j][i].setScale(sf::Vector2f(wscale, wscale));
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
	updateModel(false,startx,starty,"e",map);
	updateModel(false,endx,endy,"g",map);
	rsprite[startx][starty].setTexture(entry);
	rsprite[endx][endy].setTexture(exit);
	rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));
	inventory.setTexture(sidepanel);
	inventory.setPosition(sf::Vector2f(1000,0 ));

	//text settings with oldschool letters
	sf::Font font;
	if (!font.loadFromFile("map/prstart.ttf"))
	{
		cout<<"oops i messed up :P";
	}
	sf::Text question;
	string consoletxt ="Press return to validate map" ;
	question.setFont(font); // font is a sf::Font	
	question.setString(consoletxt);
	question.setCharacterSize(24);
	question.setColor(sf::Color::Red);
	question.setPosition(0,0);
	question.setStyle(sf::Text::Bold);

	//gameloop/view
	while (window.isOpen())
	{


		//EVENT HANDLING
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){//click on close window
				//place  ask to save  here
				window.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))//exit editor w/o saving
			{
				//will bring me back to size choice for map, used for testing right now
				displaymap(map,x,y);				
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//exit, save and name map
			{
				//if valid
				isValid= false;
				std::vector <std::vector <std::string > > mapcopy (x, vector<string>(y));
				mapcopy = map;
				updateModel(true,startx,starty,"e",mapcopy);
				
				if(isValid){
					consoletxt ="This is a Valid map" ;
				}else{
					consoletxt ="This map is invalid" ;
				}
				// will ask if done editting and offer to name map and save
			}

			//	HIGHLIGHTING SELECTED TILE
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				if (posx>1){//scale for second part
					rsprite[posx][posy].setColor(sf::Color(255, 255, 255, 255));
					posx-=1;
					rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));
					

				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{
				if (posx<x-2){//scale for second part
					rsprite[posx][posy].setColor(sf::Color(255, 255, 255, 255));
					posx+=1;

					rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));
					
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//move
			{
				if (posy>1){//scale for second part
					rsprite[posx][posy].setColor(sf::Color(255, 255, 255, 255));
					posy-=1;
					rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//move
			{
				if (posy<y-2){//scale for second part
					rsprite[posx][posy].setColor(sf::Color(255, 255, 255, 255));
					posy+=1;
					rsprite[posx][posy].setColor(sf::Color(128, 128, 128, 255));
				}

			}

			// PLACE MAP ELEMENTS
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))//wall done
			{
				if(posy!=endy || posx!=endx){
					if(posy!=starty || posx!=startx) {
						rsprite[posx][posy].setTexture(wall);			
						updateModel(false,posx,posy,"w",map);

					}				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))//Entry done
			{
				//if valid
				if(posy!=endy || posx!=endx){
					rsprite[startx][starty].setTexture(road);
					updateModel(false,startx,starty,"r",map);
					rsprite[posx][posy].setTexture(entry);
					startx = posx;starty = posy;
					updateModel(false,posx,posy,"e",map);
					
				}
				//set map coordinate to reflect change
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))//treasure done
			{
				if(posy!=endy || posx!=endx){
					if(posy!=starty || posx!=startx){
						updateModel(false,posx,posy,"t",map);
						rsprite[posx][posy].setTexture(chest);}
				}		
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))////merchant done
			{
				if(posy!=endy || posx!=endx){
					if(posy!=starty || posx!=startx){
						updateModel(false,posx,posy,"m",map);
						rsprite[posx][posy].setTexture(merchant);}
				}						
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))//Goal done
			{
				//if valid
				if(posy!=starty || posx!=startx){
					rsprite[endx][endy].setTexture(road);
					updateModel(false,endx,endy,"r",map);
					rsprite[posx][posy].setTexture(exit);
					endx = posx;endy = posy;
					updateModel(false,posx,posy,"g",map);
					
				}
				//set map coordinate to reflect change
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))//Opponent done
			{
				if(posy!=endy || posx!=endx){
					if(posy!=starty || posx!=startx){
						updateModel(false,posx,posy,"o",map);
						rsprite[posx][posy].setTexture(enemy);}
				}					
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))//road
			{
				if(posy!=endy || posx!=endx){
					if(posy!=starty || posx!=startx){
						rsprite[posx][posy].setTexture(road);
						updateModel(false,posx,posy,"r",map);}
				}				
			}


		}//End event handling				
				
				question.setString(consoletxt);
		
		//OUTPUT TO WINDOW
		window.clear();//clear old pixels

		//begin draw
		for(int i = 0;i< y;i++){
			for(int j = 0;j< x;j++){
				if (i== 0 || j == 0||i== y-1 || j == x-1){//scale
					window.draw(tsprite[j][i]);
				}else{
					window.draw(rsprite[j][i]);
				}
			}
		}
		window.draw(question);
		window.draw(inventory);
		window.display();
	}


}

bool MapEditor::updateModel(bool mustValidate ,int posx , int posy, std::string code ,std::vector <std::vector <std::string > >& map ){ //update map representation

	if (mustValidate){//check if valid. Thought:make every key validate?stop them from blocking?
		if(isValidMap(posx,posy,map)){
		map[posx][posy]= code;		
		return true;
		}
	}else{
		map[posx][posy]= code;			
		return true;
	}
	isValid=false;
	return false;
}

std::vector <std::vector <std::string > > MapEditor::loadMap(std::string name){//load map from file not needed for asg1
	string line;
	ifstream myfile ("maps.txt");
	if (myfile.is_open())
	{
		int position;
		int width;
		int height;


		while ( getline (myfile,line) ){//scan lines 
			position = line.find(name);
		if (position!= std::string::npos){
			getline (myfile,line);
			width = atoi(line.c_str());
			getline (myfile,line);
			height= atoi(line.c_str());
			getline (myfile,line);
			std::vector <std::vector <std::string > > mapRep (width, vector<string>(height));
			for(int i = 0;i<height;i++){
				for(int j = 0;j<width;j++){
					mapRep[j][i]=line[j];
					cout << mapRep[j][i];
				}
				getline (myfile,line);
				cout << endl;
			}
			return mapRep;
		}
		}
		myfile.close();

	}

	else{ std::vector <std::vector <std::string > > mapRep (0, vector<string>(0));
	cout << "You do not have maps saved, would you like to create one?";
	return mapRep;
	}
}

bool MapEditor::isValidMap(int posx, int posy,std::vector <std::vector <std::string > >& map){// verify if map startpoint and end point have clear path
	
	//check right
	if(map[posx+1][posy]!="w" && map[posx+1][posy]!="x" ){
		
		if (map[posx+1][posy]=="g"){//is goal?
			isValid = true;
			return true;
		}else{
			map[posx+1][posy]="x";//spot has been visited
			if (isValidMap(posx+1,posy,map)){
				isValid = true;
				return true;
			}

		}

	}

	//check left
	if(map[posx-1][posy]!="w" && map[posx-1][posy]!="x" ){

	
		if (map[posx-1][posy]=="g"){//is goal?
			isValid = true;
			return true;
		}else{
			map[posx-1][posy]="x";//spot has been visited
			if (isValidMap(posx-1,posy,map)){
				isValid = true;
				return true;
			}

		}

	}

	//check down
	if(map[posx][posy+1]!="w" && map[posx][posy+1]!="x" ){
		
		if (map[posx][posy+1]=="g"){//is goal?
			isValid = true;
			return true;
		}else{
			map[posx][posy+1]="x";//spot has been visited
			if (isValidMap(posx,posy+1,map)){
				isValid = true;
				return true;
			}

		}

	}

	//check up
	if(map[posx][posy-1]!="w" && map[posx][posy-1]!="x" ){
		
		if (map[posx][posy-1]=="g"){//is goal?
			isValid = true;
			return true;
		}else{
			map[posx][posy-1]="x";//spot has been visited
			if (isValidMap(posx,posy-1,map)){
				isValid = true;
				return true;
			}

		}

	}

	return false;//square is a dead end
}

void MapEditor::displaymap(std::vector <std::vector <std::string > >& map,int x,int y){//print map representation to console

	cout<<endl<<endl;


	for(int i = 0;i<y;i++){
		for(int j = 0;j<x;j++){
			cout<< map[j][i];
		}
		cout<<endl;
	}
}
*/