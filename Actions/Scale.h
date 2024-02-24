#ifndef Scale_H
#define Scale_H

#include "Action.h"

class Scale : public Action
{
private:
	Point Clicked;
	ActionType SCALE;
	double scale;
public:
	Scale(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	bool GetScale(ActionType Scale);
};

#endif