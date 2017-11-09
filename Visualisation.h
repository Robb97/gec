#pragma once
#include <HAPI_lib.h>
#include <unordered_map>
#include "Sprite.h"
#include "Rectangle.h"
using namespace HAPISPACE;

class Visualisation

{
public:
		Visualisation(int wWidth, int wHeight, BYTE *screenPointer);
		~Visualisation();
		void Clear_To_Colour(int grey);
		void Clear_To_Colour(int r, int g, int b);
		bool Create_Sprite(const std::string &fileName, const std::string &spriteName, int width, int height);
		bool Draw_Sprite(const std::string &spriteName, int posX, int posY,int blit) const;
private:
	int Width, Height;
	BYTE *screenStart;
	std::unordered_map<std::string, Sprite*> spriteMap;
	Rectangle screenRectangle;
};

