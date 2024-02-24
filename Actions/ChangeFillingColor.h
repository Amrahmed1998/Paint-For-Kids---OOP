#ifndef Change_Filling_Color_H
#define Change_Filling_Color_H
#include "Action.h"

//Add Drawing Action class
class ChangeFillingColor : public Action
{
private:
	ActionType Color;
	color DColor;
public:
	ChangeFillingColor(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();

	bool GetColor(ActionType color);
};

#endif