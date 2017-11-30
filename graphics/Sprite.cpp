#include "Sprite.h"
#include "Rectangle.h"


Sprite::Sprite(int textureWidth, int textureHeight, std::string path) : txtWidth(textureWidth), txtHeight(textureHeight),
txtPath(path), txtPntr(nullptr), frameRectangle(textureWidth, textureHeight), numFrames(0), fNum(0), rowNum(0)
{
	
}

Sprite::Sprite(int textureWidth, int textureHeight, std::string path, int frameWidth, int frameHeight, int numOfFrames, int animRow) :txtWidth(textureWidth), txtHeight(textureHeight), fNum(0), numFrames(numOfFrames), txtPath(path), txtPntr(nullptr), frameRectangle(0, frameWidth, 0, frameHeight), rowNum(animRow) {}


Sprite::~Sprite()
{
	delete[] txtPntr;
}

bool Sprite::Init_Texture()
{
	if (!HAPI.LoadTexture(txtPath, &txtPntr, txtWidth, txtHeight)) {
		return false;
	}
	return true;
}
bool Sprite::Clip_Blit_A(BYTE *screenPointer, int posX, int posY,const Helper::Rectangle &dest,int frameLimiter)
{
	BYTE *screenPntr{ screenPointer };
	BYTE *texturePntr{ txtPntr };
	Helper::Rectangle spriteRectangle(frameRectangle);
	spriteRectangle.Clip_To(dest, posX, posY);
	const int rowCoords = rowNum * frameRectangle.Get_Height();
	spriteRectangle.Translate(frameRectangle.Get_Width() * fNum, rowCoords);
	if (frameRectangle.Outside(dest, posX, posY))  return false;
		int increment = (dest.Get_Width() - spriteRectangle.Get_Width()) * 4;
		int start = (std::max(0, posX) + (std::max(0, posY)*dest.Get_Width())) * 4;
		int txtIncrement = (Get_Width() - spriteRectangle.Get_Width()) * 4;
		int txtStart = (spriteRectangle.Get_Left() + (spriteRectangle.Get_Top() * Get_Width())) * 4;
		screenPntr += start;
		texturePntr += txtStart;
		for (int h{ 0 }; h < spriteRectangle.Get_Height(); h++)
		{
			for (int w{ 0 }; w < spriteRectangle.Get_Width(); w++)
			{
				BYTE b = texturePntr[0];
				BYTE g = texturePntr[1];
				BYTE r = texturePntr[2];
				BYTE a = texturePntr[3];
				if (a == 255) {
					memcpy(screenPntr, texturePntr, sizeof(BYTE) * 4);
				}
				else if (a == 0) {}
				else {
					screenPntr[0] += ((a * (r - screenPntr[0])) >> 8);
					screenPntr[1] += ((a * (g - screenPntr[1])) >> 8);
					screenPntr[2] += ((a * (b - screenPntr[2])) >> 8);
				}
				screenPntr += sizeof(BYTE) * 4;
				texturePntr += sizeof(BYTE) * 4;
			}
			screenPntr += increment;
			texturePntr += txtIncrement;
		}

		if (counter == frameLimiter && fNum < numFrames)
		{
			fNum++;
			counter = 0;
		}
		else if (counter< frameLimiter)
		{
			counter++;
		}
		else 
		{
			fNum = 0;
				
		}
			return true;
}
