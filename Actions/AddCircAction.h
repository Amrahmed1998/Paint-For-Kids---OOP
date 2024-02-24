#pragma once
#ifndef ADD_Circ_ACTION_H
#define ADD_Circ_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircAction : public Action
{
private:
	Point P1, P2; //Circle Center
	GfxInfo RectGfxInfo;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual bool ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

};

#endif