#include "ApplicationManager.h"


int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	AppManager.GetOutput()->PrintMessage("Welcome to \(Paint For Kids\)");

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);
	

	system("pause");
	return 0;
}

