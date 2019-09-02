//
// Created by seb on 09/06/19.
//

#include <cmath>
#include "Node.hpp"
#include "Connection.hpp"

Node::Node(unsigned int id): id(id) {
}

void Node::activate() {
	value = 0;
	for (auto &item : connectedFrom) {
		value += item->getWeight();
	}
	activated = value/(1.0 + fabs(value));
}

double Node::getActivated() {
	return activated;
}

void Node::save(std::ofstream &stream) {
	stream << this->id;
	stream << this->value;
	stream << this->activated;

	stream << this->nbConnectedTo;
	stream << this->totalConnectedTo;

	stream << this->nbConnectedFrom;
	stream << this->totalConnectedFrom;
}

void Node::load(std::ifstream &stream) {
	stream >> this->id;
	stream >> this->value;
	stream >> this->activated;

	stream >> this->nbConnectedTo;
	stream >> this->totalConnectedTo;

	stream >> this->nbConnectedFrom;
	stream >> this->totalConnectedFrom;
}

