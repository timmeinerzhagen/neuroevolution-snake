#include "stdafx.h"
#include "SnakeControllerComputer.h"


#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <string>

SnakeControllerComputer::SnakeControllerComputer(int fieldWidth, int fieldHeigth, int sleepTime, bool terminateLoops) : SnakeController(fieldWidth, fieldHeigth)
{
	lastDirection = RIGHT;
	this->sleepTime = sleepTime;
	this->network = new NeuralNetwork(fieldWidth*fieldHeigth, 4, 2);
	this->roundCount = 0;
	this->terminateLoops = terminateLoops;
}

SnakeControllerComputer::SnakeControllerComputer(NeuralNetwork* network, int fieldWidth, int fieldHeigth,  int sleepTime, bool terminateLoops) : SnakeController(fieldWidth, fieldHeigth)
{
	lastDirection = RIGHT;
	this->sleepTime = sleepTime;
	this->network = network;
	this->roundCount = 0;
	this->terminateLoops = terminateLoops;
}

// Never delete the Current Network
SnakeControllerComputer::~SnakeControllerComputer()
{
}

void SnakeControllerComputer::setNetwork(NeuralNetwork * network)
{
	this->network = network;
	roundCount = 0;
}

NeuralNetwork * SnakeControllerComputer::getNetwork()
{
	return network;
}

void SnakeControllerComputer::setSleep(int sleepTime)
{
	this->sleepTime = sleepTime;
}

void SnakeControllerComputer::display(int ** field, int fieldWidth, int fieldHeigth)
{
	system("cls");

	std::cout << roundCount / (snake->getPoints() + 1);
	std::cout << "\n";

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
	std::cout << "\n";
	std::cout.precision(2);
	for(int i=1; i<network->ammountLayers; i++)
	{
		std::cout << "Layer ";
		std::cout << (i + 1);
		std::cout << "\n";
		float* result = network->layers[i]->getLayerResult();
		for (int j = 0; j < network->layers[i]->getSize(); j++)
		{
			std::cout << result[j] * 2;
			std::cout << " ; ";
			if ((j + 1) % 20 == 0)
				std::cout << "\n";
		}
			
		std::cout << "\n";
		
	}
}

Direction SnakeControllerComputer::getControllerInput(int ** field, int fieldWidth, int fieldHeigth)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

	// Test for endless Loops
	if (terminateLoops && roundCount / (snake->getPoints() + 1) > 50)
	{
		snake->setEndGame();
	}
	// Normal Action
	else 
	{
		lastDirection = (Direction)(network->Evaluate(field, fieldWidth, fieldHeigth) + 1);
		if (sleepTime != 0)
			display(field, fieldWidth, fieldHeigth);
		roundCount++;
	}
	return lastDirection;
}
