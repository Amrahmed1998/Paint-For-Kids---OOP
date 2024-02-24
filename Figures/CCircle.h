#ifndef Circle_H
#define Circle_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point Centre;
	Point point_at_Radius;
	int CalcRadius() const // Utility Function that Calculate The radius of a circle
	{
		return sqrt(pow((Centre.x - point_at_Radius.x), 2) + pow((Centre.y - point_at_Radius.y), 2));
	}
	int CalcArea() const //Utility Function that Calculate The area of a circle
	{
		return 3.14 * CalcRadius() * CalcRadius ();
	}

public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	CCircle();
	void Draw(Output* pOut) const;
	virtual CFigure* Copy() const;
	virtual Point GetMid() const;
	virtual void paste(const Point Clicked, const Point middle);
	virtual bool OutsideInterface();
	virtual void scale(double scale);
	virtual void PrintInfo(Output* pOut);
	virtual void PasteforMirror(const Point Clicked, const Point middle);
	virtual bool Get(int x, int y) const;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	/*
		//Save the figure parameters to the file
		//Load the figure parameters to the file
	*/
};

#endif