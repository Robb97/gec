#include "Movement.h"
#include <HAPI_lib.h>
using namespace HAPISPACE;

Movement::Movement() {}

Movement::~Movement()
{
}
void Movement::Player_Move(HAPI_TKeyboardData KeyInput)
{

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
}
void Movement::Patrol_Move(int sX, int fX, int sY, int fY, int speed, int patrols)
{ 
	if (p != patrols)
	{
		if (X < fX && speedcount == speed && !xMet)
		{
			X++;
			speedcount = 0;
			if (X == fX) { xMet = true; speedcount = 0; }
		}
		if (Y < fY && speedcount == speed && !yMet)
		{
			Y++;
			speedcount = 0;
			if (Y == fY) { yMet = true; speedcount = 0; }
		}
		if (X > sX && speedcount == speed && xMet)
		{
			X--;
			speedcount = 0;
			if (X == sX) { speedcount = 0; }
		}
		if (Y > sY && speedcount == speed && yMet)
		{
			Y--;
			speedcount = 0;
			if (Y == sY) { yMet = false; xMet = false; speedcount = 0; }
		}

		else
		{
			speedcount++;
		}
		p++;
	}
}