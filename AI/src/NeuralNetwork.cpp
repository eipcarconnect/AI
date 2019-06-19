//
// Created by seb on 09/06/19.
//

#include <iostream>
#include <deque>
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(NNConfiguration config) : config(config) {
	id = config.input + config.bias + config.output;

	for (unsigned int i = 0; i < id; ++i) {
		nodes.emplace(i, new Node(i));
	}

}

void NeuralNetwork::setInput(std::vector<double> &newInputs) {
	for (auto &node : nodes) {
		node.second->value = 0;
		node.second->activated = 0;
		node.second->nbConnectedFrom = 0;
		node.second->nbConnectedTo = 0;

		node.second->totalConnectedFrom = node.second->connectedFrom.size();
		node.second->totalConnectedTo = node.second->connectedTo.size();
	}

	for (int i = 0; i < newInputs.size(); ++i) {
		nodes[i]->activated = newInputs[i];
	}
}

void NeuralNetwork::update() {
	std::deque < std::shared_ptr < Node > > queue;
	std::shared_ptr < Node >	elem;
	itN it = nodes.begin();

	for(int i = 0; i < config.input; ++i) {
		queue.emplace_back(nodes[i]);
		++it;
	}

	while(!queue.empty()) {
		elem = queue.front();
		queue.pop_front();

		for (auto &connectedTo : elem->connectedTo) {

			connectedTo->to->value += elem->activated * connectedTo->weight;
			connectedTo->to->nbConnectedFrom++;
			if (connectedTo->to->nbConnectedFrom == connectedTo->to->totalConnectedFrom) {
				connectedTo->to->activate();
				queue.push_back(connectedTo->to);
			}
		}
	}
}

std::vector<double> NeuralNetwork::getOutput() {
	std::vector<double> outputs;
	outputs.reserve(config.output);

	itN it = nodes.begin();
	for(int i = 0; i < config.input + config.bias; ++i, ++it);

	for(int i = config.input + config.bias; i < config.input + config.bias + config.output; ++i, ++it) {
		outputs.emplace_back((*it).second->activated);
	}

	return outputs;
}

void NeuralNetwork::createRandomConnection() {
	std::shared_ptr<Connection> connection(new Connection(nodes[0], nodes[5], 0.5));
	connections.push_back(connection);

	connection->from->connectedTo.push_back(connection);
	connection->to->connectedFrom.push_back(connection);
}
