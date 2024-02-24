#include "Move.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{}

bool Move::ReadActionParameters()
{
	return true;
}

Point Move::GetMidFigure(int count, CFigure** fig)
{
	Point Mid;
	Mid.x = 0; Mid.y = 0;
	for (int i = 0; i < count; i++)
	{
		Mid.x += fig[i]->GetMid().x;
		Mid.y += fig[i]->GetMid().y;
	}
	Mid.x /= count;
	Mid.y /= count;
	return Mid;
}

//Execute the action
void Move::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		CFigure** CopiedFigs = pManager->GetSelectedFigureList();
		int CopiedFigCount = pManager->GetSelectedFigCount();
		if (CopiedFigCount) {
			pOut->PrintMessage("Click in the blank area to move the selected figure/s");
			pIn->GetPointClicked(Clicked.x, Clicked.y);
			if (!pIn->InDrawingArea(Clicked.x, Clicked.y)) {
				pOut->PrintMessage("Invalid Point, Please use the blank area");
				return;
			}
			Point Mid = GetMidFigure(CopiedFigCount, CopiedFigs);
			for (int i = 0; i < CopiedFigCount; i++) {
				NEWFig = CopiedFigs[i]->Copy();
				NEWFig->paste(Clicked, Mid);
				if (NEWFig->OutsideInterface()) {
					delete NEWFig;
					NEWFig = NULL;
					pOut->PrintMessage("Some figures were not moved as they will be out of the drawing area");
					return;
				}
				else
					pManager->AddFigure(NEWFig);
			}
			pManager->DeleteFigure();
			pOut->ClearDrawArea();
			pOut->PrintMessage("Figures are Moved");
			return;
		}
	}
}