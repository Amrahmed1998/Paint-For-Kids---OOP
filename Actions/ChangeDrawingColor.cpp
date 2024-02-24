#include "ChangeDrawingColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeDrawingColor::ChangeDrawingColor(ApplicationManager* pApp) :Action(pApp)
{}

bool ChangeDrawingColor::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Choose Drawing Color");

	Color = pIn->GetUserAction();
	if (!GetColor(Color)) {
		pOut->PrintMessage("Invalid Point, Please use the Colors area");

		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

//Execute the action
void ChangeDrawingColor::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		pOut->ChangeCrntDrawColor(DColor);
	}
}

bool ChangeDrawingColor::GetColor(ActionType C)   //Convert Actiontype to Color
{
	switch (C)
	{
	case CRED:
		DColor = RED;
		return true;
	case CBLUE:
		DColor = BLUE;
		return true;
	case CBLACK:
		DColor = BLACK;
		return true;
	case CWHITE:
		DColor = WHITE;
		return true;
	case CGREEN:
		DColor = GREEN;
		return true;
	case CDARKRED:
		DColor = DARKRED;
		return true;
	case CLIGHTBLUE:
		DColor = LIGHTBLUE;
		return true;
	case CPINK:
		DColor = PINK;
		return true;
	case CORANGE:
		DColor = ORANGE;
		return true;
	case CYELLOW:
		DColor = YELLOW;
		return true;
	default:
		return false;
	}
}
