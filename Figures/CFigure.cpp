#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = 0;
	if(UI.ifDEFfill)
		ChngFillClr(UI.FillColor);
}

CFigure::CFigure()
{
	Selected = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

//void SetLastSelected(bool s);	                   //Make The Figure The Last Selected Figure
//bool IsLastSelected() const;

void CFigure::setid(int id)
{
	if (id > 0) {
		ID = id;
		return;
	}
	ID = 1;
}

int CFigure::getid()
{	return ID;	}

bool CFigure::isfilled() {
	return FigGfxInfo.isFilled;
}
void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

