#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "ObservableMap.h"
#include "Observer.h"
#include <list>
using namespace std;





void ObservableMap::attach(Observer* o){
	
	cout<<"attached"<<endl;
}
void ObservableMap::detach(Observer* o){
}

void ObservableMap::notify(){
		//me->update();
		cout<<"pie"<<endl;
		system("Pause");
}
	  

