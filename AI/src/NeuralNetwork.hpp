//
// Created by seb on 09/06/19.
//

#pragma once

#include "Node.hpp"
#include "NeuralData.hpp"
#include <queue>

class NeuralNetwork {
public:
	NeuralNetwork(NNConfiguration config);

	void updateInput(std::vector<double> &newInputs);


public:
	NNConfiguration				config;
	size_t					id;

	std::list<std::shared_ptr<Node>>	nodes;
	std::list<std::shared_ptr<Connection>>	connections;
};
