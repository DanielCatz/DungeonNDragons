#pragma once
#include "Observer.h"
#include "ObservableMap.h"
#include "MEModel.h"
#include <SFML/Graphics.hpp>
class MEView:Observer{
public:
	MEView(MEModel* map,sf::RenderWindow& target);
	int* showFirstScreen();
	void editMap(int x, int y);
	void update();
	void MEView::highlightTile(int x,int y);
	void MEView::dehighlightTile(int x,int y);
	void displaymap(std::vector <std::vector <std::string > >& map,int x,int y);
	
	void changeTile(int x,int y,char code);
	void setInfo(std::string input);
	void setMapSize(int x, int y);
	void  changeXY(int dif, bool xselected);
	bool changePlane(std::string plane);
	void moveUnit(int x,int y,char type);
	void togglePane(bool);
	void setInfoPos(int mode);
private:
	MEModel* modeldata;
	
	//sfml stuff
	sf::Text sfConsole;	
	std::string info;
	std::string answerxString;
	std::string answeryString;
	sf::RenderWindow* window;
	sf::Texture player;
	sf::Texture wall;
	sf::Texture road;
	sf::Texture entry;
	sf::Texture exit;
	sf::Texture chest;
	sf::Texture enemy;
	sf::Texture sidepanel;
	sf::Sprite inventory;
	sf::Texture merchant;
	sf::Font font;	
	sf::Text answerx;
	sf::Text answery;
	std::vector< std::vector<sf::Sprite> >rsprite;
	//sf::Sprite** rsprite;
	bool updateModel(bool mustValidte, int posx , int posy, std::string code ,std::vector <std::vector <std::string > >& map );	
	bool isValidMap(int posx, int posy,std::vector <std::vector <std::string > >& map);
};


	

	
	