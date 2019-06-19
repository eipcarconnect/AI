//
// Created by seb on 09/06/19.
//

#pragma once

#include "Node.hpp"
#include "Connection.hpp"
#include "NeuralData.hpp"
#include <unordered_map>
#include <vector>
#include <list>


class NeuralNetwork {
public:
	NeuralNetwork(NNConfiguration config);

	/// Functions for usage
	void				setInput(std::vector<double> &newInputs);
	void				update();
	std::vector<double>	getOutput();

	/// Functions for learning
	void				createRandomConnection();


public:
	NNConfiguration		config;
	size_t				id;

	std::unordered_map<unsigned int, std::shared_ptr<Node>>		nodes;
	std::list<std::shared_ptr<Connection>>						connections;
};

typedef decltype(NeuralNetwork::nodes.begin()) itN;
typedef decltype(NeuralNetwork::connections.begin()) itC;
