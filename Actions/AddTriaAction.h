#ifndef ADD_Tria_ACTION_H
#define ADD_Tria_ACTION_H

#include "Action.h"

//Add Triangle Action class
class AddTriaAction : public Action
{
private:
	Point P1, P2, P3; //Triangle Corners
	GfxInfo RectGfxInfo;
public:
	AddTriaAction(ApplicationManager* pApp);

	//Reads Triangle parameters
	virtual bool ReadActionParameters();

	//Add Triangle to the ApplicationManager
	virtual void Execute();

};

#endif