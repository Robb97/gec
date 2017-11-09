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
	bool Fast_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY);
	bool Clip_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest);
	bool Alpha_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY);
	bool Change_Anim(int newRow);

private:
	int txtWidth, txtHeight;
	std::string txtPath;
	BYTE *txtPntr;
	int tWidth, tHeight, fNum, numFrames, rowNum;
	Rectangle frameRect;
};

