#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Centre = P1;
	point_at_Radius = P2;
}

CCircle::CCircle()
{}

bool CCircle::OutsideInterface()
{
	return !((Centre.x < UI.width - 10 && point_at_Radius.x < UI.width - 10)
		&& (Centre.x > 5 && point_at_Radius.x > 5)
		&& (Centre.y < (UI.height - UI.StatusBarHeight) && point_at_Radius.y < (UI.height - UI.StatusBarHeight))
		&& (Centre.y > UI.ToolBarHeight && point_at_Radius.y > UI.ToolBarHeight)
		&& (Centre.y - CalcRadius() > UI.ToolBarHeight)
		&& (Centre.y + CalcRadius() < (UI.height - UI.StatusBarHeight))
		&& (Centre.x + CalcRadius() < UI.width - 10)
		&& (Centre.x - CalcRadius() > 5));
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a Circle on the screen
	pOut->DrawCirc(Centre, point_at_Radius, FigGfxInfo, Selected);
}

Point CCircle::GetMid() const
{
	return Centre;
}

CFigure* CCircle::Copy() const
{
	if (Selected) {
		CCircle* Copiedcirc = new CCircle(*this);
		Copiedcirc->SetSelected(false);
		return Copiedcirc;
	}
	return NULL;
}
void CCircle::paste(const Point Clicked, const Point middle)
{
	int Radius = CalcRadius();
	Centre.x = Clicked.x - (middle.x - Centre.x);
	Centre.y = Clicked.y - (middle.y - Centre.y);
	point_at_Radius.x = Centre.x + Radius;
	point_at_Radius.y = Centre.y;
}

void CCircle::scale(double Scale)
{
	point_at_Radius.x = Centre.x + Scale * abs(point_at_Radius.x - Centre.x);
	point_at_Radius.y = Centre.y + Scale * abs(point_at_Radius.y - Centre.y);
}
void CCircle::PrintInfo(Output* pOut)
{
	string x = "White";
	if (UI.ifDEFfill)
		x = UI.FillColor.Color2String();

	pOut->PrintMessage("Figure No. " + to_string(CCircle::getid()) +
		" is a Circle - Center (" + to_string(Centre.x) + " , " + to_string(Centre.y)
		+ ") " + "	Radius =  " + to_string(CalcRadius()) + " Drawing Color is "
		+ FigGfxInfo.DrawClr.Color2String() + " - Filling Color is " + x);
}

void CCircle::PasteforMirror(const Point Clicked, const Point middle)
{
	int R = CalcRadius();
	Centre.x = Clicked.x + (Clicked.x - Centre.x);
	point_at_Radius.x = Centre.x + R;
	point_at_Radius.y = Centre.y;
}

bool CCircle::Get(int x, int y) const
{
	int radius = CalcRadius();
	int pDistance = sqrt(pow((Centre.x - x), 2) + pow((Centre.y - y), 2));
	if (pDistance <= radius)
		return true;
	return false;
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "CIRCLE " << "	" << getid() << "	" << Centre.x <<
		"	" << Centre.y << "	" << CalcRadius()  << "	" << FigGfxInfo.DrawClr.Color2String() << "	";
	if (FigGfxInfo.isFilled != false)
		OutFile << FigGfxInfo.FillClr.Color2String() << endl;
	else
		OutFile << "False" << endl;
}

void CCircle::Load(ifstream& Infile)
{
	int ID; 
	int x, y, radius;
	string Draw, Fill;
	Infile >> ID >> x >> y >> radius >> Draw >> Fill;
	setid(ID);
	Centre.x = x;
	Centre.y = y;
	point_at_Radius.x = Centre.x + radius;
	point_at_Radius.y = Centre.y + radius;
	FigGfxInfo.DrawClr.String2Color(Draw);
	if (Fill != "False") {
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr.String2Color(Fill);
	}
	else
		FigGfxInfo.isFilled = false;
}