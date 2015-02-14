#pragma once
#include "Observer.h"
class ObservableMap{
public:	
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
//private:
	Observer* obs; 
};