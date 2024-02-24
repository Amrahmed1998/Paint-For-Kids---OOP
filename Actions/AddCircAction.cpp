#include "AddCircAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{}

bool AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at Circle Centre");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!pIn->InDrawingArea(P1.x, P1.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");

		return false;
	}
	pOut->PrintMessage("New Circle: Click at any point on Circumference");

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
void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	if (ReadActionParameters()) {
		//Create a rectangle with the parameters read from the user
		CCircle* R = new CCircle(P1, P2, RectGfxInfo);
		if (R->OutsideInterface()) {
			delete R;
			R = NULL;
			Output* pOut = pManager->GetOutput();
			pOut->PrintMessage("The Clicked point will make the figure to be outside the drawing area");
			return;
		}   
			
		//Add the rectangle to the list of figures
		pManager->AddFigure(R);
	}


}
