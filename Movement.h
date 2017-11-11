#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;
class Movement
{
public:
	Movement();
	~Movement();

	void Player_Move(HAPI_TKeyboardData KeyInput);
	void Patrol_Move(int sX,int fX, int sY, int fY, int speed, int patrols);
	int speedcount = 0;
	bool xMet{ false };
	bool yMet{ false };
	int X{ 0 }, Y{ 0 };
	int p{ 0 };
};


