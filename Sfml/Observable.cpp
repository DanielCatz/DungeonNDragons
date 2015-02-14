#pragma once
#include "stdafx.h"
#include "Observable.h"
#include "stdafx.h"



void Observable::Attach(Observer* o)
{
	//_observers->Insert(_observers->end(), o);
	i.push_back(o);
}

void Observable::Detach(Observer* o)
{
	  //_observers->remove(o);
	for (int a= 0; a< i.size(); a++)
    {
        if (i[a]== o)
        {
            i.erase(i.begin()+a);
            return;
        }
    }
}

void Observable::notify(Observer* o)
{
	//for (i.First(); !i.IsDone(); i.Next())
	//{
		//i.CurrentItem()->Update(this);
	//};
	// set arg to something that helps
	// tell the Observers what happened
    for (int a= 0; a < i.size(); a++)
    {
        i[a]->Update(this);
    }
}

