#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>

/*
 This class will contain the information needed to create a segment of the snake body in the output window. SnakeSegment
 objects will contain information about its own current position and previous position, allowing it to be update in a way
 the simulates motion.
*/
class SnakeSegment{
	public:
		SnakeSegment(char snakeChar, int initX, int initY);
		char getSymbol();
		void setX(int x);
		void setY(int y);
		int getX() const;
		int getY() const;
		int getXPrevious();
		int getYPrevious();
		friend std::ostream &operator << (std::ostream & os, SnakeSegment &s);
	protected:
		void gotoxy(int x, int y);
		char snakeChar;
		int x;
		int y;
		int xPrevious;
		int yPrevious;
};