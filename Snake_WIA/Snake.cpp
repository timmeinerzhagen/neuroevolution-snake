#include "stdafx.h"
#include "Snake.h"

Snake::Snake()
{
	direction = DOWN;
	head = Point(5, 5);
	tail = std::vector<Point>();
	achievedPoints = 0;
	endGame = false;
}

Snake::~Snake()
{
}

int Snake::getPoints()
{
	return achievedPoints;
}

bool Snake::Move(int ** field, int fieldWidth, int fieldHeight)
{
	
	bool cont = true;
	if (!endGame)
	{
		Point newPosition = head.copy();
		switch (direction)
		{
		case UP:    newPosition.y--; break;
		case RIGHT: newPosition.x++; break;
		case DOWN:  newPosition.y++; break;
		case LEFT:  newPosition.x--; break;
		}
		if (newPosition.x < 0 || newPosition.x >= fieldWidth || newPosition.y < 0 || newPosition.y >= fieldHeight)
			cont = false;
		else
		{
			switch (field[newPosition.x][newPosition.y])
			{
			case 0:	//Loesche hinterstes Element
				if (tail.size() > 0)
				{
					field[tail.back().x][tail.back().y] = 0;
					tail.pop_back();
				}
				//Fuege Head vorne ein
				tail.insert(tail.begin(), head);
				//aktualisiere Head
				head = newPosition;
				field[head.x][head.y] = 1;
				break;
			case 1: cont = false;
				break;
			case 2: //Fuege Head vorne ein
				tail.insert(tail.begin(), head);
				//aktualisiere Head
				head = newPosition;
				field[head.x][head.y] = 1;
				achievedPoints++;
				break;
			}
		}
	}
	else
		cont = false;
	return cont;
}

void Snake::changeDirection(Direction direction)
{
	if( (this->direction + direction) % 2 != 0)
		this->direction = direction;
}

void Snake::setEndGame()
{
	this->endGame = true;
}
