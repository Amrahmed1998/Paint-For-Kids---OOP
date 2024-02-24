#include "ChangeFillingColor.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeFillingColor::ChangeFillingColor(ApplicationManager* pApp) :Action(pApp)
{}

bool ChangeFillingColor::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Choose Filling Color");

	Color = pIn->GetUserAction();
	if (!GetColor(Color)) {
		pOut->PrintMessage("Invalid Point, Please use the Colors area");

		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

//Execute the action
void ChangeFillingColor::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		int SCount = pManager->GetSelectedFigCount();
		CFigure** SList = pManager->GetSelectedFigureList();

		if (SList[0] != NULL)    //if There was a Selected Figure Change its drawing Color
		{
			for (int i = 0; i < SCount; i++)
				SList[i]->ChngFillClr(DColor);

			pOut->ClearDrawArea();
			pOut->PrintMessage("Figures are Filled");
		}
		
		else                  //else change The default Drawing Colorl
		{
			pOut->SetDefFILL(true);
			pOut->ChangeCrntFillColor(DColor);
			pOut->PrintMessage("Fill Color is changed");
		};
	}
}

bool ChangeFillingColor::GetColor(ActionType C)   //Convert Actiontype to Color
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
