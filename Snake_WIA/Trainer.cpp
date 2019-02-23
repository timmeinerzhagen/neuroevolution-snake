#include "stdafx.h"
#include "Trainer.h"

#include "SnakeControllerComputer.h"
#include <chrono>

Trainer::Trainer()
{
}

Trainer::~Trainer()
{
}

void Trainer::sort()
{
	int min, pos;

	// Min-Sort
	for (int i = 0; i < ammountNetworks; i++)
	{
		pos = i;
		min = networks[i]->getFitness();
		for (int j = i; j < ammountNetworks; j++)
		{
			if (networks[j]->getFitness() < min)
			{
				min = networks[j]->getFitness();
				pos = j;
			}
		}
		NeuralNetwork* helper = networks[i];
		networks[i] = networks[pos];
		networks[pos] = helper;
	}
}

// TO-DO: Mutation
NeuralNetwork * Trainer::recombine(NeuralNetwork * net0, NeuralNetwork * net1, NeuralNetwork * net2, int strengthMutation, int ammountHiddenLayers)
{
	Layer** ll0 = net0->getLayers();
	Layer** ll1 = net1->getLayers();
	Layer** ll2 = net2->getLayers();
	for (int i = 0; i < ammountHiddenLayers + 1; i++)
	{
		Layer* l0 = ll0[i];
		Layer* l1 = ll1[i];
		Layer* l2 = ll2[i];

		for (int j = 0; j < l1->getSize(); j++)
		{
			Neuron** n0 = l0->getNeurons();

			int ra = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (strengthMutation - 1));

			// Mutation
			if (ra == 0)
			{
				delete n0[j];
				n0[j] = new Neuron(l1->getNeurons()[j]->getAmmountWeights());
				Neuron** n1 = l1->getNeurons();
				auto weights = n0[j]->getWeights();
				int random = static_cast <int> (rand()) / (static_cast <float> (RAND_MAX / n0[j]->getAmmountWeights()));
				weights[random] = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
				n0[j]->setWeights(weights);
			}
			// Normal
			else
			{
				Neuron** n1 = l1->getNeurons();
				Neuron** n2 = l2->getNeurons();
				int random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
				Neuron* n;
				if (random == 0)
					n = n1[j]->copy();
				else
					n = n2[j]->copy();
				delete n0[j];
				n0[j] = n;
			}
		}
	}
	return net0;
}

NeuralNetwork* Trainer::train(int generations, int ammountNetworks, int fieldWidth, int fieldHeight, int ammountHiddenLayers)
{
	// Create Generation 1 Networks
	srand(time(NULL));
	this->networks = (NeuralNetwork**)malloc(ammountNetworks * sizeof(NeuralNetwork*));
	this->ammountNetworks = ammountNetworks;
	for (int i = 0; i < ammountNetworks; i++)
	{
		networks[i] = new NeuralNetwork(fieldWidth * fieldHeight, 4, ammountHiddenLayers);
	}

	
	// Process of Evolution
	SnakeControllerComputer controller = SnakeControllerComputer(fieldWidth, fieldHeight, 0, true);
	for (int i = 0; i < generations; i++)
	{
		std::cout << "Generation Nr. ";
		std::cout << i + 1;
		std::cout << "\n";

		//if (i > 1)
		//	controller.setSleep(1);

		// Evaluate the Networks
		for (int j = 0; j < ammountNetworks; j++)
		{
			if (networks[j]->getFitness() == -1)
			{
				controller.setNetwork(networks[j]);
				int run = controller.Run();
				networks[j]->setFitness(run);
				std::cout << run;
			}
		}
		std::cout << "\n";

		// Sort the Networks
		sort();
		std::cout << "Sorted\n";
		for (int j = 0; j < ammountNetworks; j++)
		{
				std::cout << networks[j]->getFitness();
		}
		std::cout << "\n";

		//srand(rand() + i );
		// Recombine the Networks; rewrite 1/10 of the created Networks
		for (int i = 0; i < ammountNetworks / 2; i++)
		{
			int randomNetwork = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (ammountNetworks-1));
			//NeuralNetwork* helper = recombine(networks[i], networks[ammountNetworks-i-1], networks[randomNetwork], 4, ammountHiddenLayers);
			//NeuralNetwork* helper = recombine(networks[i], networks[ammountNetworks-i-1], networks[ammountNetworks + i - 1 - ammountNetworks / 2], 0, ammountHiddenLayers);
			NeuralNetwork* helper = recombine(networks[i], networks[ammountNetworks - 1], networks[ammountNetworks - 1], 5, ammountHiddenLayers);
			networks[i] = helper;
			helper->setFitness(-1);
		}

	}
	
	/*for (int i = 0; i < ammountNetworks; i++)
	{
		std::cout << i;
		std::cout << " - ";
		std::cout << networks[i]->getFitness();
		std::cout << "\n";
	}*/

	// Free Memory used by Networks; TO-DO for correct Network/Needs to be saved
	for (int i = 0; i < ammountNetworks; i++)
	{
		delete networks[i];
	}
	free(networks);



	// TO DO
	return NULL;
}
