#include "Mirror.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Mirror::Mirror(ApplicationManager* pApp) :Action(pApp)
{}

bool Mirror::ReadActionParameters()
{
	return true;
}

Point Mirror::GetMidFigure(int count, CFigure** fig)
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
void Mirror::Execute()
{
	if (ReadActionParameters()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		CFigure** CopiedFigs = pManager->GetSelectedFigureList();
		int CopiedFigCount = pManager->GetSelectedFigCount();
		if (pManager->GetSelectedFigCount()) {
			pOut->PrintMessage("Click in the blank area to mirror the selected figure/s");
			pIn->GetPointClicked(Clicked.x, Clicked.y);
			if (!pIn->InDrawingArea(Clicked.x, Clicked.y)) {
				pOut->PrintMessage("Invalid Point, Please use the blank area");
				return;
			}
			Point Mid = GetMidFigure(CopiedFigCount, CopiedFigs);
			for (int i = 0; i < CopiedFigCount; i++) {
				NEWFig = CopiedFigs[i]->Copy();
				NEWFig->PasteforMirror(Clicked, CopiedFigs[i]->GetMid());
				if (NEWFig->OutsideInterface()) {
					delete NEWFig;
					NEWFig = NULL;
					pOut->PrintMessage("Some figures were not mirrored as they will be out of the drawing area");
					return;
				}
				else
					pManager->AddFigure(NEWFig);
			}
			pOut->PrintMessage("Figures are Mirrored");
			return;
		}
		pOut->PrintMessage("Please first select figure/s");
	}
}