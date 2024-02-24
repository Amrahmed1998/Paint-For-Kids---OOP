#ifndef CTriangle_H
#define CTriangle_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;

	int CalcArea() const //Utility Function that Calculate The width of Rectangle
	{
		return 0.5 * abs(Corner1.x * (Corner2.y - Corner3.y) + Corner2.x * (Corner3.y - Corner1.y) + Corner3.x * (Corner1.y - Corner2.y));
	}

public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	CTriangle();
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