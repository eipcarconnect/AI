//
// Created by seb on 09/06/19.
//

#pragma once


//#include "Connection.hpp"
#include <memory>
#include <list>
#include <iostream>
#include <fstream>

class Connection;

class Node {
public:
	Node() = default;
	Node(unsigned int id);

	void	activate();

	double	getActivated();

	void	save(std::ofstream &stream);
	void	load(std::ifstream &stream);

public:
	unsigned int	id;

	std::list<std::shared_ptr<Connection>>	connectedFrom;
	std::list<std::shared_ptr<Connection>>	connectedTo;

	double	value;
	double	activated;

	unsigned int	nbConnectedTo;
	unsigned int	totalConnectedTo;

	unsigned int	nbConnectedFrom;
	unsigned int	totalConnectedFrom;
};
