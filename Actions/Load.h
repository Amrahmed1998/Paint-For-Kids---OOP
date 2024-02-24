#ifndef Load_H
#define Load_H

#include "Action.h"

class Load : public Action
{
private:
	ifstream InputFile;
	string FileName;

public:
	Load(ApplicationManager* pApp);

	//Reads parameters
	virtual bool ReadActionParameters();

	//Change color to the ApplicationManager
	virtual void Execute();
};

#endif
