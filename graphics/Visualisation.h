#pragma once
#include <HAPI_lib.h>
#include <unordered_map>
#include "Rectangle.h"

class Sprite;

using namespace HAPISPACE;

class Visualisation

{
public:
		Visualisation();
		~Visualisation();
		void Init_Vis(int wWidth, int wHeight);
		bool Clear_To_Colour(int grey);
		bool Clear_To_Colour(int r, int g, int b);
		bool Create_Sprite(const std::string &fileName, const std::string &spriteName, int width, int height);
		bool Create_Animated(const std::string &fileName, const std::string &uniqueName, int width, int height, int fWidth, int fHeight, int numFrames, int animRow);
		bool Draw_Sprite(const std::string &spriteName, int posX, int posY, int frameLimiter) const;
private:
	int Width, Height;
	BYTE *screenStart;
	std::unordered_map<std::string, Sprite*> spriteMap;
	Helper::Rectangle *screenRectangle;
};

