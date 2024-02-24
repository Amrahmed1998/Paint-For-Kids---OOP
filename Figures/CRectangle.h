#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;

	int CalcLen() const //Utility Function that Calculate The length of Rectangle
	{
		return abs(Corner2.y - Corner1.y);
	}

	int CalcWid() const //Utility Function that Calculate The width of Rectangle
	{
		return abs(Corner2.x - Corner1.x);
	}

	int CalcArea() const //Utility Function that Calculate The width of Rectangle
	{
		return CalcLen() * CalcWid();
	}

public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo);
	CRectangle();
	void Draw(Output* pOut) const;
	virtual CFigure* Copy() const;
	virtual Point GetMid() const;
	virtual void paste(const Point Clicked,const Point middle);
	virtual bool OutsideInterface();
	virtual void scale(double scale);
	virtual void PrintInfo(Output* pOut);
	virtual void PasteforMirror(const Point Clicked, const Point middle);
	virtual bool Get(int x, int y) const;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	//Save the figure parameters to the file
	/*
		//Load the figure parameters to the file
	*/
};

#endif