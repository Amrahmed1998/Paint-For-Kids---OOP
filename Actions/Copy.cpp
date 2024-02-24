#include "Copy.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Copy::Copy(ApplicationManager* pApp) :Action(pApp)
{}

bool Copy::ReadActionParameters()
{
	return true;
}

//Execute the action
void Copy::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		int Scount = pManager->GetSelectedFigCount();
		CFigure** SList = pManager->GetSelectedFigureList();
		pManager->SetClipboardCount(1);
		if (Scount) {
			pOut->ClearStatusBar();
			pOut->PrintMessage(to_string(pManager->GetSelectedFigCount()) + " Figures are copied to clipboard");
			return;
		}
		else
			pOut->PrintMessage("Please first Select the Figures");

	}
}

