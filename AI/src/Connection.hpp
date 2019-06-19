//
// Created by seb on 09/06/19.
//

#pragma once

#include <memory>

class Node;

class Connection {
public:
	Connection() = default;
	Connection(std::shared_ptr<Node> &from, std::shared_ptr<Node> &to, double weight = 0.0);

	double	getWeight();


public:
	std::shared_ptr<Node>	from;
	std::shared_ptr<Node>	to;

	double	weight;


};

