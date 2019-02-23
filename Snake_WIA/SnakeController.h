#pragma once

#include "stdafx.h"

#include "Snake.h"

class SnakeController {
protected:
	int fieldWidth, fieldHeigth;
	int** field;
	Snake* snake;
	virtual Direction getControllerInput(int** field, int fieldWidth, int fieldHeigth) = 0;

public:
	SnakeController(int fieldWidth, int fieldHeigth);
	~SnakeController();
	
	int Run();
};