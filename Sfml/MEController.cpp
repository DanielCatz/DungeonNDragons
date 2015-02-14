#pragma once
#include "stdafx.h"
#include "MEController.h"
#include "MEView.h"
#include "MEModel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Fighter.h"
#include "Archer.h"
#include "Knight.h"
#include "Sorcerer.h"
#include "Character.h"
#include "IPController.h"
#include "Map.h"
#include "Contractor.h"
#include "MapBuilder.h"
#include "ArenaMapBuilder.h"
using namespace std;

Controller ctl;
//CONSTRUCTOR
int playerlevel =0;
MEController::MEController(sf::RenderWindow& target){
	model = new MEModel;	
	view = new MEView(model,target);
	window = new sf::RenderWindow();
	window= &target;	
}

//MAP EDITING
bool MEController::launchEditor(){
	view->showFirstScreen();
	view->togglePane(false);
	handleFS();//handle the first screen.
	if (model->getxsize()!=0){
		model->createBaseMap(model->getxsize(),model->getysize());//lauch model
		view->editMap(model->getxsize()-2,model->getysize()-2);//launch view
		handleEdit();// controller takes over and mediates
		return true;
	}else{
		cout<<"go back a screen";
		system("pause");
		return false;
	}
}

void MEController::handleFS(){
	Sleep(1000);
	int valuex = 10;
	int valuey = 10;
	bool isDecided= false;
	bool dimensionx= true;
	while (window->isOpen() && !isDecided)//window loop
	{
		//EVENT HANDLING
		sf::Event event;

		while (window->pollEvent(event))
		{


			if (event.type == sf::Event::Closed){//click on close window

				window->close();
			}



			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//move
			{


				if(dimensionx)	{
					if (valuex<32){
						valuex+=1;					
						view->changeXY(valuex,dimensionx);}}
				else{if (valuey<32){
					valuey+=1;
					view->changeXY(valuey,dimensionx);}}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))//move
			{
				valuex = 0;
				valuey = 0;
				isDecided=true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//move
			{
				if (valuex<2){}

				if(dimensionx)	{
					if (valuex>2){
						valuex-=1;
						view->changeXY(valuex,dimensionx);}}
				else{
					if (valuey>2){
						valuey-=1;
						view->changeXY(valuey,dimensionx);}}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				dimensionx=view->changePlane("l");

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{

				dimensionx=view->changePlane("r");

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//accept input
			{
				isDecided= true;
				break;
			}			
		}

		view->showFirstScreen();


	}

	model->initSize(valuex,valuey);
	valuex = 10;
	valuey = 10;
	view->changeXY(valuex,true);
	view->changeXY(valuey,false);

}  

void MEController::handleEdit(){
	view->togglePane(false);
	view->setInfo("Press 'A' to create an Arena!");
	view->setInfoPos(0);
	view->update();
	Sleep(1000);
	int x = 1;
	int y = 1;
	int i = 0;
	bool isEditing=true;
	vector <string> mapList=model->getMapNames();//select
	while (window->isOpen()&& isEditing)
	{
		//EVENT HANDLING
		sf::Event event;
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed){//click on close window
				//place  ask to save  here
				window->close();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))//exit editor w/o saving
			{
				model->displaymap();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//exit, save and name map in final version
			{

				if(model->isValid()){

					view->setInfo("Map Saved!");
					model->saveMap("map");
					Sleep(1000);
					isEditing=false;
					break;
				}
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))//cycle maps up
			{

				if((i+1)<mapList.size()){
					i++;
					loadRedraw(mapList[i]);
					cout<<i;
				}

			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))//cycle maps down
			{

				if((i)>1){
					i--;
					loadRedraw(mapList[i]);
					cout<<i;
				}


			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))//save
			{
				Contractor archie;
				MapBuilder* mb = new ArenaMapBuilder(playerlevel);
				archie.setMapBuilder(mb);
				archie.constructMap();
				Map* map = archie.getmap();
				model->saveMapArena(map);
				loadRedraw("Arena");
				view->setInfo("Built an Arena");
				view->update();
				Sleep(3000);
				isEditing=false;
			}




			//HIGHLIGHTING SELECTED TILE
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				if (model->getcurx() > 1){//scale for second part


					view->dehighlightTile(model->getcurx(),model->getcury());				
					view->highlightTile(model->getcurx()-1,model->getcury());
					model->setcurx(model->getcurx()-1);	
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{
				if (model->getcurx() < model->getxsize()-2){//scale for second part			

					view->dehighlightTile(model->getcurx(),model->getcury());				
					view->highlightTile(model->getcurx()+1,model->getcury());
					model->setcurx(model->getcurx()+1);
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//move
			{
				if (model->getcury() > 1){//scale for second part							
					view->dehighlightTile(model->getcurx(),model->getcury());				
					view->highlightTile(model->getcurx(),model->getcury()-1);
					model->setcury(model->getcury()-1);	
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//move
			{
				if (model->getcury() < model->getysize()-2){//scale for second part

					view->dehighlightTile(model->getcurx(),model->getcury());				
					view->highlightTile(model->getcurx(),model->getcury()+1);
					model->setcury(model->getcury()+1);

				}

			}

			// PLACE MAP ELEMENTS
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))//wall done
			{
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()) {
						view->changeTile(model->getcurx(),model->getcury(),'w');	

						if(model->setMapCell(model->getcurx(),model->getcury(),"w")){
							view->setInfo ("This is a Valid map") ;
						}else{
							view->setInfo ("This map is invalid" );
						}

					}			
				}

			}



			if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))//treasure done
			{
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()) {
						view->changeTile(model->getcurx(),model->getcury(),'t');			
						if(model->setMapCell(model->getcurx(),model->getcury(),"t")){
							view->setInfo ("This is a Valid map") ;
						}else{
							view->setInfo ("This map is invalid" );
						}

					}			
				}	
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))////merchant done
			{
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()) {
						view->changeTile(model->getcurx(),model->getcury(),'m');
						if(model->setMapCell(model->getcurx(),model->getcury(),"m")){
							view->setInfo ("This is a Valid map") ;
						}else{
							view->setInfo ("This map is invalid" );
						}

					}			
				}						
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))//Entry done
			{
				//if valid
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					view->changeTile(model->getstartx(),model->getstarty(),'r');
					model->setMapCell(model->getstartx(),model->getstarty(),"r");
					//updateModel(false,startx,starty,"r",map);
					view->changeTile(model->getcurx(),model->getcury(),'e');
					if(model->setMapCell(model->getcurx(),model->getcury(),"e")){
						view->setInfo ("This is a Valid map") ;
					}else{
						view->setInfo ("This map is invalid" );
					}
					model->setstartx(model->getcurx());model->setstarty(model->getcury());

				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))//Goal done
			{
				//if valid
				if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()){
					view->changeTile(model->getendx(),model->getendy(),'r');
					model->setMapCell(model->getendx(),model->getendy(),"r");
					//updateModel(false,startx,starty,"r",map);
					view->changeTile(model->getcurx(),model->getcury(),'g');
					if(model->setMapCell(model->getcurx(),model->getcury(),"g")){
						view->setInfo ("This is a Valid map") ;
					}else{
						view->setInfo ("This map is invalid" );
					}
					model->setendx(model->getcurx());model->setendy(model->getcury());


				}
				//set map coordinate to reflect change
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))//Opponent done
			{
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()) {
						view->changeTile(model->getcurx(),model->getcury(),'o');
						if(model->setMapCell(model->getcurx(),model->getcury(),"o")){
							view->setInfo ("This is a Valid map") ;
						}else{
							view->setInfo ("This map is invalid" );
						}

					}			
				}				
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))//road
			{
				if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
					if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()) {
						view->changeTile(model->getcurx(),model->getcury(),'r');	
						if(model->setMapCell(model->getcurx(),model->getcury(),"r")){
							view->setInfo ("This is a Valid map") ;
						}else{
							view->setInfo ("This map is invalid" );
						}

					}			
				}			
			}

		}//End event handling				
	}		
}

