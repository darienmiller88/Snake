#include "SnakeBody.h"

SnakeBody::SnakeBody(char symbol, int initX, int initY, int amountToGrowBy) : snakeHead(symbol, initX,initY), 
	amountToGrowBy(amountToGrowBy), score(0){
}

int SnakeBody::getLength(){
	return tail.size();
}

int SnakeBody::getScore(){
	return score;
}

void SnakeBody::gotoxy(int x, int y) {
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool SnakeBody::collideWithTail(int rightBorder, int bottomBorder){
	//if the head of the snake runs into the tail at any point, the game will also end, and true will be returned. 
	for (auto &segment : tail)
		if (segment.getX() == snakeHead.getX() and segment.getY() == snakeHead.getY()) {
			snakeHead.flickerSnakeHead();
			return true;
		}

	//otherwise, if the player isn't trash, return false and let the game continue.
	return false;
}

void SnakeBody::wasFoodEaten(int foodX, int foodY){
	if (snakeHead.getX() == foodX and snakeHead.getY() == foodY) {
		for (size_t i = 0; i < amountToGrowBy; i++)
			grow();
		score += 10;
	}		
}

SnakeHead &SnakeBody::getSnakeHead(){
	return snakeHead;
}

std::vector<SnakeSegment> SnakeBody::getTail() const{
	return tail;
}

void SnakeBody::grow(){
	if (tail.size() == 0) 
		tail.push_back(SnakeSegment(snakeHead.getSymbol(), snakeHead.getXPrevious(), snakeHead.getYPrevious()));
	else if (tail.size() > 0) {
		SnakeSegment lastSegment = tail.back();
		tail.push_back(SnakeSegment(snakeHead.getSymbol(), lastSegment.getXPrevious(), lastSegment.getYPrevious()));
	}
}

//The way we will go about updating the positions of all of the segments is by abiding by my rule of "A sgement's 
//current x and y position is the previous x and y of the segment in front of it". For example, the previous x and y
//of the snake head will be the current x and y of the first sgement of the tail, causing it to follow the head. The
//previous x and y of the first segment will be the current x and y of the second, and so on.
void SnakeBody::updateBody(){
	if (tail.size() > 0) {
		tail.front().setX(snakeHead.getXPrevious());
		tail.front().setY(snakeHead.getYPrevious());
		for (size_t i = 1; i < tail.size(); i++){
			tail[i].setX(tail[i - 1].getXPrevious());
			tail[i].setY(tail[i - 1].getYPrevious());
		}
	}
}

//print out the entire snake body (head + tail)
std::ostream &operator << (std::ostream &os, SnakeBody &s){
	os << s.getSnakeHead();
	for (auto &segment : s.tail)
		os << segment;
	return os;
}