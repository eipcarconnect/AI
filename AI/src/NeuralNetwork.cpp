//
// Created by seb on 09/06/19.
//

#include <iostream>
#include <deque>
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(NNConfiguration config) : config(config), gene(randomDevice()), doubleg(-1, 1) {
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

			connectedTo->to->value += connectedTo->getWeight();
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

	for(int i = config.input + config.bias; i < config.input + config.bias + config.output; ++i) {
		outputs.emplace_back(nodes[i]->activated);
	}

	return outputs;
}

void NeuralNetwork::createRandomConnection() {
	std::shared_ptr<Node>	from;
	std::shared_ptr<Node>	to;
	std::deque<std::shared_ptr<Node>> queue;
	std::vector<bool> seenNodes;
	bool looping = true;
	std::shared_ptr<Node> elem;

	seenNodes.resize(nodes.size(), false);


	while (looping) {
		from = getRandomNodeFrom();
		to = getRandomNodeTo();
		looping = false;
		queue.push_back(to);
		while(!queue.empty()) {
			elem = queue.front();
			queue.pop_front();

			for (auto it = elem->connectedTo.begin(); it != elem->connectedTo.end(); ++it) {
				if ((*it)->to->id == from->id)
					looping = true;

				if (!seenNodes[(*it)->to->id]) {
					seenNodes[(*it)->to->id] = true;
					queue.push_back((*it)->to);
				}
			}
		}

	}

	std::shared_ptr<Connection> newConnection(new Connection(from, to, doubleg(gene)));
	newConnection->from->connectedTo.emplace_back(newConnection);
	newConnection->to->connectedFrom.emplace_back(newConnection);
	connections.emplace_back(newConnection);
}

std::shared_ptr<Node> NeuralNetwork::getRandomNodeFrom() {
	std::uniform_int_distribution<int>		intg(0, nodes.size() - config.output - 1);
	int rand = intg(gene);

	if (rand >= config.input + config.bias)
		return nodes[rand + config.output];
	return nodes[rand];
}

std::shared_ptr<Node> NeuralNetwork::getRandomNodeTo() {
	std::uniform_int_distribution<int>		intg(config.input + config.bias, nodes.size() - 1);
	int rand = intg(gene);

	return nodes[rand];
}
