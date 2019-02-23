#pragma once

#include "Neuron.h"
#include "Layer.h"

class Layer {
	private:
		int bias;
		int size;
		Layer* nextLayer;
		Neuron** neurons;

	public:
		Layer();
		Layer(int size, Layer* nextLayer);
		Layer(int size, int bias, Neuron** neurons, Layer* nextLayer);
		~Layer();

		int getBias();
		void setBias(int bias);

		Neuron** getNeurons();
		void setNeurons(Neuron** neurons);

		void setNextLayer(Layer* nextLayer);
		int getSize();

		float* getLayerResult();
};