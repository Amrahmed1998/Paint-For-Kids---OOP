#include "ApplicationManager.h"
#include "Actions/AddRectAction.h"
#include "Actions/AddTriaAction.h"
#include "Actions/AddCircAction.h"
#include "Actions/AddLineAction.h"
#include "Actions/ChangeDrawingColor.h"
#include "Actions/ChangeFillingColor.h"
#include "Actions/Select.h"
#include "Actions/Copy.h"
#include "Actions/Paste.h"
#include "Actions/Delete.h"
#include "Actions/Move.h"
#include "Actions/Scale.h"
#include "Actions/Mirror.h"
#include "Actions/Forward.h"
#include "Actions/Backward.h"
#include "Actions/Save.h"
#include "Actions/Load.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	selectedFigCount = 0;
	ClipboradCount = 0;
	SelectedFig = new CFigure * [MaxFigCount];
	Clipboard = new CFigure * [MaxFigCount];

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++) {
		FigList[i] = NULL;
		SelectedFig[i] = NULL;
		Clipboard[i] = NULL;
	}
		

}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		
		case DRAW_TRI:
			pAct = new AddTriaAction(this);
			break;

		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLinetAction(this);
			break;

		case CHNG_DRAW_CLR:
			pAct = new ChangeDrawingColor(this);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChangeFillingColor(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case PASTE:
			pAct = new Paste(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case MOVE:
			pAct = new Move(this);
			break;

		case SCALE:
			pAct = new Scale(this);
			break;

		case MIRROR:
			pAct = new Mirror(this);
			break;

		case FORWARD:
			pAct = new ForwardAction(this);
			break;

		case BACKWARD:
			pAct = new BackwardAction(this);
			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
	if (FigCount == 1)
		pFig->setid(1);
	else
		pFig->setid(FigCount);
	
}

void ApplicationManager::ClearFigList()
{
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
}

void ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < selectedFigCount; i++) {
		RemoveFigureFromFigureList(SelectedFig[i]);
		SelectedFig[i] = NULL;
	}
	selectedFigCount = 0;
}


void ApplicationManager::RemoveFigureFromFigureList(CFigure* fig)
{
	int ID = fig->getid();
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] == fig) {
			delete FigList[i];
			FigList[i] = FigList[FigCount - 1];
			FigList[i]->setid(ID);
			FigList[FigCount - 1] = NULL;
			FigCount--;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->Get(x, y))
			return FigList[i];
	}
	return NULL;
}
void ApplicationManager::select(CFigure* Figure)
{
	SelectedFig[selectedFigCount] = Figure;
	SelectedFig[selectedFigCount++]->SetSelected(true);
}

void ApplicationManager::unselect(CFigure* Figure)
{
	for (int i = 0; i < selectedFigCount; i++) {
		if (SelectedFig[i] == Figure) {
			SelectedFig[i]->SetSelected(false);
			SelectedFig[i] = SelectedFig[selectedFigCount - 1];
			SelectedFig[selectedFigCount - 1] = NULL;
			selectedFigCount--;
		}
	}
}

void ApplicationManager::ClearSelectedFigList()
{
	
	for (int i = 0; i < selectedFigCount; i++) {
		SelectedFig[i] = NULL;
	}
	selectedFigCount = 0;
}


CFigure** ApplicationManager::GetSelectedFigureList() const
{
	return SelectedFig;
}

int ApplicationManager::GetSelectedFigCount()
{
	return selectedFigCount;
}

void ApplicationManager::AddFigureToClipboard(CFigure* pFig)
{
	if(ClipboradCount < MaxFigCount)
		Clipboard[ClipboradCount++] = pFig;
}

CFigure** ApplicationManager::GetClipboard() const
{
	return Clipboard;
}

void ApplicationManager::ClearClipbord()
{
	for (int i = 0; i < ClipboradCount; i++)
	{
		delete Clipboard[i];
		Clipboard[i] = NULL;
	}
	ClipboradCount = 0;
}

void ApplicationManager::SetClipboardCount(int count)
{
	ClipboradCount = count;
}

int ApplicationManager::GetClipboardCount() const
{
	return ClipboradCount;
}


////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ForwardFigure(CFigure* Fig) {
	bool Flag = false;
	CFigure* Temp = NULL;
	if (Fig != FigList[FigCount - 1])       //Check if The Figure already in Front
	{
		for (int i = 0; i < FigCount - 1; i++) {
			if (Fig == FigList[i]) {
				Flag = true;
				Temp = FigList[i];
			}
			if (Flag) {
				FigList[i] = FigList[i + 1];
			}
		}
		FigList[FigCount - 1] = Temp;
		Temp = NULL;
	}

	//Forward Fgure in the Selected FigList too
	if (Fig != SelectedFig[selectedFigCount - 1])
	{
		for (int i = 0; i < selectedFigCount - 1; i++) {
			if (Fig == SelectedFig[i]) {
				Flag = true;
				Temp = SelectedFig[i];
			}
			if (Flag) {
				SelectedFig[i] = SelectedFig[i + 1];
			}
		}
		SelectedFig[selectedFigCount - 1] = Temp;
		Temp = NULL;
	}
}

void ApplicationManager::BackwardFigure(CFigure* Fig) {
	bool Flag = false;
	CFigure* Temp = NULL;
	if (Fig != FigList[0])      //Check if The Figure already in Back
	{
		for (int i = FigCount - 1; i > 0; i--) {
			if (Fig == FigList[i]) {
				Flag = true;
				Temp = FigList[i];
			}
			if (Flag) {
				FigList[i] = FigList[i - 1];
			}
		}
		FigList[0] = Temp;
		Temp = NULL;
	}

	//Backward Fgure in the Selected FigList too
	if (Fig != SelectedFig[0])
	{
		for (int i = selectedFigCount - 1; i > 0; i--) {
			if (Fig == SelectedFig[i]) {
				Flag = true;
				Temp = SelectedFig[i];
			}
			if (Flag) {
				SelectedFig[i] = SelectedFig[i - 1];
			}
		}
		SelectedFig[0] = Temp;
		Temp = NULL;
	}
}

void ApplicationManager::Saveallfigures(ofstream& OutFile)
{
	OutFile << FigCount << endl;
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
