#pragma once

#include "SnakeController.h"
#include "NeuralNetwork.h"

class SnakeControllerComputer : public SnakeController {
private:
	int sleepTime;
	Direction lastDirection;
	NeuralNetwork* network;
	void display(int ** field, int fieldWidth, int fieldHeigth);
	bool terminateLoops;
	int roundCount;

protected:
	virtual Direction getControllerInput(int** field, int fieldWidth, int fieldHeigth);
public:
	SnakeControllerComputer(int fieldWidth, int fieldHeigth, int sleepTime, bool terminateLoops);
	SnakeControllerComputer(NeuralNetwork * network, int fieldWidth, int fieldHeigth, int sleepTime, bool terminateLoops);
	~SnakeControllerComputer();

	void setSleep(int sleepTime);

	void setNetwork(NeuralNetwork* network);
	NeuralNetwork* getNetwork();
};