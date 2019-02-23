#pragma once

#include "NeuralNetwork.h"

class Trainer {
private:
	void sort();
	NeuralNetwork * recombine(NeuralNetwork* net0, NeuralNetwork* net1, NeuralNetwork* net2, int strengthMutation, int ammountHiddenLayers);
public:
	NeuralNetwork ** networks;
	int ammountNetworks;
	Trainer();
	~Trainer();

	NeuralNetwork* train(int generations, int ammountNetworks, int fieldWidth, int fieldHeight, int ammountHiddenLayers);
};