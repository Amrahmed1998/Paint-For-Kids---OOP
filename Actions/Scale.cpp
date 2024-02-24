#include "Scale.h"

#include "..\ApplicationManager.h"
//#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Scale::Scale(ApplicationManager* pApp) :Action(pApp)
{}

bool Scale::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int SFig = pManager->GetSelectedFigCount();
	if (!SFig) {
		pOut->PrintMessage("Please Select a Figure");
		return false;
	}
	pOut->PrintMessage("Resize the selected figures : Please choose a scale");
	SCALE = pIn->GetUserAction();
	if (!GetScale(SCALE)) {
		pOut->PrintMessage("Invalid Point, Please choose a scale");
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

//Execute the action
void Scale::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		CFigure** SelectedFigs = pManager->GetSelectedFigureList();
		int SelectedFigCount = pManager->GetSelectedFigCount();
		if (SelectedFigCount) {
			for (int i = 0; i < SelectedFigCount; i++) {
				SelectedFigs[i]->scale(scale);
				if (SelectedFigs[i]->OutsideInterface()) {
					SelectedFigs[i]->scale(1 / scale);
					pOut->PrintMessage("Some figures were not Resized as they will be out of the drawing area");
					pManager->unselect(SelectedFigs[i]);
					return;
				}
				pManager->unselect(SelectedFigs[i]);
				pOut->ClearDrawArea();
				pOut->PrintMessage("Figures are rescaled");
				return;	
			}
			return;

		}
	}
}

bool Scale::GetScale(ActionType Scale)   //Convert Actiontype to Color
{
	switch (Scale)
	{
	case HALF:
		scale = 0.5;
		return true;

	case TWO:
		scale = 2;
		return true;

	case QUARTER:
		scale = 0.25;
		return true;

	case FOUR:
		scale = 4;
		return true;
	default:
		return false;
	}
}


