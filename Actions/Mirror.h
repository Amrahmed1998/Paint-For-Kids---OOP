#ifndef Mirror_H
#define Mirror_H

#include "Action.h"
#include "..\Figures\CFigure.h"
class Mirror : public Action
{
private:
	Point Clicked;
	CFigure* NEWFig;
public:
	Mirror(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	Point GetMidFigure(int count, CFigure** Fig);
};

#endif