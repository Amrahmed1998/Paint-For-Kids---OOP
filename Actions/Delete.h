#ifndef Delete_H
#define Delete_H

#include "Action.h"

class Delete : public Action
{
private:
public:
	Delete(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();
};

#endif