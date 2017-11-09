/*
HAPI Start
----------
This solution contains an already set up HAPI project and this main file

The didestory structure and main files are:

HAPI_Start - contains the Visual Studio solution file (.sln)
HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
HAPI - the didestory with all the HAPI library files
Data - a place to put your data files with a few sample ones provided

Additionally in the top didestory there are two batch files for creating a redistributable Demo folder
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "Visualisation.h"
#include<algorithm>
#include<math.h>
using namespace HAPISPACE;

void HAPI_Main()
{
	int width{ 800 };
	int height{ 600 };
	int X{ 0 };
	int Y{ 0 };
	int bY{ 0 };
	int bX{ 500 };
	int blit{ 0 };
	int row{0};
	// User prompt to deicde on blit function used
	HAPI_UserResponse responseA;
	HAPI_UserResponse responseB;
	HAPI.UserMessage("Do you want to use clipping?", "Clipping ?", HAPI_ButtonType::eButtonTypeYesNoCancel, &responseA);
	if (responseA == HAPI_UserResponse::eUserResponseYes)
	{
		blit = 3;
	}
	if (responseA==HAPI_UserResponse::eUserResponseNo)
	{	
		HAPI.UserMessage("Do you want to use Alpha blending?", "Alpha ?", HAPI_ButtonType::eButtonTypeYesNo, &responseB);
		if (responseB == HAPI_UserResponse::eUserResponseYes)
		{
			blit = 1;
		}
		if (responseB == HAPI_UserResponse::eUserResponseNo)
		{
			blit = 2;	
		}	
	}
	if (responseA == HAPI_UserResponse::eUserResponseCancel)
	{
		blit = 4;
	}
	HAPI_TKeyboardData KeyInput;
	HAPI.SetShowFPS(true);
	if (!HAPI.Initialise(width, height, "feeling HAPI"))
		return;
	BYTE *screen = HAPI.GetScreenPointer();
	Visualisation vis(width, height, screen);
	if (!vis.Create_Sprite("Data\\background.tga", "background", 256, 256))
	{
		HAPI.UserMessage(" Background failed to load", "Error");
		return;
	}
	if (!vis.Create_Sprite("Data\\alphaThing.tga", "ball", 64, 64))
	{
		HAPI.UserMessage(" Background failed to load", "Error");
		return;
	}
	if (!vis.Create_Animated("Data\\trump_run.png", "trump", 600, 400, 100, 100, 6,0)) {
		return;
	}
	if (!vis.Create_Animated("Data\\MeatSmall.png", "food", 128, 160, 32, 32, 4, 1)) {
		HAPI.UserMessage("NO FRUUT N VEJ", "Error");
		return;
	}

	while (HAPI.Update())
	{
		KeyInput = HAPI.GetKeyboardData();

		if (KeyInput.scanCode['W'])
		{
			Y--;
		}
		if (KeyInput.scanCode['A'])
		{
			X--;
		}
		if (KeyInput.scanCode['S'])
		{
			Y++;
		}
		if (KeyInput.scanCode['D'])
		{
			X++;
		}
		if (KeyInput.scanCode['I'])
		{
			bY--;
		}
		if (KeyInput.scanCode['J'])
		{
			bX--;
		}
		if (KeyInput.scanCode['K'])
		{
			bY++;
		}
		if (KeyInput.scanCode['L'])
		{
			bX++;
		}
		if (blit == 1 || blit == 2)
		{
			X = std::max(0, X);
			X = std::min(width - 64, X);
			Y = std::max(0, Y);
			Y = std::min(height - 64, Y);
		}

		vis.Clear_To_Colour(0);

		if (!vis.Draw_Sprite("background", 0, 0,1))
		{
			HAPI.UserMessage("background failed to draw", "error");
		}


			if (!vis.Draw_Sprite("ball", 0, 0, 1))
			{
				HAPI.UserMessage("ball failed to draw", "error");
			}
		if (!vis.Draw_Sprite("trump", X, Y,blit))
		{
			HAPI.UserMessage("trump failed to draw", "error");
		}
		vis.Draw_Sprite("trump", bX, bY, blit);
		if (!vis.Draw_Sprite("food", 300, 300, blit))
		{
			HAPI.UserMessage("food failed to draw", "error");
		}
	}
}

