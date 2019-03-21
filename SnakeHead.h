#pragma once
#include "SnakeSegment.h"

/*
This class will inherit from the SnakeSegment class, and will determine the unique behavior of the head of the snake. I chose
to visualize the snake in two parts: the head and the body, whereby the head is a segment that can the player can move 
through user input, and manually change its positioned, whereas a segment is stationary until it is updated through its 
member functions.
*/
class SnakeHead : public SnakeSegment{
	public:
		SnakeHead(char symbol, int initX, int initY);
		void move();
		bool collidedWithWall(int rightBorder, int bottomBorder);
		void phaseThroughWall(int rightBorder, int bottomBorder);
		void flickerSnakeHead();
		void cpuMove(char moveDirection);
		void update();
	private:
		int xSpeed;
		int ySpeed;
		

		//enum to assign a char direction to one of these constants. 
		enum movement { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
		movement direction;
};