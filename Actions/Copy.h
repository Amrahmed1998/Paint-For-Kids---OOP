#ifndef Copy_H
#define Copy_H

#include "Action.h"

class Copy : public Action
{
private:
public:
	Copy(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();
};

#endif