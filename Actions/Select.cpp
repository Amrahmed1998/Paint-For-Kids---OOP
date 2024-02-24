#include "Select.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{}

bool Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Select Figure : Click at the figure");

	pIn->GetPointClicked(Clicked.x, Clicked.y);
	if (!pIn->InDrawingArea(Clicked.x, Clicked.y)) {
		pOut->PrintMessage("Invalid Point, Please use the blank area");
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

//Execute the action
void Select::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		CFigure** SList = pManager->GetSelectedFigureList();
		int SFig = pManager->GetSelectedFigCount();
		CFigure* SelectedFigure = pManager->GetFigure(Clicked.x, Clicked.y);
		if (!SelectedFigure) {
			pOut->PrintMessage("Please Select a Figure");
			return;
		}
		if (!SelectedFigure->IsSelected()) {
			pManager->select(SelectedFigure);
			SelectedFigure->PrintInfo(pOut);
			SelectedFigure = NULL;
			return;
		}
		pManager->unselect(SelectedFigure);
		pOut->ClearStatusBar();

	}
}

