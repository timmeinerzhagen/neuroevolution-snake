#pragma once

class Neuron {
	private:
		float value;
		int ammountWeights;
		float* weights;

	public:
		Neuron(int ammountWeights);
		Neuron(int ammountWeights, float* weights);
		~Neuron();

		float getValue();
		void setValue(float value);


		int getAmmountWeights();

		float* getWeights();
		void setWeights(float* weights);

		Neuron* copy();
};