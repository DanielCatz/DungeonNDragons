#include "MEView.h"
#include "MEModel.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Archer.h"
#include "Fighter.h"
#include "Sorcerer.h"
#include "Knight.h"


class MEController{
	public:
	MEController(sf::RenderWindow& target);
	bool launchEditor();
	bool launchSelector();
	void drive();//for proff
	bool handleGameplay(Character& object);
	private:
	
	MEModel* model;
	MEView* view;
	void handleEdit();
	sf::RenderWindow* window;
	void handleFS();
	std::vector <std::vector <std::string > > loadRedraw(std::string mapName);

};