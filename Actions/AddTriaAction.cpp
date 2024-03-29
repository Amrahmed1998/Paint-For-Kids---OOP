#include "AddTriaAction.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriaAction::AddTriaAction(ApplicationManager* pApp) :Action(pApp)
{}

bool AddTriaAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!pIn->InDrawingArea(P1.x, P1.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");

		return false;
	}
	pOut->PrintMessage("New Triangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if (!pIn->InDrawingArea(P2.x, P2.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");

		return false;
	}
	pOut->PrintMessage("New Triangle: Click at Third corner");

	//Read 3rd corner and store in point P2
	pIn->GetPointClicked(P3.x, P3.y);
	if (!pIn->InDrawingArea(P3.x, P3.y)) {
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
void AddTriaAction::Execute()
{
	//This action needs to read some parameters first
	if(ReadActionParameters()){
		//Create a Triangle with the parameters read from the user
		CTriangle* R = new CTriangle(P1, P2, P3, RectGfxInfo);

		//Add the Triangle to the list of figures
		pManager->AddFigure(R);
	}

	
}
