#ifndef Save_H
#define Save_H

#include "Action.h"

class Save : public Action
{
private:
	ofstream OutputFile;
	string FileName;

public:
	Save(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();
};

#endif

// if file is not open  //open