#include "Forward.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ForwardAction::ForwardAction(ApplicationManager* pApp) :Action(pApp)
{}

bool ForwardAction::ReadActionParameters() {
	return true;
}


//Execute the action
void ForwardAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	int SCount = pManager->GetSelectedFigCount();
	CFigure** SList = pManager->GetSelectedFigureList();
	CFigure** TempSList = new CFigure * [SCount];

	for (int i = 0; i < SCount; i++)
	{
		TempSList[i] = SList[i];
	}


	if (SList[0] != NULL)    //if There was a Selected Figure Forward it 
	{
		for (int i = 0; i < SCount; i++)
			pManager->ForwardFigure(TempSList[i]);

		for (int i = 0; i < SCount; i++) {
			pManager->unselect(SList[i]);
		}

		pOut->ClearDrawArea();

		pOut->PrintMessage("");

		delete[] TempSList;
	}

	else
	{
		pOut->PrintMessage("Select Figure at First");
	}
}
