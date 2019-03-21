#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(char snakeChar, int initX, int initY) : snakeChar(snakeChar), x(initX), y(initY),
	xPrevious(initX), yPrevious(initY){
}

char SnakeSegment::getSymbol(){
	return snakeChar;
}

int SnakeSegment::getX() const{
	return x;
}

int SnakeSegment::getY() const{
	return y;
}

int SnakeSegment::getXPrevious(){
	return xPrevious;
}

int SnakeSegment::getYPrevious(){
	return yPrevious;
}

void SnakeSegment::setY(int newY){
	yPrevious = y;
	y = newY;
}

void SnakeSegment::setX(int newX){
	//before updating, save the value of the segment's old position so we know where it was in the previous instance.
	xPrevious = x;
	x = newX;
}

//function to change the cursor position in the output, creating the concept of a x-y coordinate plane
void SnakeSegment::gotoxy(int x, int y){
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::ostream & operator<<(std::ostream & os, SnakeSegment & s){
	//in order to create the illusion of movement, we have to first print out a blank where the segment USED to be prior to
	//changing its position
	s.gotoxy(s.getXPrevious(), s.getYPrevious());
	os << " ";

	//afterwards, print out the segment in its current position. The repetition of printing out a blank in the previous 
	//position, and printing out the actual character value in its current position creates the illusion of movement
	s.gotoxy(s.getX(), s.getY());
	os << s.getSymbol();

	//reset the cursor to the top left so it doesn't follow the segment as it "moves" in the output
	s.gotoxy(0, 0);

	return os;
}