//MAP SELECTION
bool MEController::launchSelector(){//will need to return the map
	view->togglePane(true);
	view->setInfoPos(0);
	int i = 1;	
	vector <string> mapList=model->getMapNames();	
	model->createBaseMap(model->getxsize(),model->getysize());//lauch model
	view->editMap(model->getxsize()-2,model->getysize()-2);//launch view
	loadRedraw(mapList[i]);
	view->dehighlightTile(model->getcurx(),model->getcury());
	bool isChoosing = true;
	int x = 1;
	int y = 1;


	while (window->isOpen()&& isChoosing)
	{
		//EVENT HANDLING
		sf::Event event;
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed){//click on close window
				//place  ask to save  here
				window->close();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))//exit editor w/o saving
			{
				return false;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//exit, save and name map in final version
			{
				//set char to entry, break loop, call play
				view->changeTile(model->getstartx(),model->getstarty(),'p');
				model->notify();
				isChoosing=false;

			}

			//HIGHLIGHTING SELECTED TILE
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				if((i)>1){
					i--;
					loadRedraw(mapList[i]);

				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{
				if((i+1)<mapList.size()){
					i++;
					loadRedraw(mapList[i]);

				}
			}


		}//End event handling				

	}
	return true;

}


bool MEController::handleGameplay(Character& player){
	view->togglePane(true);
	view->dehighlightTile(model->getcurx(),model->getcury());
	model->setcurx(model->getstartx());
	model->setcury(model->getstarty());
	Character enemies[10];	
	
	view->setInfo("			Game Start!");
	view->setInfoPos(1);
	int currentHP = player.getHP();
	int i = 0;
	bool found=false;

	// create a directory for this character, if it doesn't exist
	CreateDirectoryA(player.getName().c_str(), NULL);

	while (window->isOpen())
	{
		//EVENT HANDLING
		sf::Event event;
		while (window->pollEvent(event))
		{

			
			if (event.type == sf::Event::Closed){//click on close window
				//place  ask to save  here
				window->close();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))//move
			{
				ctl.loadItems(*window, player);
				view->update();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))//move
			{
				ctl.Display(enemies[0], *window, false);
			}


			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))//
			{
				if (model->getMapCell(model->getcurx()+1,model->getcury())=="o"){//look right 
					//if enemy is not in array

					for(int j = 0;j<10;j++){						
						if (enemies[j].getX() ==model->getcurx()+1 ){
							if (enemies[j].getY() ==model->getcury() ){
								found=true;
								//player
								currentHP-= ((enemies[j].getAttack()-ctl.Dice1d8())*0.5);
								//monster
								enemies[j].setHP(enemies[j].getHP()-player.getAttack()+ctl.Dice1d8());

								if(enemies[j].getHP()<=0){
									view->changeTile(model->getcurx()+1,model->getcury(),'r');
									model->setMapCell(model->getcurx()+1,model->getcury(),"r");

								}
								if(currentHP<0){
									view->changeTile(model->getcurx(),model->getcury(),'r');
									model->setMapCell(model->getcurx(),model->getcury(),"r");
									view->setInfoPos(2);
									view->setInfo("You're dead dude!");
									view->update();									
									Sleep(5000);
									return false;
								}

								view->setInfo(ctl.Display(enemies[j], *window, false));
								cout<<endl<<currentHP;
							}
						}


					}
					if (!found){
						Character op = ctl.generateEnemies(*window, player);
						op.setX(model->getcurx()+1);
						op.setY(model->getcury());
						enemies[i] = op;
						//player
						currentHP-= ((enemies[i].getAttack()-ctl.Dice1d8())*0.5);
						//monster
						enemies[i].setHP(enemies[i].getHP()-player.getAttack()+ctl.Dice1d8());
						view->setInfo(ctl.Display(enemies[i], *window, false));
						i++;

					}
					found=false;
					view->update();

				}
				else if (model->getMapCell(model->getcurx()-1,model->getcury())=="o"){//look left

					for(int j = 0;j<10;j++){						
						if (enemies[j].getX() ==model->getcurx()-1 ){
							if (enemies[j].getY() ==model->getcury() ){
								found=true;
								//player
								currentHP-= ((enemies[j].getAttack()-ctl.Dice1d8())*0.5);
								//monster
								enemies[j].setHP(enemies[j].getHP()-player.getAttack()+ctl.Dice1d8());

								if(enemies[j].getHP()<0){
									view->changeTile(model->getcurx()-1,model->getcury(),'r');
									model->setMapCell(model->getcurx()-1,model->getcury(),"r");

								}
								if(currentHP<0){
									view->changeTile(model->getcurx(),model->getcury(),'r');
									model->setMapCell(model->getcurx(),model->getcury(),"r");
									view->setInfoPos(2);
									view->setInfo("You're dead dude!");
									view->update();									
									Sleep(5000);
									return false;
								}
								view->setInfo(ctl.Display(enemies[j], *window, false));
								cout<<endl<<currentHP;
							}
						}


					}
					if (!found){
						Character op = ctl.generateEnemies(*window, player);
						op.setX(model->getcurx()-1);
						op.setY(model->getcury());
						enemies[i] = op;
						//player
						currentHP-= ((enemies[i].getAttack()-ctl.Dice1d8())*0.5);
						//monster
						enemies[i].setHP(enemies[i].getHP()-player.getAttack()+ctl.Dice1d8());
						view->setInfo(ctl.Display(enemies[i], *window, false));
						i++;
						cout<<endl<<"new monster"<<endl;
					}
					found=false;
					view->update();
				}
				else if (model->getMapCell(model->getcurx(),model->getcury()-1)=="o"){//look up
					for(int j = 0;j<10;j++){						
						if (enemies[j].getX() ==model->getcurx() ){
							if (enemies[j].getY() ==model->getcury()-1 ){
								found=true;
								//player
								currentHP-= ((enemies[j].getAttack()-ctl.Dice1d8())*0.5);
								//monster
								enemies[j].setHP(enemies[j].getHP()-player.getAttack()+ctl.Dice1d8());

								if(enemies[j].getHP()<0){
									view->changeTile(model->getcurx(),model->getcury()-1,'r');
									model->setMapCell(model->getcurx(),model->getcury()-1,"r");

								}
								if(currentHP<0){
									view->changeTile(model->getcurx(),model->getcury(),'r');
									model->setMapCell(model->getcurx(),model->getcury(),"r");
									view->setInfoPos(2);
									view->setInfo("You're dead dude!");
									view->update();									
									Sleep(5000);
									return false;
								}
								view->setInfo(ctl.Display(enemies[j], *window, false));
								cout<<endl<<currentHP;
							}
						}


					}
					if (!found){
						Character op = ctl.generateEnemies(*window, player);
						op.setX(model->getcurx());
						op.setY(model->getcury()-1);
						enemies[i] = op;
						//player
						currentHP-= ((enemies[i].getAttack()-ctl.Dice1d8())*0.5);
						//monster
						enemies[i].setHP(enemies[i].getHP()-player.getAttack()+ctl.Dice1d8());
						view->setInfo(ctl.Display(enemies[i], *window, false));
						i++;
						cout<<endl<<"new monster"<<endl;
					}
					found=false;
					view->update();
				}
				else if (model->getMapCell(model->getcurx(),model->getcury()+1)=="o"){//look down
					for(int j = 0;j<10;j++){						
						if (enemies[j].getX() ==model->getcurx() ){
							if (enemies[j].getY() ==model->getcury()+1){
								found=true;
								//player
								currentHP-= ((enemies[j].getAttack()-ctl.Dice1d8())*0.5);
								//monster
								enemies[j].setHP(enemies[j].getHP()-player.getAttack()+ctl.Dice1d8());

								if(enemies[j].getHP()<0){
									view->changeTile(model->getcurx(),model->getcury()+1,'r');
									model->setMapCell(model->getcurx(),model->getcury()+1,"r");

								}
								if(currentHP<0){
									view->changeTile(model->getcurx(),model->getcury(),'r');
									model->setMapCell(model->getcurx(),model->getcury(),"r");
									view->setInfoPos(2);
									view->setInfo("You're dead dude!");
									view->update();									
									Sleep(5000);
									return false;
								}
								view->setInfo(ctl.Display(enemies[j], *window, false));
								cout<<endl<<currentHP;
							}
						}


					}
					if (!found){
						Character op = ctl.generateEnemies(*window, player);
						op.setX(model->getcurx());
						op.setY(model->getcury()+1);
						enemies[i] = op;
						//player
						currentHP-= ((enemies[i].getAttack()-ctl.Dice1d8())*0.5);
						//monster
						enemies[i].setHP(enemies[i].getHP()-player.getAttack()+ctl.Dice1d8());
						view->setInfo(ctl.Display(enemies[i], *window, false));
						i++;
						cout<<endl<<"new monster"<<endl;

					}
					found=false;
					view->update();
				}
				Sleep(200);
			}




			//HIGHLIGHTING SELECTED TILE
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//move
			{
				if (model->getcurx() > 1){//scale for second part
					if (model->getMapCell(model->getcurx()-1,model->getcury())!="w"&&model->getMapCell(model->getcurx()-1,model->getcury())!="o"){

						if (model->getMapCell(model->getcurx()-1,model->getcury())=="g"){

							ctl.levelUp(player);
							view->setInfo("GOAL!");
							view->update();
							Sleep(1000);
							ctl.Display(player, *window, false);
							ctl.save(player);
							return false;
						}
						if (model->getMapCell(model->getcurx()-1,model->getcury())=="t"){
							IPController chest = IPController(*window, player.getName(), player.getLevel(), model->getcurx(),model->getcury());
							//cout<<endl<<"treasure"<<endl;
						}
						if (model->getMapCell(model->getcurx()-1,model->getcury())=="m"){
							if(currentHP + player.getHP()*0.2 > player.getHP() )
								currentHP = player.getHP();
							else
								currentHP += player.getHP()*0.2;
							cout<<endl<<"merchant"<<endl;
						}

						view->changeTile(model->getcurx(),model->getcury(),'r');
						model->setMapCell(model->getcurx(),model->getcury(),"r");
						model->setcurx(model->getcurx()-1);
						view->changeTile(model->getcurx(),model->getcury(),'p');
						model->setMapCell(model->getcurx(),model->getcury(),"p");
						/*if (model->getMapCell(model->getcurx()-1,model->getcury())=="o"){

						player.displayStats(player, *window);
						cout<<endl<<"monster"<<endl;
						Character Enemy = ctl.generateEnemies(*window, player);
						}*/


					}


				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//move
			{
				if (model->getcurx() < model->getxsize()-2){//scale for second part			

					if (model->getMapCell(model->getcurx()+1,model->getcury())!="w"&&model->getMapCell(model->getcurx()+1,model->getcury())!="o"){

						if (model->getMapCell(model->getcurx()+1,model->getcury())=="g"){

							ctl.levelUp(player);	

							view->setInfo("GOAL!");
							view->update();
							Sleep(1000);

							ctl.Display(player, *window, false);
							ctl.save(player);
							return false;
						}
						if (model->getMapCell(model->getcurx()+1,model->getcury())=="t"){
							IPController chest = IPController(*window, player.getName(), player.getLevel(), model->getcurx(),model->getcury());
							//cout<<endl<<"treasure"<<endl;
						}
						if (model->getMapCell(model->getcurx()+1,model->getcury())=="m"){
							if(currentHP + player.getHP()*0.2 > player.getHP() )
								currentHP = player.getHP();
							else
								currentHP += player.getHP()*0.2;
							cout<<endl<<"merchant"<<endl;
						}



						//move player
						view->changeTile(model->getcurx(),model->getcury(),'r');
						model->setMapCell(model->getcurx(),model->getcury(),"r");
						model->setcurx(model->getcurx()+1);
						view->changeTile(model->getcurx(),model->getcury(),'p');
						model->setMapCell(model->getcurx(),model->getcury(),"p");

						/*if (model->getMapCell(model->getcurx()+1,model->getcury())=="o"){
						player.displayStats(player, *window);
						cout<<endl<<"monster"<<endl;
						Character Enemy = ctl.generateEnemies(*window, player);
						}*/


					}				
				}//if not a wall

			}		


			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//move
			{
				if (model->getcury() > 1){//scale for second part							
					if (model->getMapCell(model->getcurx(),model->getcury()-1)!="w"&&model->getMapCell(model->getcurx(),model->getcury()-1)!="w"){

						if (model->getMapCell(model->getcurx(),model->getcury()-1)=="g"){

							ctl.levelUp(player);

							view->setInfo("GOAL!");
							view->update();
							Sleep(1000);

							ctl.Display(player, *window, false);
							ctl.save(player);
							return false;
						}
						if (model->getMapCell(model->getcurx(),model->getcury()-1)=="t"){
							IPController chest = IPController(*window, player.getName(), player.getLevel(), model->getcurx(),model->getcury());
							//cout<<endl<<"treasure"<<endl;
						}
						if (model->getMapCell(model->getcurx(),model->getcury()-1)=="m"){

							if(currentHP + player.getHP()*0.2 > player.getHP() )
								currentHP = player.getHP();
							else
								currentHP += player.getHP()*0.2;
							cout<<endl<<"merchant"<<endl;
						}

						view->changeTile(model->getcurx(),model->getcury(),'r');
						model->setMapCell(model->getcurx(),model->getcury(),"r");
						model->setcury(model->getcury()-1);
						view->changeTile(model->getcurx(),model->getcury(),'p');
						model->setMapCell(model->getcurx(),model->getcury(),"p");
						/*if (model->getMapCell(model->getcurx(),model->getcury()-1)=="o"){
						player.displayStats(player, *window);
						cout<<endl<<"monster"<<endl;
						Character Enemy = ctl.generateEnemies(*window, player);
						}*/


					}
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//move
			{

				if (model->getcury() < model->getysize()-2){//scale for second part

					if (model->getMapCell(model->getcurx(),model->getcury()+1)!="w"&&model->getMapCell(model->getcurx(),model->getcury()+1)!="o"){

						if (model->getMapCell(model->getcurx(),model->getcury()+1)=="g"){

							ctl.levelUp(player);
							view->setInfo("GOAL!");
							view->update();
							Sleep(1000);

							ctl.Display(player, *window, false);
							ctl.save(player);
							return false;
						}
						if (model->getMapCell(model->getcurx(),model->getcury()+1)=="t"){
							IPController chest = IPController(*window, player.getName(), player.getLevel(), model->getcurx(),model->getcury());
							//cout<<endl<<"treasure"<<endl;
						}
						if (model->getMapCell(model->getcurx(),model->getcury()+1)=="m"){
							if(currentHP + player.getHP()*0.2 > player.getHP() )
								currentHP = player.getHP();
							else
								currentHP += player.getHP()*0.2;
							cout<<endl<<"merchant"<<endl;
						}

						view->changeTile(model->getcurx(),model->getcury(),'r');
						model->setMapCell(model->getcurx(),model->getcury(),"r");
						model->setcury(model->getcury()+1);
						view->changeTile(model->getcurx(),model->getcury(),'p');
						model->setMapCell(model->getcurx(),model->getcury(),"p");
						/*if (model->getMapCell(model->getcurx(),model->getcury()+1)=="o"){
						player.displayStats(player, *window);
						cout<<endl<<"monster"<<endl;
						Character Enemy = ctl.generateEnemies(*window, player);
						}*/				


					}

				}

			}


		}//End event handling				
	}	
	view->setInfoPos(0);
	return false;
}

// GENERAL FUNCTIONS
std::vector <std::vector <std::string > > MEController::loadRedraw(string mapName){


	std::vector <std::vector <std::string > > maploaded;
	maploaded =model->loadMap(mapName);
	view->setMapSize(maploaded.size()-2,maploaded[0].size()-2);
	view->editMap(maploaded.size()-2,maploaded[0].size()-2);
	model->setxsize(maploaded.size()-2);
	model->setysize(maploaded[0].size()-2);

	model->createBaseMap(maploaded.size()-2,maploaded[0].size()-2);

	for(int i = 0;i< maploaded[0].size();i++){
		for(int j = 0;j<maploaded.size();j++){

			if("w"==maploaded[j][i]){
				view->changeTile(j,i,'w');		
				model->setMapCell(j,i,"w");
			}else if("e"==maploaded[j][i]){
				view->changeTile(j,i,'e');
				model->setMapCell(j,i,"e");
				model->setstartx(j);model->setstarty(i);
			}
			else if("o"==maploaded[j][i]){
				view->changeTile(j,i,'o');
				model->setMapCell(j,i,"o");		}
			else if("m"==maploaded[j][i]){
				view->changeTile(j,i,'m');
				model->setMapCell(j,i,"m");		}
			else if("r"==maploaded[j][i]){
				view->changeTile(j,i,'r');	
				model->setMapCell(j,i,"r");}
			else if("g"==maploaded[j][i]){
				view->changeTile(j,i,'g');		
				model->setMapCell(j,i,"g");	
				model->setendx(j);model->setendy(i);}	
			else if("t"==maploaded[j][i]){
				view->changeTile(j,i,'t');
				model->setMapCell(j,i,"t");		}
		}
	}			
	view->setInfo(mapName+" loaded");	
	model->setcurx(1);
	model->setcury(1);
	return maploaded;
}


//TESTING
void MEController::drive(){

	cout<<endl<<"FIRST LETS MOVE TO THE RIGHT "<<endl;
	Sleep( 2000 );
	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	if (model->getcurx() < model->getxsize()-2){//scale for second part			

		view->dehighlightTile(model->getcurx(),model->getcury());				
		view->highlightTile(model->getcurx()+1,model->getcury());
		model->setcurx(model->getcurx()+1);
	}



	Sleep( 2000 );
	cout<<endl<<"THEN WELL MOVE TO THE LEFT "<<endl;
	Sleep( 3000 );
	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	if (model->getcurx() > 1){//scale for second part


		view->dehighlightTile(model->getcurx(),model->getcury());				
		view->highlightTile(model->getcurx()-1,model->getcury());
		model->setcurx(model->getcurx()-1);	
	}

	Sleep( 2000 );
	cout<<endl<<"NOW LETS LOAD A SMALLER MAP "<<endl;
	Sleep( 3000 );
	loadRedraw("dragons keep");

	Sleep( 2000 );
	cout<<endl<<"LETS MOVE THE ENTRY POINT NOW "<<endl;
	Sleep( 3000 );
	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	//if valid
	if(model->getcury()!=model->getendy() || model->getcurx()!=model->getendx()){
		view->changeTile(model->getstartx(),model->getstarty(),'r');
		model->setMapCell(model->getstartx(),model->getstarty(),"r");
		//updateModel(false,startx,starty,"r",map);
		view->changeTile(model->getcurx(),model->getcury(),'e');
		if(model->setMapCell(model->getcurx(),model->getcury(),"e")){
			view->setInfo ("This is a Valid map") ;
		}else{
			view->setInfo ("This map is invalid" );
		}
		model->setstartx(model->getcurx());model->setstarty(model->getcury());

	}

	Sleep( 2000 );
	cout<<endl<<"LETS TRY AND PUT THE GOAL IN PLACE \n OF THE ENTRY"<<endl;
	Sleep( 3000 );

	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	//if valid
	if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()){
		view->changeTile(model->getendx(),model->getendy(),'r');
		model->setMapCell(model->getendx(),model->getendy(),"r");
		//updateModel(false,startx,starty,"r",map);
		view->changeTile(model->getcurx(),model->getcury(),'g');
		if(model->setMapCell(model->getcurx(),model->getcury(),"g")){
			view->setInfo ("This is a Valid map") ;
		}else{
			view->setInfo ("This map is invalid" );
		}
		model->setendx(model->getcurx());model->setendy(model->getcury());


	}

	Sleep( 2000 );
	cout<<endl<<"THAT DIDINT WORK BECAUSE THE ENTRY \n CANNOT BE OVERWRITTEN, SO LETS MOVE OVER "<<endl;
	Sleep( 3000 );

	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	if (model->getcurx() < model->getxsize()-2){//scale for second part			

		view->dehighlightTile(model->getcurx(),model->getcury());				
		view->highlightTile(model->getcurx()+1,model->getcury());
		model->setcurx(model->getcurx()+1);
	}



	Sleep( 2000 );
	cout<<endl<<"THIS LOOKS LIKE A GOOD SPOT FOR THE GOAL "<<endl;
	Sleep( 3000 );

	cout<<"EVENT Detected in Controller"<<endl;
	cout<<"Checking Rules For Appropriate Action"<<endl;
	//if valid
	if(model->getcury()!=model->getstarty() || model->getcurx()!=model->getstartx()){
		view->changeTile(model->getendx(),model->getendy(),'r');
		model->setMapCell(model->getendx(),model->getendy(),"r");
		//updateModel(false,startx,starty,"r",map);
		view->changeTile(model->getcurx(),model->getcury(),'g');
		if(model->setMapCell(model->getcurx(),model->getcury(),"g")){
			view->setInfo ("This is a Valid map") ;
		}else{
			view->setInfo ("This map is invalid" );
		}
		model->setendx(model->getcurx());model->setendy(model->getcury());


	}

	Sleep( 2000 );
	cout<<endl<<"THIS LOOKS A LITTLE EASIER :) "<<endl;
	Sleep( 2000 );
	cout<<endl<<endl<<endl<<endl<<"**------DEMO DONE------** ";

}//deletable 