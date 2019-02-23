#pragma once

#include "Layer.h"

class NeuralNetwork {
private:

public:
	Layer** layers;
	int ammountLayers;
	int fitness;
	NeuralNetwork(int sizeInputLayer, int sizeOutputLayer, int ammountHiddenLayers);
	~NeuralNetwork();

	int Evaluate(int** input, int x, int y);
	int getFitness();
	void setFitness(int fitness);

	Layer** getLayers();
};