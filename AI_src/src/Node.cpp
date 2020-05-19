//
// Created by seb on 09/06/19.
//

#include <cmath>
#include "Node.hpp"
#include "Connection.hpp"

Node::Node(unsigned int id): id(id) {
	value = 0.0;
	activated = 0.0;
}

void Node::activate() {
	if (!connectedFrom.empty())
		value = 0;
	for (auto &item : connectedFrom) {
		value += item->getWeight();
	}
	activated = value/(1.0 + fabs(value));
}

void Node::save(std::ofstream &stream) {
	stream << this->id;
	stream << this->value;
	stream << this->activated;
}

void Node::load(std::ifstream &stream) {
	stream >> this->id;
	stream >> this->value;
	stream >> this->activated;
}

