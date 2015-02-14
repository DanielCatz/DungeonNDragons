#pragma once
#include <list>
#include <vector>
#include "Controller.h"
#include "Observer.h"

class Observable
{
public:
	Observable(void);
	~Observable(void);
	void Observable::notify(Observer* o);
	void Observable::Attach(Observer* o);
	void Observable::Detach(Observer* o);
	vector <Observer*>i;
};

