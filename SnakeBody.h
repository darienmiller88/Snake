#pragma once
#include "SnakeHead.h"
#include <vector>

/*
this class will combine the head of the snake, and the tail of the snake (represente by a vector of segements) into a 
unified body. This will be the actual snake representation the user will be controlling, with the head determining where
in space the segements of the tail shall go.
*/
class SnakeBody{
	public:
		SnakeBody(char symbol, int initX, int initY, int amountToGrowBy);

		//return the snakehead by reference so the changes made to it by calling the move() function are permanent, causing
		//the tail of the snake to follow the head and cause the whole body to move.
		SnakeHead &getSnakeHead();   
		std::vector<SnakeSegment> getTail() const;
		int getLength();
		int getScore();
		bool collideWithTail(int rightBorder, int bottomBorder);
		void gotoxy(int x, int y);
		void updateBody();
		void wasFoodEaten(int foodX, int foodY);
		friend std::ostream &operator << (std::ostream & os, SnakeBody &s);
	private:
		SnakeHead snakeHead;
		std::vector<SnakeSegment> tail;
		int score;
		int amountToGrowBy;
		void grow();
};