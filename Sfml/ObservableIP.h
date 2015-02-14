/*
COMP 345/2 section N - Assignment 2 - Part 3: Item Container Observer
Author: Celina Taing (6784151)
Date: November 4, 2013
*/

#pragma once
#include "Observer.h"

class ObservableIP
{
public:
	virtual void attach(Observer* o){};
	virtual void detach(Observer* o){};
	virtual void notify(){};
	Observer* obs; 
};