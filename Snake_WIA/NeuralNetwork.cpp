#include "stdafx.h"
#include "NeuralNetwork.h"
#include <vector>
#include <iostream>

NeuralNetwork::NeuralNetwork(int sizeInputLayer, int sizeOutputLayer, int ammountHiddenLayers)
{
	this->ammountLayers = ammountHiddenLayers + 2;
	
	this->fitness = -1;

	layers = (Layer**)malloc(ammountLayers * sizeof(Layer*));
	layers[ammountLayers - 1] = new Layer(sizeOutputLayer, NULL);
	for (int i = ammountLayers - 2; i > 0; i--)
		this->layers[i] = new Layer(16, this->layers[i+1]);
	layers[0] = new Layer(sizeInputLayer, (layers[1]));
}

NeuralNetwork::~NeuralNetwork()
{
	for(int i=0; i<ammountLayers; i++)
		delete layers[i];
	free(layers);
}

int NeuralNetwork::Evaluate(int** field, int x, int y)
{
	//std::vector<Neuron> n = std::vector<Neuron>();
	//for (int i=0; i<layers[0].getSize(); i++) 
	//	n.push_back(layers[0].getNeurons()[i]);


	Neuron** neurons = layers[0]->getNeurons();
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			neurons[i*y + j]->setValue(field[i][j]/(float)2); // 0:Leer; 0,5:Snake; 1: Point

	for(int i=1; i<ammountLayers; i++)
	{
		Neuron** input = layers[i-1]->getNeurons();
		Neuron** output = layers[i]->getNeurons();
		int sizeInput = layers[i-1]->getSize();
		int sizeOutput = layers[i]->getSize();
		for(int j=0; j<sizeOutput; j++)
		{
			float erg = 0;
			for (int k=0; k<sizeInput; k++)
			{
				Neuron* nCurr = input[k];
				float value = nCurr->getValue();
				float* weights = nCurr->getWeights();
				erg += value * weights[j];
			}
			output[j]->setValue(erg);
		}
	}

	//Conclusuion
	Layer* out = layers[ammountLayers - 1];
	float erg = 0;
	int pos = 0;
	for (int i = 0; i < out->getSize(); i++)
	{
		if (out->getNeurons()[i]->getValue() > erg)
		{
			erg = out->getNeurons()[i]->getValue();
			pos = i;
		}
	}
		
	return pos;
}

int NeuralNetwork::getFitness()
{
	return fitness;
}

void NeuralNetwork::setFitness(int fitness)
{
	this->fitness = fitness;
}

Layer ** NeuralNetwork::getLayers()
{
	return layers;
}
