//
// Created by seb on 09/06/19.
//

#include "Connection.hpp"
#include "Node.hpp"
#include "NeuralNetwork.hpp"

Connection::Connection(std::shared_ptr<Node> &from, std::shared_ptr<Node> &to, double weight):
	from(from), to(to), weight(weight){
}

double Connection::getWeight() {
	return from->activated * weight;
}

void Connection::save(std::ofstream &stream) {
	stream << this->from->id;
	stream << this->to->id;

	stream << this->weight;
}

void Connection::load(std::ifstream &stream, NeuralNetwork &network) {
	unsigned int id;

	stream >> id;
	this->from = network.nodes[id];

	stream >> id;
	this->to = network.nodes[id];

	stream >> this->weight;
}
