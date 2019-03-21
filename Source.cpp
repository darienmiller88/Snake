/*
C++ Snake
By Darien Miller
*/

#include <iostream>
#include <string>
#include <random>
#include "SnakeBody.h"
using namespace std;

const int NUM_ROWS = 15;
const int NUM_COLUMNS = 40;
enum gameModeChoice { MODEONE = 4, MODETWO = 5 };
void createMap();
void createFood(int &foodX, int &foodY, const vector<SnakeSegment> &tail);
void gotoxy(int x, int y);
void playGame(const gameModeChoice &userChoice, string &finalMessage);
void displayMenu();
void createMovableCursor(gameModeChoice &userChoice);
int random(int min, int max);
void cpuMove();
void whichDirection(SnakeHead &head, SnakeBody &snake, char direction, int distance);

int main() {
	gameModeChoice userChoice;
	string finalMessage;
	createMovableCursor(userChoice);
	system("cls");
	
	createMap();
	playGame(userChoice, finalMessage);
	
	gotoxy(10, 20);
	cout << finalMessage;
	
}

void playGame(const gameModeChoice &userChoice, string &finalMessage) {
	int foodX, foodY;
	SnakeBody snake('s', NUM_COLUMNS / 2, NUM_ROWS / 2, 3);
	SnakeHead &head = snake.getSnakeHead();
	bool gameIsRunning = true; 

	createFood(foodX, foodY, snake.getTail());
	while (gameIsRunning) {
		cout << snake << endl;
		head.move();
		snake.wasFoodEaten(foodX, foodY);
		if (head.getX() == foodX and head.getY() == foodY)
			createFood(foodX, foodY, snake.getTail());
		snake.updateBody();

		//if the user chose mode one, which is the standard snake game, check for when the head collides with a wall, or 
		//if it runs into itself
		if (userChoice == MODEONE)
			gameIsRunning = !(snake.collideWithTail(NUM_COLUMNS, NUM_ROWS) or head.collidedWithWall(NUM_COLUMNS, NUM_ROWS));
		//otherwise, if mode two was chosen, only check to see if the head collided with the tail
		else {
			gameIsRunning = !snake.collideWithTail(NUM_COLUMNS, NUM_ROWS);
			head.phaseThroughWall(NUM_COLUMNS, NUM_ROWS);
		}

		if (snake.getLength() == NUM_ROWS * NUM_COLUMNS)
			finalMessage = "HOLY SHIT YOU WON! CONGRATS";
		else
			finalMessage = "GAME OVER SCRUB";

		gotoxy(0, NUM_ROWS + 3);
		cout << "Score: " << snake.getScore();
			
		Sleep(50);
	}
}

void createFood(int &foodX, int &foodY, const vector<SnakeSegment> &tail) {
	foodX = random(1, NUM_COLUMNS-1);
	foodY = random(1, NUM_ROWS - 1);
	bool foodInTail = false;
	
	while (!foodInTail){
		foodInTail = true;
		for (size_t i = 0; i < tail.size() and foodInTail; i++)
			if (foodX == tail[i].getX() and foodY == tail[i].getY()) {
				foodX = random(1, NUM_COLUMNS - 1), foodY = random(1, NUM_ROWS - 1);
				foodInTail = false;
			}
	}
	
	gotoxy(foodX, foodY);
	cout << "f";
}

void createMap(){
	for (size_t rows = 0; rows < NUM_COLUMNS; rows++)
		cout << "*";

	cout << "\n";
	for (size_t i = 0; i < NUM_ROWS; i++)
	{
		cout << "*";
		for (size_t i = 0; i < NUM_COLUMNS - 1; i++)
			cout << " ";
		cout << "*\n";
	}

	for (size_t rows = 0; rows < NUM_COLUMNS; rows++)
		cout << "*";
	cout << "\n";
}

void displayMenu() {
	cout << "Welcome to my top quality snake game!! Have fun, follow the on screen instructions, and get a top score\n";
	cout << "To control the snake, use the following commands: w = move up, s = move down, a = move left, d = move down\n";
	cout << "To control the cursor, w to move up, s to move down, enter to choose. Please select your mode\n";

	gotoxy(20, 4);
	cout << "Standard snake game where a wall crash is Game Over";
	gotoxy(20, 5);
	cout << "Special mode where the snake will pass through a wall, and appear on oposite side";
}

void createMovableCursor(gameModeChoice &userChoice) {
	displayMenu();
	int yPos = 4;
	
	char input = ' ';
	while (input != char(13)) {
		gotoxy(15, yPos);
		cout << "-->";
		input = _getch();
		gotoxy(15, yPos);
		cout << "   ";

		if ((input == 'w' or input == 's') and yPos == MODEONE)
			yPos++;
		else if ((input == 'w' or input == 's') and yPos == MODETWO)
			yPos--;
	}
	userChoice = (yPos == MODEONE) ? MODEONE : MODETWO;
}

int random(int min, int max){
	random_device seed;
	default_random_engine rnGen(seed());
	uniform_int_distribution<int> dist(min, max);

	return dist(rnGen);
}

void gotoxy(int x, int y) {
	COORD coord;
	
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
