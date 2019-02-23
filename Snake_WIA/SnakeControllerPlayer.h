#pragma once

#include "SnakeController.h"

class SnakeControllerPlayer : public SnakeController {
private:
	Direction lastDirection;
	int sleepTime;

	void display(int ** field, int fieldWidth, int fieldHeigth);

protected:
	virtual Direction getControllerInput(int** field, int fieldWidth, int fieldHeigth);

public:
	SnakeControllerPlayer(int fieldWidth, int fieldHeigth, int sleepTime);
	~SnakeControllerPlayer();
};