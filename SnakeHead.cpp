#include "SnakeHead.h"

SnakeHead::SnakeHead(char snakeChar, int initX, int initY) : SnakeSegment(snakeChar, initX, initY), xSpeed(0), ySpeed(0){
}

void SnakeHead::update() {
	xPrevious = x;
	yPrevious = y;
	
	//the x and y of the snakehead will change in accordance to an x and y speed value. So if the x speed is changed to 5, 
	//the snake will move along the x axis by 5 units every time update() is called.
	x += xSpeed;
	y += ySpeed;
}

//This function is simply for fun + cosmetics. Once the users game has ended, cause the head of the snake to flicker 
//on and off
void SnakeHead::flickerSnakeHead(){
	for (size_t i = 0; i < 3; i++) {
		gotoxy(xPrevious, yPrevious);
		std::cout << " ";
		Sleep(200);
		gotoxy(xPrevious, yPrevious);
		std::cout << snakeChar;
		Sleep(200);
	}
}

void SnakeHead::cpuMove(char moveDirection){
	if (moveDirection == UP and direction != DOWN)
		ySpeed = -1, xSpeed = 0, direction = UP;
	else if (moveDirection == DOWN and direction != UP)
		ySpeed = 1, xSpeed = 0, direction = DOWN;
	else if (moveDirection == RIGHT and direction != LEFT)
		xSpeed = 1, ySpeed = 0, direction = RIGHT;
	else if (moveDirection == LEFT and direction != RIGHT)
		xSpeed = -1, ySpeed = 0, direction = LEFT;
	direction = movement();
	//update();
}

void SnakeHead::phaseThroughWall(int rightBorder, int bottomBorder){
	if (x == rightBorder)
		x = 1;
	else if (x == 0)
		x = rightBorder - 1;
	else if (y == bottomBorder)
		y = 1;
	else if (y == 0)
		y = bottomBorder - 1;
}

void SnakeHead::move() {
	char input = ' ';

	if (_kbhit()) {
		input = _getch();

		//in order to prevent the user from going backwards, the snake head can only move in a given direction so long as 
		//the direction the user inputs isn't opposite of where the snake is moving. For example, a snake head can only move
		//down as long as it IS NOT currently moving up. 
		if (input == UP and direction != DOWN)
			ySpeed = -1, xSpeed = 0, direction = UP;
		else if (input == DOWN and direction != UP)
			ySpeed = 1, xSpeed = 0, direction = DOWN;
		else if (input == RIGHT and direction != LEFT)
			xSpeed = 1, ySpeed = 0, direction = RIGHT;
		else if (input == LEFT and direction != RIGHT)
			xSpeed = -1, ySpeed = 0, direction = LEFT;
	}
	update();
}

bool SnakeHead::collidedWithWall(int rightBorder, int bottomBorder){
	if (x >= rightBorder or x == 0 or y == 0 or y > bottomBorder) {
		flickerSnakeHead();
		return true;
	}
	return false;
}