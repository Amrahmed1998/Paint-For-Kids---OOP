#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddLinetAction::AddLinetAction(ApplicationManager* pApp) :Action(pApp)
{}

bool AddLinetAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first Point");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!pIn->InDrawingArea(P1.x, P1.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");

		return false;
	}
	pOut->PrintMessage("New Rectangle: Click at second Point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if (!pIn->InDrawingArea(P2.x, P2.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");

		return false;
	}
	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddLinetAction::Execute()
{
	//This action needs to read some parameters first
	if (ReadActionParameters()) {
		//Create a Line with the parameters read from the user
		CLine* R = new CLine(P1, P2, RectGfxInfo);

		//Add the rectangle to the list of figures
		pManager->AddFigure(R);
	}
}
