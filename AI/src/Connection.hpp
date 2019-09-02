//
// Created by seb on 09/06/19.
//

#pragma once

#include <memory>
#include <fstream>

class NeuralNetwork;
class Node;

class Connection {
public:
	Connection() = default;
	Connection(std::shared_ptr<Node> &from, std::shared_ptr<Node> &to, double weight = 0.0);

	double	getWeight();

	void	save(std::ofstream &stream);
	void	load(std::ifstream &stream, NeuralNetwork &network);

public:
	std::shared_ptr<Node>	from;
	std::shared_ptr<Node>	to;

	double	weight;


};

