#ifndef Select_H
#define Select_H

#include "Action.h"

class Select : public Action
{
private:
	Point Clicked;
public:
	Select(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();
};

#endif