#include "World.h"

#include "../Visualisation/Visualisation.h"

World::World()
{
}


World::~World()
{
	delete vis;
}

bool World::LoadLevel()
{
	if (!vis->Create_Animated("Data\\trump_run.png", "trump", 600, 400, 100, 100, 6, 0))
	{
		HAPI.UserMessage("FART", "FART");
		return false;
	}
	return true;
}

void World::Update() 
{
	if (!vis->Draw_Sprite("trump", 20, 20, 2))
	{
		HAPI.UserMessage("GUFF", "GUFF");
		return;
	}
}

void World::Run() 
{
	vis = new Visualisation;
	vis->Init_Vis(800, 600);
	if (LoadLevel())
		while (HAPI.Update()) 
		{
			vis->Clear_To_Colour(0);
			Update();
		}
		
}