#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info

	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	//void SetLastSelected(bool s);	                   //Make The Figure The Last Selected Figure
	//bool IsLastSelected() const;	                   //check whether fig is Last selected Figure
	void setid(int id);
	int getid();
	bool isfilled();
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual bool Get(int x, int y) const = 0;
	// lat selected
		
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	/*
	*	//Save the figure parameters to the file
		//Load the figure parameters to the file
	
	*/
	virtual void Draw(Output* pOut) const = 0;		//Draw the figure
	virtual CFigure* Copy() const = 0;
	virtual Point GetMid() const = 0;
	virtual void paste(const Point Clicked, const Point middle) = 0;
	virtual bool OutsideInterface() = 0;
	virtual void scale(double scale) = 0;
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	virtual void PasteforMirror(const Point Clicked, const Point middle) = 0;
	virtual void Save(ofstream& OutFile) = 0;
	virtual void Load(ifstream& Infile) = 0;
};

#endif