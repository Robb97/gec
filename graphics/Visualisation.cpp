#include "Visualisation.h"
#include "Sprite.h"
#include <algorithm>
#include <cassert>


Visualisation::Visualisation() :
	screenStart(nullptr), screenRectangle(nullptr)
{
	screenRectangle = new Helper::Rectangle(0, 0);
}

Visualisation::~Visualisation()
{
	delete screenRectangle;
	for (auto p : spriteMap) 
	{
		delete p.second;
	}
}

void Visualisation::Init_Vis(int wWidth, int wHeight)
{
	if (!HAPI.Initialise(wWidth, wHeight, "HapiTime"))
	{
		return;
	}
	Width = wWidth;
	Height = wHeight;
	screenStart = HAPI.GetScreenPointer();
	screenRectangle->Set_Height(wHeight);
	screenRectangle->Set_Width(wWidth);
}

bool Visualisation::Clear_To_Colour(int grey)
{
	memset(screenStart, grey, (Width * Height * 4));
	return true;
}

bool Visualisation::Clear_To_Colour(int r, int g, int b)
{
	BYTE *screenPntr = screenStart;
	for (int h{ 0 }; h < Height; h++) 
	{
		for (int w{ 0 }; w < Width; w++)
		{
			screenPntr[0] = r;
			screenPntr[1] = g;
			screenPntr[2] = b;
			screenPntr += sizeof(BYTE) * 4;
		}
	}
	return true;
}



bool Visualisation::Draw_Sprite(const std::string &spriteName, int posX, int posY, int frameLimiter) const
{
	if (spriteMap.find(spriteName) == spriteMap.end())
	{
		return false;
	}
	spriteMap.at(spriteName)->Clip_Blit_A(screenStart, posX, posY, (*screenRectangle), frameLimiter);
		return true;

}
bool Visualisation::Create_Animated(const std::string &fileName, const std::string &spriteName, int width, int height, int fWidth, int fHeight, int numFrames, int animRow)
{
	if (spriteMap.find(spriteName) == spriteMap.end()) 
	{
		Sprite *s = new Sprite(width, height, fileName, fWidth, fHeight, numFrames, animRow);
		if (!s->Init_Texture()) {
			delete s;
			return false;
			
		}
		spriteMap[spriteName] = s;
		std::cout << spriteMap.at(spriteName)->Get_Height();
		return true;
		
	}
	return true;
	}



bool Visualisation::Create_Sprite(const std::string &fileName, const std::string &spriteName, int width, int height)
{
	if (spriteMap.find(spriteName) == spriteMap.end()) 
	{
		Sprite *s = new Sprite(width, height, fileName);
		if (!s->Init_Texture()) 
		{
			delete s;
			return false;
		}
		spriteMap[spriteName] = s ;
		return true;
	}
	return true;
}

