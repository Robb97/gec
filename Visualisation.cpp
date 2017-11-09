#include "Visualisation.h"



Visualisation::Visualisation(int wWidth, int wHeight, BYTE *screenPointer) :
	Width(wWidth), Height(wHeight), screenStart(screenPointer), screenRectangle(wWidth,wHeight)
{

}


Visualisation::~Visualisation()
{
	for (auto p : spriteMap) 
	{
		delete p.second;
	}
}

void Visualisation::Clear_To_Colour(int grey)
{
	memset(screenStart, grey, (Width * Height * 4));
}

void Visualisation::Clear_To_Colour(int r, int g, int b)
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
}


bool Visualisation::Draw_Sprite(const std::string &spriteName, int posX, int posY,int blit) const
{
	if (spriteMap.find(spriteName) == spriteMap.end())
	{
		return false;
	}
	//determining which function to use based on value of blit
	if (blit == 1)
	{
		spriteMap.at(spriteName)->Alpha_Blit(screenStart, Width, posX, posY);
		return true;
	}
	if (blit == 2)
	{
		spriteMap.at(spriteName)->Fast_Blit(screenStart, Width, posX, posY);
		return true;
	}

	if (blit == 3)
	{
		spriteMap.at(spriteName)->Clip_Blit(screenStart, posX, posY, screenRectangle);
		return true;
	}
	return false;
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
	return false;
}

