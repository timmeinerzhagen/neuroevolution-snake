#include "stdafx.h"
#include "SnakeController.h"

#include <time.h> 
#include <iostream>


SnakeController::SnakeController(int fieldWidth, int fieldHeigth)
{
	this->fieldWidth = fieldWidth;
	this->fieldHeigth = fieldHeigth;
	field = (int**) malloc(fieldWidth * sizeof(int));
	for (int i = 0; i<fieldWidth; i++)
		field[i] = (int*)malloc(fieldHeigth * sizeof(int));
}

// Snake gets deleted automatically
SnakeController::~SnakeController()
{
	free(field);
}

int SnakeController::Run()
{
	for (int x = 0; x < fieldWidth; x++)
		for (int y = 0; y < fieldHeigth; y++)
			field[x][y] = 0;

	snake = new Snake();
	int points = -1;
	srand(2);
	do {
		// Place Point on Field
		if (snake->getPoints() != points)
		{
			bool placing = true;
			do
			{
				int x = rand() % fieldWidth;
				int y = rand() % fieldHeigth;
				if (field[x][y] != 1) {
					field[x][y] = 2;
					placing = false;
				}
			} while (placing);
			points = snake->getPoints();
		}

		snake->changeDirection(getControllerInput(field, fieldWidth, fieldHeigth));
		
	} while (snake->Move(field, fieldWidth, fieldHeigth));
	//system("cls");
	//std::cout << "\nGAME OVER";

	delete snake;

	return points;
}
