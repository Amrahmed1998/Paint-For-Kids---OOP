#ifndef ADD_Line_ACTION_H
#define ADD_Line_ACTION_H

#include "Action.h"

//Add Line Action class
class AddLinetAction : public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
public:
	AddLinetAction(ApplicationManager* pApp);

	//Reads Line parameters
	virtual bool ReadActionParameters();

	//Add Line to the ApplicationManager
	virtual void Execute();

};

#endif