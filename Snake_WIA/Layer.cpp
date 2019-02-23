#include "stdafx.h"
#include "Layer.h"

Layer::Layer()
{
	Layer(16, NULL);
}

/*
 * @param nextLayer kann NULL sein wenn outputLayer
 */
Layer::Layer(int size, Layer* nextLayer)
{
	this->size = size;
	this->bias = 0;
	this->nextLayer = nextLayer;

	int sizeNextLayer = 0;
	if (nextLayer != NULL)
		sizeNextLayer = nextLayer->getSize();

	this->neurons = (Neuron**) malloc(size * sizeof(Neuron*));
	for (int i = 0; i < size; i++)
		this->neurons[i] = new Neuron(sizeNextLayer);
}

Layer::Layer(int size, int bias, Neuron** neurons, Layer* nextLayer)
{
	this->size = size;
	this->bias = bias;
	this->neurons = neurons;
	this->nextLayer = nextLayer;
}

Layer::~Layer()
{
	for (int i=0; i<size; i++)
		delete neurons[i];
	free(this->neurons);
}

int Layer::getBias()
{
	return this->bias;
}

void Layer::setBias(int bias)
{
	this->bias = bias;
}

Neuron** Layer::getNeurons()
{
	return this->neurons;
}

void Layer::setNeurons(Neuron** neurons)
{
	this->neurons = neurons;
}

void Layer::setNextLayer(Layer * nextLayer)
{
	this->nextLayer = nextLayer;
}

int Layer::getSize()
{
	return this->size;
}

float * Layer::getLayerResult()
{
	float* erg = (float*) __vcrt_malloc_normal(size * sizeof(Neuron));
	for(int i=0; i<size; i++)
	{
		erg[i] = neurons[i]->getValue();
	}
	return erg;
}
