#ifndef Move_H
#define Move_H

#include "Action.h"
#include "..\Figures\CFigure.h"
class Move : public Action
{
private:
	Point Clicked;
	CFigure* NEWFig;
public:
	Move(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	Point GetMidFigure(int count, CFigure** Fig);
};

#endif