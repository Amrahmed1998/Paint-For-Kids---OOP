#include "Load.h"

#include "..\ApplicationManager.h"
#include "..\Figures\CLine.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Load::Load(ApplicationManager* pApp) :Action(pApp)
{}

bool Load::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Load : Enter the file name");
	FileName = pIn->GetSrting(pOut);
	pOut->PrintMessage("File Load Successfully");
	return true;
}

//Execute the action
void Load::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	InputFile.open(FileName, ios::in);
	if (!InputFile.is_open()) {
		pOut->PrintMessage("Error opening file for loading.");
		return;
	}
	pOut->ClearDrawArea();
	pManager->ClearFigList();
	pManager->ClearSelectedFigList();
	string Draw, Fill, FigType;
	int Figcount;
	InputFile >> Draw >> Fill >> Figcount;
	color drawingclr = pOut->getCrntDrawColor();
	drawingclr.String2Color(Draw);
	pOut->ChangeCrntDrawColor(drawingclr);
	if (Fill == "FALSE") {
		pOut->SetDefFILL(true);
		color COLOR = WHITE;
		pOut->ChangeCrntFillColor(COLOR);
	}
	else {
		pOut->SetDefFILL(true);
		color Fillingclr = pOut->getCrntFillColor();
		Fillingclr.String2Color(Fill);
		pOut->ChangeCrntFillColor(Fillingclr);
	}
	CFigure* Figure = NULL;
	while (InputFile >> FigType) {
		if (FigType == "LINE")
			Figure = new CLine;
		else if (FigType == "CIRCLE")
			Figure = new CCircle;

		else if (FigType == "RECTANGLE")
			Figure = new CRectangle;

		else if (FigType == "TRIANGLE")
			Figure = new CTriangle;
		
		Figure->Load(InputFile);
		if (Figure->isfilled() == false) {
			Figure->ChngFillClr(WHITE);
		}
		pManager->AddFigure(Figure);
		Figure = NULL;
	}

	InputFile.close();
	pOut->ClearStatusBar();
	pOut->PrintMessage("File is Loaded Successfully");
}

