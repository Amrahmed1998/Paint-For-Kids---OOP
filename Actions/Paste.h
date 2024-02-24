#ifndef Paste_H
#define Paste_H

#include "Action.h"
#include "..\Figures\CFigure.h"
class Paste : public Action
{
private:
	Point Clicked;
	CFigure* NEWFig;
public:
	Paste(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	Point GetMidFigure(int count, CFigure** Fig);
};

#endif