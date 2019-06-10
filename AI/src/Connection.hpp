//
// Created by seb on 09/06/19.
//

#pragma once

#include <bits/shared_ptr.h>

class Node;

class Connection {
public:
	Connection(std::shared_ptr<Node> &from, std::shared_ptr<Node> &to, double weight = 0.0);

	double	getWeight();


public:
	std::shared_ptr<Node>	from;
	std::shared_ptr<Node>	to;

	double	weight;


};

