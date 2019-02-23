#include "stdafx.h"
#include "SnakeControllerPlayer.h"

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

SnakeControllerPlayer::SnakeControllerPlayer(int fieldWidth, int fieldHeigth, int sleepTime) : SnakeController(fieldWidth, fieldHeigth)
{
	lastDirection = RIGHT;
	this->sleepTime = sleepTime;
}

SnakeControllerPlayer::~SnakeControllerPlayer()
{
}

void SnakeControllerPlayer::display(int ** field, int fieldWidth, int fieldHeigth)
{
	system("cls");
	for (int i = 0; i < fieldWidth + 2; i++)
		std::cout << "-";
	std::cout << "\n";
	for (int y = 0; y < fieldHeigth; y++)
	{
		std::cout << "|";
		for (int x = 0; x < fieldWidth; x++)
		{
			char out;
			switch (field[x][y])
			{
				case 0: out = ' '; 
						break;
				case 1: out = 'O';
						break;
				case 2: out = '*';
						break;
			}
			std::cout << out;
		}
		std::cout << "|\n";
	}
	for (int i = 0; i<fieldWidth + 2; i++)
		std::cout << "-";
	std::cout << "\n";

	switch (lastDirection)
	{
	case UP:    std::cout << "UP"; break;
	case RIGHT: std::cout << "RIGHT"; break;
	case DOWN:  std::cout << "DOWN"; break;
	case LEFT:  std::cout << "LEFT"; break;
	}
}

Direction SnakeControllerPlayer::getControllerInput(int ** field, int fieldWidth, int fieldHeigth)
{
	display(field, fieldWidth, fieldHeigth);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		lastDirection = UP;
	else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		lastDirection = RIGHT;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		lastDirection = DOWN;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		lastDirection = LEFT;
	return lastDirection;
}
