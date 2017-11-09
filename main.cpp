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
#include "main.h"
#include<algorithm>
using namespace HAPISPACE;

void HAPI_Main()
{
	int width{ 800 };
	int height{ 600 };
	int X{ 0 };
	int Y{ 0 };
	int blit{ 0 };
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
		return;
	}
	HAPI_TKeyboardData KeyInput;
	HAPI.SetShowFPS(true);
	if (!HAPI.Initialise(width, height, "feeling HAPI"))
		return;
	BYTE *screen = HAPI.GetScreenPointer();
	Visualisation vis(width, height, screen);
	if (!vis.Create_Sprite("Data\\trump_run.png", "sprite", 100,100))
	{
		HAPI.UserMessage(" Sprite failed to load", "Error");
		return;
	}
	if (!vis.Create_Sprite("Data\\background.tga", "background", 256, 256))
	{
		HAPI.UserMessage(" Background failed to load", "Error");
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
		if (blit == 1 || blit == 2)
		{
			X = std::max(0, X);
			X = std::min(width - 64, X);
			Y = std::max(0, Y);
			Y = std::min(height - 64, Y);
		}
		vis.Clear_To_Colour(0);

		if (!vis.Draw_Sprite("background", 0, 0,blit))
		{
			HAPI.UserMessage("background failed to draw", "error");
		}
		if (!vis.Draw_Sprite("sprite", X, Y,blit))
		{
			HAPI.UserMessage("sprite failed to draw", "error");
		}
	}
}

