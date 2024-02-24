#include "Delete.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{}

bool Delete::ReadActionParameters()
{
	return true;
}

//Execute the action
void Delete::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		int Scount = pManager->GetSelectedFigCount();
		if (Scount) {
			pManager->DeleteFigure();
			pOut->ClearDrawArea();
			pOut->PrintMessage("Selected Figures are Deleted");
			return;
		}
		else
			pOut->PrintMessage("Please Select Figures to be deleted");

	}
}

