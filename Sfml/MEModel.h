#pragma once
#include "stdafx.h"
#include "Observer.h"
#include "ObservableMap.h"
#include <iostream>
#include <vector>
#include "ArenaMapBuilder.h"

class MEModel:ObservableMap{
public:
	//map selectors
	
	std::vector <std::string > getMapNames();

//end select
	MEModel();
	void attach(Observer* o);
	void detach(Observer* o);
	void notify();
	int getxsize();
	int getysize();
	int getstartx();
	int getstarty();
	int getendx();
	int getendy();
	int getcurx();
	int getcury();
	bool isValid();
	void setxsize(int x);
	void setysize(int y);
	void setstartx(int x);
	void setstarty(int y);
	void setendx(int x);
	void setendy(int y);
	void setcurx(int x);
	void setcury(int y);
	void createBaseMap(int x,int y);
	void displaymap();	
	std::string getMapCell(int x, int y);
	bool setMapCell(int x, int y, std::string code);
	void initSize(int x, int y);
	void createTestMap();
	std::vector <std::vector <std::string > > loadMap(std::string name);
void saveMap(std::string name);
void saveMapArena(Map* arena);
private:
	int xsize;
	int ysize;
	int startx;
	int starty;
	int endx;
	int endy;
	int curx;
	int cury;
	bool validateMap(int posx, int posy,std::vector< std::vector<std::string> >& mapcopy);
	std::vector <std::vector <std::string > > mapModel;
	bool isValidMap;
	
};