//
// Created by seb on 09/06/19.
//

#pragma once


#include "Connection.hpp"
#include <list>

class Node {
public:
	Node();

	void activate();

	double	getActivated();

public:
	std::list<std::shared_ptr<Connection>>	connectedAt;
	std::list<std::shared_ptr<Connection>>	connectedTo;

	double	totalPower;
	double	activated;
};
