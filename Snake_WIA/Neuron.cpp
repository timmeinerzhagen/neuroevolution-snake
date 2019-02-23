#include "stdafx.h"
#include "Neuron.h"
#include "Layer.h"

#include <iostream>
#include <windows.h>

Neuron::Neuron(int ammountWeights) 
{
	this->ammountWeights = ammountWeights;

	this->weights = (float*) malloc(ammountWeights * sizeof(float));
	for (int i = 0; i < ammountWeights; i++)
	{
		float ra = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1)));//(rand() % 200 / (float) 200) - 1;
		this->weights[i] = ra;
	}
}

Neuron::Neuron(int ammountWeights, float* weights)
{
	this->ammountWeights = ammountWeights;
	this->weights = weights;
}

Neuron::~Neuron()
{
	free(this->weights);
}



float Neuron::getValue()
{
	return this->value;
}

void Neuron::setValue(float value)
{
	this->value = value;
}

int Neuron::getAmmountWeights()
{
	return this->ammountWeights;
}

float* Neuron::getWeights()
{
	return this->weights;
}

void Neuron::setWeights(float * weights)
{
	this->weights = weights;
}

Neuron * Neuron::copy()
{
	float* weights = (float*) malloc(ammountWeights * sizeof(float));
	for (int i = 0; i < ammountWeights; i++)
	{
		weights[i] = this->weights[i];
	}
	return new Neuron(ammountWeights, weights);
}
