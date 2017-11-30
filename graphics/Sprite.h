#pragma once

#include<HAPI_lib.h>
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(int textureWidth, int textureHeight, std::string path);
	Sprite(int textureWidth, int textureHeight, std::string path, int frameWidth, int frameHeight, int numOfFrames, int animRow);
	~Sprite();

	int Get_Height() const { return txtHeight; }
	int Get_Width() const { return txtWidth; }
	bool Init_Texture();
	bool Clip_Blit_A(BYTE *screenPointer, int posX, int posY, const Helper::Rectangle &dest, int frameLimiter);


private:
	int txtWidth, txtHeight;
	std::string txtPath;
	BYTE *txtPntr;
	int tWidth, tHeight, fNum, numFrames, rowNum;
	Helper::Rectangle frameRectangle;
	int counter;
};

