#pragma once
#include <algorithm>

namespace Helper
{
	class Rectangle
	{
	public:
		int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };
		Rectangle() = default;
		Rectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
		Rectangle(int w, int h) : left(0), right(w), top(0), bottom(h) {}
		~Rectangle() {}

		//'Get' & 'Set' functions for dimensions
		int Get_Left() const { return left; }
		int Get_Top() const { return top; }
		int Get_Width() const { return right - left; }
		int Get_Height() const { return bottom - top; }

		void Set_Height(int height) 
		{
			(height < 1) ? bottom = bottom : bottom = height;
		}

		void Set_Width(int width)
		{
			(width < 1) ? right = right : right = width;
		}

		// by applying translate within this file it will me from calling it multiple times throughout the whole project by
		// calling it inside every function here
		void Translate(int tempX, int tempY)
		{
			top += tempY;
			bottom += tempY;
			left += tempX;
			right += tempX;
		}

		//clip to rectangle, making use of min/max to determine the dimensions of the clipped rectangle
		void Clip_To(const Rectangle& other, int posX, int posY)
		{
			Translate(posX, posY);
			left = std::max(left, other.left);
			right = std::min(right, other.right);
			top = std::max(top, other.top);
			bottom = std::min(bottom, other.bottom);
			Translate(-posX, -posY);
		}
		//checks if rectangle is inside of referenced rectangled
		bool Contained(const Rectangle& other, int posX, int posY)
		{
			Translate(posX, posY);
			if ((left > 0 && right < other.Get_Width()) && (top > 0 && bottom < other.Get_Height()))
			{
				Translate(-posX, -posY);
				return true;
			}
			Translate(-posX, -posY);
			return false;
		}
		//checks if rectangle is outside of referenced rectangled
		bool Outside(const Rectangle& other, int posX, int posY)
		{
			Translate(posX, posY);
			if (right <= 0 || left > other.Get_Width())
			{
				Translate(-posX, -posY);
				return true;
			}
			else if (bottom < 0 || top >= other.Get_Height())
			{
				Translate(-posX, -posY);
				return true;
			}
			Translate(-posX, -posY);
			return false;
		}


	};

}