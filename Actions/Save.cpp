#include "Save.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Save::Save(ApplicationManager* pApp) :Action(pApp)
{}

bool Save::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Save : Enter the file name");
	FileName = pIn->GetSrting(pOut);
	pOut->PrintMessage("File Saved Successfully at the program location folder");
	return true;
}

//Execute the action
void Save::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	OutputFile.open(FileName, ios::out);
	OutputFile << pOut->getCrntDrawColor().Color2String() << "	";
	if (pOut->getDefFILL())
			OutputFile << pOut->getCrntFillColor().Color2String() << endl;
	else
			OutputFile << "FALSE" << endl;

	pManager->Saveallfigures(OutputFile);
	OutputFile.close(); 
}

