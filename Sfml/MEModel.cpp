#pragma once
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MEModel.h"
#include <fstream>
#include <vector>
#include "Map.h"
using namespace std;


MEModel::MEModel(){
	 xsize= 0; 
	 ysize=0;
	 startx=1;
	 starty=1;
	 endx=0;
	 endy=0;
	 curx=1;
	 cury=1;
	 isValidMap=true;	
	 
}

void MEModel::initSize(int x, int y){
	xsize=x;
	ysize=y;
}

void MEModel::createTestMap(){	
	mapModel = loadMap("dragons keep");
	notify();
}


void MEModel::createBaseMap( int x, int y){
	endx=x;
	endy=1;
	xsize=x+2;
	ysize=y+2;
	
	mapModel = std::vector< std::vector<std::string> > (xsize, std::vector<std::string>(ysize));



for(int i = 0;i<ysize;i++){
		for(int j = 0;j<xsize;j++){		
			if (i== 0 || j == 0||i== ysize-1 || j == xsize-1){
			mapModel[j][i]= "w";			
			}else{
			mapModel[j][i]= "r";			
			}
		}
		
	}
mapModel[startx][starty]= "e";
mapModel[endx][endy]= "g";
	//displaymap();
	
}

void MEModel::notify(){
	
	obs->update();

}
void MEModel::attach(Observer* o){
	obs=o;
}
void MEModel::detach(Observer* o){

}

void MEModel::displaymap(){//print map representation to console	
		std::cout<<std::endl;
	for(int i = 0;i<ysize;i++){
		for(int j = 0;j<xsize;j++){
			std::cout<< mapModel[j][i];
		}
		
		std::cout<<std::endl;
	}
}

std::string MEModel::getMapCell(int x, int y){
return mapModel[x][y];	
}
bool MEModel::setMapCell(int x, int y, std::string code){
mapModel[x][y] = code;

	notify();
	return isValid();
}

bool MEModel::isValid(){
	
	std::vector< std::vector<std::string> > mapcopy(xsize, std::vector<std::string>(ysize));
	
	mapcopy = mapModel;
	
	isValidMap=validateMap(startx,starty,mapcopy);notify();return isValidMap;}
bool MEModel::validateMap(int posx, int posy,std::vector< std::vector<std::string> >& mapcopy){// verify if map startpoint and end point have clear path
	
	

	//check right
 	if(mapcopy[posx+1][posy]!="w" && mapcopy[posx+1][posy]!="x" ){
		
		if (mapcopy[posx+1][posy]=="g"){//is goal?
			isValidMap = true;
			return true;
		}else{
			mapcopy[posx+1][posy]="x";//spot has been visited
			if (validateMap(posx+1,posy,mapcopy)){
				isValidMap = true;
				return true;
			}

		}

	}

	//check left
	if(mapcopy[posx-1][posy]!="w" && mapcopy[posx-1][posy]!="x" ){

	
		if (mapcopy[posx-1][posy]=="g"){//is goal?
			isValidMap = true;
			return true;
		}else{
			mapcopy[posx-1][posy]="x";//spot has been visited
			if (validateMap(posx-1,posy,mapcopy)){
				isValidMap = true;
				return true;
			}

		}

	}

	//check down
	if(mapcopy[posx][posy+1]!="w" && mapcopy[posx][posy+1]!="x" ){
		
		if (mapcopy[posx][posy+1]=="g"){//is goal?
			isValidMap = true;
			return true;
		}else{
			mapcopy[posx][posy+1]="x";//spot has been visited
			if (validateMap(posx,posy+1,mapcopy)){
				isValidMap = true;
				return true;
			}

		}

	}

	//check up
	if(mapcopy[posx][posy-1]!="w" && mapcopy[posx][posy-1]!="x" ){
		
		if (mapcopy[posx][posy-1]=="g"){//is goal?
			isValidMap = true;
			return true;
		}else{
			mapcopy[posx][posy-1]="x";//spot has been visited
			if (validateMap(posx,posy-1,mapcopy)){
				isValidMap = true;
				return true;
			}

		}

	}

	return false;//square is a dead end
}

