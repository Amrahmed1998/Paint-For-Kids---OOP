#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures
private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	int selectedFigCount;
	CFigure** SelectedFig; //Pointer to the selected figure

	int ClipboradCount;
	CFigure** Clipboard;   //Pointer to the copied/cut figure

	//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	void ClearFigList();


	CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void select(CFigure* Figure);
	void unselect(CFigure* Figure);
	CFigure** GetSelectedFigureList() const;
	int GetSelectedFigCount();
	void ApplicationManager::ClearSelectedFigList();
	
	void AddFigureToClipboard(CFigure* pFig);
	CFigure** GetClipboard() const;
	int GetClipboardCount() const;
	void SetClipboardCount(int count);
	void ClearClipbord();

	void DeleteFigure();
	void RemoveFigureFromFigureList(CFigure* fig);

	void ForwardFigure(CFigure* Fig);
	void BackwardFigure(CFigure* Fig);

	void Saveallfigures(ofstream& OutFile);

	// -- Interface Management Functions
	Input* GetInput() const; //Return pointer to the input
	Output* GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif