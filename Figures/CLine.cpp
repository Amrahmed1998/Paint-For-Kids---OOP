
#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Point1 = P1;
	Point2 = P2;
}

CLine::CLine()
{}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a rectangle on the screen	
	pOut->DrawLine(Point1, Point2, FigGfxInfo, Selected);
}

CFigure* CLine::Copy() const
{
	if (Selected) {
		CLine* CopiedLine = new CLine(*this);
		CopiedLine->SetSelected(false);
		return CopiedLine;
	}
	return NULL;
}

Point CLine::GetMid() const
{
	Point P;
	P.x = (Point1.x + Point2.x) / 2;
	P.y = (Point1.y + Point2.y) / 2;
	return P;
}

void CLine::paste(const Point Clicked, const Point middle)
{
	Point1.x = Clicked.x - (middle.x - Point1.x);
	Point1.y = Clicked.y - (middle.y - Point1.y);
	Point2.x = Clicked.x - (middle.x - Point2.x);
	Point2.y = Clicked.y - (middle.y - Point2.y);
}

bool CLine::OutsideInterface()
{
	return !((Point1.x < UI.width - 10 && Point2.x < UI.width - 10)
		&& (Point1.x > 5 && Point2.x > 5)
		&& (Point1.y < (UI.height - UI.StatusBarHeight) && Point2.y < (UI.height - UI.StatusBarHeight))
		&& (Point1.y > UI.ToolBarHeight && Point2.y > UI.ToolBarHeight));
}

void CLine::scale(double Scale)
{
	int Midx = (Point1.x + Point2.x) / 2;
	int Midy = (Point1.y + Point2.y) / 2;

	if ((Point1.x >= Point2.x && Point1.y <= Point2.y) || (Point1.x <= Point2.x && Point1.y >= Point2.y))
	{
		Point1.x = Midx + Scale * abs(Point1.x - Midx);
		Point1.y = Midy - Scale * abs(Midy - Point1.y);
		Point2.x = Midx - Scale * abs(Midx - Point2.x);
		Point2.y = Midy + Scale * abs(Point2.y - Midy);
	}
	else if ((Point1.x >= Point2.x && Point1.y >= Point2.y) || (Point1.x <= Point2.x && Point1.y <= Point2.y)) {
		Point1.x = Midx + Scale * abs(Point1.x - Midx);
		Point1.y = Midy + Scale * abs(Point1.y - Midy);
		Point2.x = Midx - Scale * abs(Midx - Point2.x);
		Point2.y = Midy - Scale * abs(Midy - Point2.y);
	}
}

void CLine::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Figure No. " + to_string(ID) +
		" is a Line - Point1 (" + to_string(Point1.x) + " , " + to_string(Point1.y)
		+ ") Point2 (" + to_string(Point2.x) + " , " + to_string(Point2.y) + ") Length= " +
		to_string(Calclen()) + " Drawing Color is " + FigGfxInfo.DrawClr.Color2String());
}

void CLine::PasteforMirror(const Point Clicked, const Point middle)
{
	Point1.x += 2*(Clicked.x - Point1.x);
	Point2.x += 2 * (Clicked.x - Point2.x);
}

bool CLine::Get(int x, int y) const
{
	if ((Point2.x - Point1.x) == 0) {
		if (Point1.y > Point2.y)
			return (Point2.x == x && y > Point2.y && y < Point1.y);
		if (Point1.y < Point2.y)
			return ((Point2.x >= x - 1 && Point2.x <= x + 1) && y > Point1.y && y < Point2.y);
	}

	if ((Point2.y - Point1.y) == 0) {
		if (Point1.x > Point2.x)
			return (Point2.y == y && x > Point2.x && x < Point1.x);
		if (Point1.x < Point2.x)
			return ((Point2.y >= y - 1 && Point2.y <= y + 1) && x > Point1.x && x < Point2.x);
	}

	double VectorAPx = x - Point1.x;
	double VectorAPy = y - Point1.y;
	double VectorABx = Point2.x - Point1.x;
	double VectorABy = Point2.y - Point1.y;
	double MagAB2 = VectorABx * VectorABx + VectorABy * VectorABy;
	double ABdotAP = VectorABx * VectorAPx + VectorABy * VectorAPy;
	double t = ABdotAP / MagAB2;

	Point Closest;
	if (t < 0)
	{
		Closest.x = Point1.x;
		Closest.y = Point1.y;
	}
	else if (t > 1)
	{
		Closest.x = Point2.x;
		Closest.y = Point2.y;
	}
	else
	{
		Closest.x = Point1.x + VectorABx * t;
		Closest.y = Point1.y + VectorABy * t;
	}

	//The Distance Between The Closest Point To The Give Point 
	int Distance = sqrt(pow((Closest.x - x), 2) + pow((y - y), 2));

	if (Point1.x > Point2.x && Point1.y > Point2.y)
		return(Distance < 3 && x <Point1.x && x >Point2.x && y <Point1.y && y>Point2.y);

	if (Point1.x < Point2.x && Point1.y > Point2.y)
		return(Distance < 3 && x >Point1.x && x < Point2.x && y <Point1.y && y>Point2.y);

	if (Point1.x > Point2.x && Point1.y < Point2.y)
		return(Distance < 3 && x <Point1.x && x >Point2.x && y >Point1.y && y < Point2.y);

	if (Point1.x < Point2.x && Point1.y < Point2.y)
		return(Distance < 3 && x >Point1.x && x <Point2.x && y >Point1.y && y < Point2.y);

}

void CLine::Save(ofstream& OutFile)
{
	OutFile << "Line " << "	" << getid() << "	" << Point1.x <<
		"	" << Point1.y << "	" << Point2.x << "	" << Point2.y << "	" << FigGfxInfo.DrawClr.Color2String() 
		<< "	" << endl;
}

void CLine::Load(ifstream& Infile)
{
	int ID, x1, y1, x2, y2;
	string Draw;
	Infile >> ID >> x1 >> y1 >> x2 >> y2 >> Draw;
	setid(ID);
	Point1.x = x1;  Point1.y = y1;
	Point1.x = x2;  Point1.y = y2;
	FigGfxInfo.DrawClr.String2Color(Draw);
}