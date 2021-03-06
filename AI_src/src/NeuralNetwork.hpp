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
	std::vector<double>		getOutput();

	bool 				save(std::string path);
	bool 				load(std::string path);

	/// Functions for learning
	void				mutate();
	void				createRandomConnection();
	void				createRandomNode();
	void 				randomiseConnectionWeight();

	/// Tools to make code more readable
private:
	std::shared_ptr<Node>		getRandomNodeFrom();
	std::shared_ptr<Node>		getRandomNodeTo();

public:
	NNConfiguration		config;
	size_t			id;
	size_t 			brainCycle;
	double          fitnesse;

	std::unordered_map<unsigned int, std::shared_ptr<Node>>	nodes;
	std::list<std::shared_ptr<Connection>>			connections;

    /// Variables for random numbers
	std::uniform_real_distribution<double>	doubleg;
};

typedef std::shared_ptr<Node> SNode;
typedef std::shared_ptr<Connection> SConnection;
