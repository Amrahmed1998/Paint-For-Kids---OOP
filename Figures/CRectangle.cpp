#include "CRectangle.h"


CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	
CRectangle::CRectangle()
{}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

Point CRectangle::GetMid() const
{
	Point Middle;
	Middle.x = (Corner1.x + Corner2.x) / 2;
	Middle.y = (Corner1.y + Corner2.y) / 2;
	return Middle;
}

CFigure* CRectangle::Copy() const
{
		if (Selected) {
			CRectangle* Copiedrect = new CRectangle(*this);
			Copiedrect->SetSelected(false);
			return Copiedrect;
		}
		return NULL;
}

bool CRectangle::OutsideInterface()
{
	return !((Corner1.x < UI.width && Corner2.x < UI.width)
		&& (Corner1.x > 5 && Corner2.x > 5)
		&& (Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight))
		&& (Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight));
		/*&& (GetMid().y + (CalcLen() / 2) < (UI.height - UI.StatusBarHeight))
		&& (GetMid().y - (CalcLen() / 2) > UI.ToolBarHeight)
		&& (GetMid().x + (CalcWid() / 2) < UI.width - 10)
		&& (GetMid().x - (CalcWid() / 2) > 5));*/ 
}

void CRectangle::scale(double scale)
{
	int NewLen = scale * CalcLen();
	int NewWid = scale * CalcWid();
	Point middle = GetMid();
	Corner1.x = middle.x - NewWid / 2;
	Corner1.y = middle.y - NewLen / 2;
	Corner2.x = middle.x + NewWid / 2;
	Corner2.y = middle.y + NewLen / 2;
}
void CRectangle::PrintInfo(Output* pOut)
{
	string x = "White";
	if (UI.ifDEFfill)
		x = UI.FillColor.Color2String();

	pOut->PrintMessage("Figure No. " + to_string(getid()) +
		" is a Rectangle - Corner1 (" + to_string(Corner1.x) + " , " + to_string(Corner1.y)
		+ ") Corner2 (" + to_string(Corner2.x) + " , " + to_string(Corner2.y) + ") Length = " + 
		to_string(CalcLen()) + " " +
		"Width = " + to_string(CalcWid()) + " Area = " + to_string(CalcArea()) + " Drawing Color is "
		+ FigGfxInfo.DrawClr.Color2String() + " - Filling Color is " + x);
}

void CRectangle::paste(const Point Clicked, const Point middle)
{
	Corner1.x = Clicked.x - (middle.x - Corner1.x);
	Corner1.y = Clicked.y - (middle.y - Corner1.y);
	Corner2.x = Clicked.x - (middle.x - Corner2.x);
	Corner2.y = Clicked.y - (middle.y - Corner2.y);
}

void CRectangle::PasteforMirror(const Point Clicked, const Point middle)
{
	Point NewMiddle;
	NewMiddle.y = middle.y;
	NewMiddle.x = Clicked.x + (Clicked.x - middle.x);
	int w = CalcWid() / 2;
	Corner1.x = NewMiddle.x - w;
	Corner2.x = NewMiddle.x + w;
}

bool CRectangle::Get(int x, int y) const
{
	if (((x >= Corner1.x && x <= Corner2.x) || (x <= Corner1.x && x >= Corner2.x)) &&
		((y >= Corner1.y && y <= Corner2.y) || (y <= Corner1.y && y >= Corner2.y)))
		return true;
	return false;
}

void CRectangle::Save(ofstream& OutFile)
{

	OutFile << "RECTANGLE " << "	" << getid() << "	" << Corner1.x <<
	"	" << Corner1.y << "	" << Corner2.x << "	" << Corner2.y << "	" << FigGfxInfo.DrawClr.Color2String() << "	";
	if (FigGfxInfo.isFilled != false)
		OutFile << FigGfxInfo.FillClr.Color2String() << endl;
	else
		OutFile << "False" << endl;
}

void CRectangle::Load(ifstream& Infile)
{
	int ID, x1, y1, x2, y2;
	string Draw, Fill;
	Infile >> ID >> x1 >> y1 >> x2 >> y2 >> Draw >> Fill;
	setid(ID);
	Corner1.x = x1;  Corner1.y = y1;
	Corner2.x = x2;  Corner2.y = y2;
	FigGfxInfo.DrawClr.String2Color(Draw);
	if (Fill != "False") {
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr.String2Color(Fill);
	}
	else
		FigGfxInfo.isFilled = false;
}