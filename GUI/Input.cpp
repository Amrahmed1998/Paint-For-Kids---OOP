#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			//int ClickedItemOrder = -1;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			//	ITM_WHITE, ITM_BLACK, ITM_RED, ITM_DARKRED, ITM_YELLOW, ITM_ORANGE, ITM_BLUE, ITM_LIGHTBLUE, ITM_GREEN, ITM_PINK
			// IF Colour clicked 
			if(x >= 4 && x <= 131){
				if (x >= 4 && x <= 27 && y >= 5 && y <= 21)
					return CWHITE;
				if (x >= 30 && x <= 53 && y >= 5 && y <= 21)
					return CRED;
				if (x >= 56 && x <= 79 && y >= 5 && y <= 21)
					return CYELLOW;
				if (x >= 82 && x <= 105 && y >= 5 && y <= 21)
					return CBLUE;
				if (x >= 108 && x <= 131 && y >= 5 && y <= 21)
					return CGREEN;
				if (x >= 4 && x <= 27 && y >= 29 && y <= 50)
					return CBLACK;
				if (x >= 30 && x <= 53 && y >= 29 && y <= 50)
					return CDARKRED;
				if (x >= 56 && x <= 79 && y >= 29 && y <= 50)
					return CORANGE;
				if (x >= 82 && x <= 105 && y >= 29 && y <= 50)
					return CLIGHTBLUE;
				if (x >= 108 && x <= 131 && y >= 29 && y <= 50)
					return CPINK;
			}
			// Color changing
			if (x >= 144 && x <= 250 && y >= 5 && y <= 23)
				return CHNG_DRAW_CLR;
			if (x >= 144 && x <= 250 && y >= 29 && y <= 47)
				return CHNG_FILL_CLR;
			// If a figure selected
			if (x >= 255 && x <= 317 && y >= 5 && y <= 55)
				return DRAW_LINE;
			if (x >= 319 && x <= 380 && y >= 5 && y <= 55)
				return DRAW_RECT;
			if (x >= 382 && x <= 443 && y >= 5 && y <= 55)
				return DRAW_CIRC;
			if (x >= 445 && x <= 506 && y >= 5 && y <= 55)
				return DRAW_TRI;
			// MAke an action
			if (x >= 508 && x <= 569 && y >= 5 && y <= 55)
				return SELECT;
			if (x >= 571 && x <= 632 && y >= 5 && y <= 55)
				return COPY;
			if (x >= 634 && x <= 695 && y >= 5 && y <= 55)
				return PASTE;
			if (x >= 697 && x <= 758 && y >= 5 && y <= 55)
				return MOVE;
			if (x >= 760 && x <= 821 && y >= 5 && y <= 55)
				return MIRROR;
			if (x >= 823 && x <= 884 && y >= 5 && y <= 55)
				return DEL;
			


			// scaling
			if (x >= 885 && x <= 948 && y >= 5 && y <= 55)
				return SCALE;
			if (x >= 950 && x <= 975 && y >= 3 && y <= 28)
				return FOUR;
			if (x >= 950 && x <= 975 && y >= 30 && y <= 55)
				return QUARTER;
			if (x >= 976 && x <= 1000 && y >= 3 && y <= 28)
				return TWO;
			if (x >= 976 && x <= 1000 && y >= 30 && y <= 55)
				return HALF;
			// Drawing order
			if (x >= 1002 && x <= 1093 && y >= 4 && y <= 25)
				return FORWARD;
			if (x >= 1002 && x <= 1093 && y >= 30 && y <= 51)
				return BACKWARD;
			// EXit
			if (x >= 1095 && x <= 1155 && y >= 5 && y <= 55)
				return SAVE;
			if (x >= 1160 && x <= 1220 && y >= 5 && y <= 55)
				return LOAD;

			else {
				return EMPTY;
			}	//A click on empty place in desgin toolbar
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
/////////////////////////////////

bool Input::InDrawingArea(int x, int y)
{
	return ((x < UI.width)
		&& (x > 0)
		&& (y < (UI.height - UI.StatusBarHeight))
		&& (y > UI.ToolBarHeight));
}


Input::~Input()
{
}
