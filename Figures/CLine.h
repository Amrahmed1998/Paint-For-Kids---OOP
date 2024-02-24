#ifndef CLine_H
#define CLine_H

#include "CFigure.h"
#include <cmath>

class CLine : public CFigure {
private:

	Point Point1;
	Point Point2;
	int Calclen() const //Utility Function That Calcualte The Length of The Line
	{
		return sqrt(pow((Point1.x - Point2.x), 2) + pow((Point1.y - Point2.y), 2));
	}

public:

	CLine(Point, Point, GfxInfo FigureGfxInfo);
	CLine();
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