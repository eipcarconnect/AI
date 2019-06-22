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
#include <random>


class NeuralNetwork {
public:
	NeuralNetwork(NNConfiguration config);

	/// Functions for usage
	void				setInput(std::vector<double> &newInputs);
	void				update();
	std::vector<double>	getOutput();

	/// Functions for learning
	void				createRandomConnection();

/// Tools to make code more readable
private:
	std::shared_ptr<Node> getRandomNodeFrom();
	std::shared_ptr<Node> getRandomNodeTo();

public:
	NNConfiguration		config;
	size_t				id;

	std::unordered_map<unsigned int, std::shared_ptr<Node>>		nodes;
	std::list<std::shared_ptr<Connection>>						connections;

	/// Variables for random numbers
	std::random_device	randomDevice;
	std::mt19937		gene;
	std::uniform_real_distribution<double>	doubleg;
};

typedef decltype(NeuralNetwork::nodes.begin()) itN;
typedef decltype(NeuralNetwork::connections.begin()) itC;
