#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1240;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;

	
	UI.StatusBarHeight = 60;
	UI.ToolBarHeight = 56;
	UI.MenuItemWidth = 63;
	
	UI.DrawColor = BLACK;	//Drawing color
	UI.FillColor = WHITE;	//Filling color
	UI.MsgColor = BLACK;		//Messages color
	UI.BkGrndColor = WHITE;	//Background color
	UI.HighlightColor = RED;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = DARKMAGENTA;
	UI.PenWidth = 2;	//width of the figures frames
	UI.ifDEFfill = false;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("OOP Project - Paint for Kids - D I E S E L");
	CreateDrawToolBar();
	CreateStatusBar();
}

Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);

	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	string BACKGround = "images\\MenuItems\\Untitled-1.jpg";
	pW->DrawImage(BACKGround, 0, UI.ToolBarHeight, w, h - UI.ToolBarHeight - UI.StatusBarHeight);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_WHITE] = "images\\MenuItems\\white.jpg";		//4
	MenuItemImages[ITM_BLACK] = "images\\MenuItems\\Black.jpg";		//6
	MenuItemImages[ITM_BLUE] = "images\\MenuItems\\Blue.jpg";		//2
	MenuItemImages[ITM_LIGHTBLUE] = "images\\MenuItems\\Light_BLue.jpg";
	MenuItemImages[ITM_RED] = "images\\MenuItems\\Red.jpg";			//1
	MenuItemImages[ITM_DARKRED] = "images\\MenuItems\\Nbiti.jpg";	//10
	MenuItemImages[ITM_YELLOW] = "images\\MenuItems\\Yellow.jpg";	//7
	MenuItemImages[ITM_ORANGE] = "images\\MenuItems\\Orange.jpg";	//8
	MenuItemImages[ITM_GREEN] = "images\\MenuItems\\Green.jpg";		//3
	MenuItemImages[ITM_PINK] = "images\\MenuItems\\Pink.jpg";		//9
	MenuItemImages[ITM_DCol] = "images\\MenuItems\\Drawing_color.jpg";
	MenuItemImages[ITM_FCol] = "images\\MenuItems\\Filling_color.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Line.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Circle.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\Triangle.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Select.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\Copy.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\Paste.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\Cut.jpg";
	MenuItemImages[ITM_MIRROR] = "images\\MenuItems\\Mirror.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[ITM_SCALE] = "images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_FOUR] = "images\\MenuItems\\Four.jpg";
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\Quarter.jpg";
	MenuItemImages[ITM_TWO] = "images\\MenuItems\\Two.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\Half.jpg";
	MenuItemImages[ITM_ToFront] = "images\\MenuItems\\Forward.jpg";
	MenuItemImages[ITM_ToBACK] = "images\\MenuItems\\Backward.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Load.jpg";
	//MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	int j = 0;
	for (int i = 0; i < 10; i++) {
		pWind->DrawImage(MenuItemImages[i++], 4 + j * 26, 5, 23, 21);
		pWind->DrawImage(MenuItemImages[i],  4+ j++ * 26, 29, 23, 21); // 4 - 27 + 4 * 4 + 4 * 23
	}
	pWind->DrawImage(MenuItemImages[10], 143, 7, 107, 18);
	pWind->DrawImage(MenuItemImages[11], 143, 31, 107, 18);
	j = 0;
	for(int i = 12; i <= 21; i++)
		pWind->DrawImage(MenuItemImages[i], 255 + j++ * UI.MenuItemWidth, 5, UI.MenuItemWidth, 50);

	pWind->DrawImage(MenuItemImages[22], 885, 5, UI.MenuItemWidth, 50);
	j = 0; 
	for (int i = 23; i < 27; i++) {
			pWind->DrawImage(MenuItemImages[i++], 950 + (j * 25), 7, 25, 25);
			pWind->DrawImage(MenuItemImages[i], 950 + (j++ * 25), 31, 25, 25);
	}
	pWind->DrawImage(MenuItemImages[27], 1001, 4, 91, 21);
	pWind->DrawImage(MenuItemImages[28], 1001, 30, 91, 21);
	pWind->DrawImage(MenuItemImages[29], 1095, 5, UI.MenuItemWidth, 50);
	pWind->DrawImage(MenuItemImages[30], 1160, 5, UI.MenuItemWidth, 50);
	//pWind->DrawImage(MenuItemImages[31], 1385 + UI.MenuItemWidth, 5, UI.MenuItemWidth, 50);
	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

/*void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}*/
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 2);
	pWind->SetBrush(UI.BkGrndColor);
	string BACKGround = "images\\MenuItems\\Untitled-1.jpg";
	pWind->DrawImage(BACKGround, 0, UI.ToolBarHeight + 1, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.25), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//
void Output::SetDefFILL(bool c)
{
	UI.ifDEFfill = c;
}

bool Output::getDefFILL()
{
	return UI.ifDEFfill;
}

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, UI.PenWidth);
	if (UI.ifDEFfill)
		RectGfxInfo.isFilled = true;
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawCirc(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (UI.ifDEFfill)
		CircleGfxInfo.isFilled = true;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	float Radius = 0.0;
	Radius = sqrt((pow(P1.x - P2.x, 2)) + (pow(P1.y - P2.y, 2)));
	pWind->DrawCircle(P1.x, P1.y, Radius, style);
}

void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, FRAME);

}

void Output::DrawTria(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (UI.ifDEFfill)
		TriGfxInfo.isFilled = true;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}

void Output::ChangeCrntDrawColor(color C)
{
	UI.DrawColor = C;
}


void Output::ChangeCrntFillColor(color C)
{
	UI.ifDEFfill = true;
	UI.FillColor = C;
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