std::vector <std::vector <std::string > > MEModel::loadMap(std::string name){//load map from file not needed for asg1
	string line;
	string msg="";
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
					if(line[j]=='e'){
						startx=j;
						starty=i;
					}		
					mapRep[j][i]=line[j];
					
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

//simple setters and getter
int MEModel::getxsize(){return xsize;}
int MEModel::getysize(){return ysize;}
int MEModel::getstartx(){return startx;}
int MEModel::getstarty(){return starty;}
int MEModel::getendx(){return endx;}
int MEModel::getendy(){return endy;}
int MEModel::getcurx(){return curx;}
int MEModel::getcury(){return cury;}
void MEModel::setxsize(int x){xsize=x;notify();}
void MEModel::setysize(int y){ysize=y;notify();}
void MEModel::setstartx(int x){startx=x;notify();}
void MEModel::setstarty(int y){starty=y;notify();}
void MEModel::setendx(int x){endx=x;notify();}
void MEModel::setendy(int y){endy=y;notify();}
void MEModel::setcurx(int x){curx=x;notify();}
void MEModel::setcury(int y){cury=y;notify();}

//map selector

std::vector <std::string > MEModel::getMapNames(){//load map from file not needed for asg1
	string line;
	string msg="";
	ifstream myfile ("mapList.txt");
	std::vector <std::string >  mapList= std::vector <std::string >(1,"");
	if (myfile.is_open())
	{
		int position;
		int width;
		int height;


		while ( getline (myfile,line) ){//scan lines 
			mapList.push_back(line);
				}
		myfile.close();
		mapList.shrink_to_fit();
		
		return mapList;
	}
	else{ 
	cout << "You do not have maps saved, would you like to create one?";
	return mapList;
	}


}

void MEModel::saveMap(std::string name){//load map from file not needed for asg1
	string line;
	string s="qwsdfg";
	ofstream mymaps ("maps.txt",ios::app);
	ofstream myList ("mapList.txt",ios::app);


	static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	
		for (int i = 0; i < 6; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];    }
		name+=s;
		

	if (myList.is_open() )
	{
	if (mymaps.is_open() )
	{
		//TODO
		//if exists regen
		//position = line.find(name);

		


		mymaps<<endl;	
		mymaps<<endl;	
		mymaps<<name;			
		mymaps<<endl;		
		mymaps<<mapModel.size();
		mymaps<<endl;
		mymaps<<mapModel[0].size();
		mymaps<<endl;
		for(int i = 0;i<mapModel[0].size();i++){
			for(int j = 0;j<mapModel.size();j++){					
				mymaps << mapModel[j][i];
				}				
				mymaps << endl;
			}			
		mymaps.close();		
	}

	else{ 
	cout << "You do not have maps saved, would you like to create one?";
	
	}
		myList<<endl;		
		myList<<name;		
		myList.close();		
	}
	else{ 
	cout << "You do not have maps saved, would you like to create one?";
	
	}
}

void MEModel::saveMapArena(Map* arena){//load map from file not needed for asg1
	string line;
	string s="qwsdfg";
	ofstream mymaps ("maps.txt",ios::app);
	ofstream myList ("mapList.txt",ios::app);


	std::vector <std::vector <std::string > > mapDupe=arena->getMap();
		

	if (myList.is_open() )
	{
	if (mymaps.is_open() )
	{
		//TODO
		//if exists regen
		//position = line.find(name);

		


		mymaps<<endl;	
		mymaps<<endl;	
		mymaps<<"Arena";			
		mymaps<<endl;		
		mymaps<<"11";
		mymaps<<endl;
		mymaps<<"11";
		mymaps<<endl;
		for(int i = 0;i<11;i++){
			for(int j = 0;j<11;j++){					
				mymaps << mapDupe[j][i];
				}				
				mymaps << endl;
			}			
		mymaps.close();		
	}

	else{ 
	cout << "You do not have maps saved, would you like to create one?";
	
	}
		myList<<endl;		
		myList<<"Arena";		
		myList.close();		
	}
	else{ 
	cout << "You do not have maps saved, would you like to create one?";
	
	}
}