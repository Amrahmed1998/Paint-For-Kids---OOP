#ifndef Change_Drawing_Color_H
#define Change_Drawing_Color_H

#include "Action.h"

//Add Drawing Action class
class ChangeDrawingColor : public Action
{
private:
	ActionType Color;
	color DColor;
public:
	ChangeDrawingColor(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	bool GetColor(ActionType color);
};

#endif