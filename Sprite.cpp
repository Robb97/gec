#include "Sprite.h"
#include "Rectangle.h"


Sprite::Sprite(int textureWidth, int textureHeight, std::string path) :
	txtWidth(textureWidth), txtHeight(textureHeight), txtPath(path), txtPntr(nullptr)
{

}

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

bool Sprite::Fast_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY)
{
	BYTE *screenPntr{ screenPointer };
	BYTE *texturePntr{ txtPntr };
	int increment = (screenWidth - 100) * 4;
	int start = (posX + (posY * screenWidth)) * 4;

	screenPntr += start;

	for (int h{ 0 }; h < (txtHeight); h++) {
		for (int w{ 0 }; w < (txtWidth); w++) {
			memcpy(screenPntr, texturePntr, sizeof(HAPI_TColour));
			screenPntr += sizeof(HAPI_TColour);
			texturePntr += sizeof(HAPI_TColour);
		}
		screenPntr += increment;
	}
	return true;
}

bool Sprite::Clip_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest)
{
	BYTE *screenPntr{ screenPointer };
	BYTE *texturePntr{ txtPntr };
	Rectangle spriteRectangle(0,txtWidth,0, txtHeight);
	spriteRectangle.Clip_To(dest, posX, posY);
	if (spriteRectangle.Outside(dest, posX, posY)){}
	else 
	{
		int increment = (dest.Width() - spriteRectangle.Width()) * 4;
		int start = (std::max(0, posX) + (std::max(0, posY)*dest.Width())) * 4;
		int txtIncrement = (txtWidth - spriteRectangle.Width()) * 4;
		int txtStart = (spriteRectangle.Left() + (spriteRectangle.Top() * txtWidth)) * 4;
		screenPntr += start;
		texturePntr += txtStart;
		for (int h{ 0 }; h < spriteRectangle.Height(); h++) 
		{
			for (int w{ 0 }; w < spriteRectangle.Width(); w++)
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
	}
	return true;
}

bool Sprite::Alpha_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY)
{
	BYTE *screenPntr{ screenPointer };
	BYTE *texturePntr{ txtPntr };
	int increment = (screenWidth - txtWidth) * 4;
	int start = (posX + (posY * screenWidth)) * 4;
	screenPntr += start;
	for (int h{ 0 }; h < txtHeight; h++) {
		for (int w{ 0 }; w < txtWidth; w++) {
			BYTE b = texturePntr[0];
			BYTE g = texturePntr[1];
			BYTE r = texturePntr[2];
			BYTE a = texturePntr[3];
			if (a == 255) {
				memcpy(screenPntr, texturePntr, sizeof(BYTE) * 4);
			}
			else {
				screenPntr[0] += ((a * (r - screenPntr[0])) >> 8);
				screenPntr[1] += ((a * (g - screenPntr[1])) >> 8);
				screenPntr[2] += ((a * (b - screenPntr[2])) >> 8);
			}
			screenPntr += sizeof(BYTE) * 4;
			texturePntr += sizeof(BYTE) * 4;
		}
		screenPntr += increment;
	}
	return true;
}