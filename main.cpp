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
#include "Visualisation\\Visualisation.h"
#include<algorithm>
#include<math.h>
#include"Movement.h"
#include<iostream>
#include "World\World.h"
using namespace HAPISPACE;




void HAPI_Main()
{
	HAPI_TControllerData data = HAPI.GetControllerData(0);
	int value = data.analogueButtons[HK_ANALOGUE_LEFT_TRIGGER];
	HAPI_TKeyboardData KeyInput;
	int width{ 800 };
	int height{ 600 };
	int X{ 0 };
	int Y{ 0 };
	int bY{ 0 };
	int bX{ 500 };
	int blit{ 3 };
	int row{0};

	World a;

	a.Run();

	//if (!HAPI.Initialise(width, height, "feeling HAPI"))
	//	return;
	//HAPI.SetShowFPS(true);



	//Visualisation vis(width, height, screen);
	//if (!vis.Create_Sprite("Data\\background.tga", "background", 256, 256))
	//{
	//	HAPI.UserMessage(" Background failed to load", "Error");
	//	return;
	//}
	//if (!vis.Create_Sprite("Data\\alphaThing.tga", "ball", 64, 64))
	//{
	//	HAPI.UserMessage(" Background failed to load", "Error");
	//	return;
	//}
	//if (!vis.Create_Animated("Data\\trump_run.png", "trump", 600, 400, 100, 100, 6,0)) {
	//	return;
	//}
	//if (!vis.Create_Animated("Data\\MeatSmall.png", "food", 128, 160, 32, 32, 4, 1)) {
	//	HAPI.UserMessage("food failed to load", "Error");
	//	return;
	//}

	//while (HAPI.Update())
	//{
	//	data = HAPI.GetControllerData(0);
	//	KeyInput = HAPI.GetKeyboardData();
		//if (blit == 1 || blit == 2)
		//{
		//	X = std::max(0, X);
		//	X = std::min(width - 64, X);
		//	Y = std::max(0, Y);
		//	Y = std::min(height - 64, Y);
		//}

		//vis.Clear_To_Colour(0);


		////drawing sprites
		//if (!vis.Draw_Sprite("background", 0, 0,1,0))
		//{
		//	HAPI.UserMessage("background failed to draw", "error");
		//}
		//if (!vis.Draw_Sprite("ball", 0, 0, 1,0))
		//{
		//	HAPI.UserMessage("ball failed to draw", "error");
		//}
		//if (!vis.Draw_Sprite("trump", trumpMove.X, trumpMove.Y,blit,250))
		//{
		//	HAPI.UserMessage("trump failed to draw", "error");
		//}
		//vis.Draw_Sprite("trump", bX, bY, blit,200);
		//if (!vis.Draw_Sprite("food", foodMove.X, foodMove.Y, blit, 2))
		//{
		//	HAPI.UserMessage("food failed to draw", "error");
		//}
	
}

