#pragma once

#include "stdafx.h"
#include <vector>

class Snake {
private:
	Direction direction;
	Point head;
	std::vector<Point> tail;
	int achievedPoints;
	bool endGame;

public:
	Snake();
	~Snake();

	int getPoints();
	bool Move(int** field, int fieldWidth, int fieldHeight);
	void changeDirection(Direction direction);
	void setEndGame();
};