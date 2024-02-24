#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3,GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

CTriangle::CTriangle()
{}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a Triangle on the screen	
	pOut->DrawTria(Corner1, Corner2, Corner3,FigGfxInfo, Selected);
}

Point CTriangle::GetMid() const
{
	Point Middle;
	Middle.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Middle.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	return Middle;
}

CFigure* CTriangle::Copy() const
{
	if (Selected) {
		CTriangle* Copiedtri = new CTriangle(*this);
		Copiedtri->SetSelected(false);
		return Copiedtri;
	}
	return NULL;
}
void CTriangle::paste(const Point Clicked, const Point middle)
{
	Corner1.x = Clicked.x - (middle.x - Corner1.x);
	Corner1.y = Clicked.y - (middle.y - Corner1.y);
	Corner2.x = Clicked.x - (middle.x - Corner2.x);
	Corner2.y = Clicked.y - (middle.y - Corner2.y);
	Corner3.x = Clicked.x - (middle.x - Corner3.x);
	Corner3.y = Clicked.y - (middle.y - Corner3.y);
}

bool CTriangle::OutsideInterface()
{
	return !((Corner1.x < UI.width - 10 && Corner2.x < UI.width - 10 && Corner3.x < UI.width - 10)
		&& (Corner1.x > 5 && Corner2.x > 5 && Corner3.x > 5)
		&& (Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight) && Corner3.y < (UI.height - UI.StatusBarHeight))
		&& (Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight && Corner3.y > UI.ToolBarHeight));
}

void CTriangle::scale(double Scale)
{
	Corner2.x = ((Corner2.x - Corner1.x) * Scale) + Corner1.x;
	Corner2.y = ((Corner2.y - Corner1.y) * Scale) + Corner1.y;
	Corner3.x = ((Corner3.x - Corner1.x) * Scale) + Corner1.x;
	Corner3.y = ((Corner3.y - Corner1.y) * Scale) + Corner1.y;
}

void CTriangle::PrintInfo(Output* pOut)
{
	string x = "White";
	if (UI.ifDEFfill)
		x = UI.FillColor.Color2String();

	pOut->PrintMessage("Figure No. " + to_string(ID) +
		" is a Triangle - Corner1 (" + to_string(Corner1.x) + " , " + to_string(Corner1.y)
		+ ") Corner2 (" + to_string(Corner2.x) + " , " + to_string(Corner2.y) + ") Corner3 (" + 
		to_string(Corner3.x) + " , " + to_string(Corner3.y) + ") " +
		 + "Area = " + to_string(CalcArea()) + " Drawing Color is "
		+ FigGfxInfo.DrawClr.Color2String() + " - Filling Color is " + x);
}

void CTriangle::PasteforMirror(const Point Clicked, const Point middle)
{
	Corner1.x += 2 * (Clicked.x - Corner1.x);
	Corner2.x += 2 * (Clicked.x - Corner2.x);
	Corner3.x += 2 * (Clicked.x - Corner3.x);
}

bool CTriangle::Get(int x, int y) const
{
	double denominator = ((Corner2.y - Corner3.y) * (Corner1.x - Corner3.x) + (Corner3.x - Corner2.x) * (Corner1.y - Corner3.y));
	double a = ((Corner2.y - Corner3.y) * (x - Corner3.x) + (Corner3.x - Corner2.x) * (y - Corner3.y)) / denominator;
	double b = ((Corner3.y - Corner1.y) * (x - Corner3.x) + (Corner1.x - Corner3.x) * (y - Corner3.y)) / denominator;
	double c = 1 - a - b;
	return (0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1);
}

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "TRIANGLE  " << getid() << "  " << Corner1.x << "  " << Corner1.y << "  " << Corner2.x << "  " << Corner2.y << "  " << Corner3.x << "  " << Corner3.y << "  ";
	OutFile << FigGfxInfo.DrawClr.Color2String() << "  ";
	
	if (FigGfxInfo.isFilled != false)
		OutFile << FigGfxInfo.FillClr.Color2String() << endl;
	else
		OutFile << "False" << endl;
}

void CTriangle::Load(ifstream& Infile)
{
	int ID, x1, y1, x2, y2, x3, y3;
	string Draw, Fill;
	Infile >> ID >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> Draw >> Fill;
	setid(ID);
	Corner1.x = x1;  Corner1.y = y1;
	Corner2.x = x2;  Corner2.y = y2;
	Corner3.x = x3;  Corner3.y = y3;
	FigGfxInfo.DrawClr.String2Color(Draw);
	if (Fill != "False") {
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr.String2Color(Fill);
	}
	else
		FigGfxInfo.isFilled = false;
}