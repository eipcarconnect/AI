//
// Created by seb on 09/06/19.
//

#include <iostream>
#include <deque>
#include <fstream>
#include "NeuralNetwork.hpp"
#include <algorithm>

NeuralNetwork::NeuralNetwork(NNConfiguration config) : config(config), gene(randomDevice()), doubleg(-1, 1) {
	brainCycle = 20;
	id = config.input + config.bias + config.output;

	for (unsigned int i = 0; i < id; ++i) {
		nodes.emplace(i, new Node(i));
	}

}

void NeuralNetwork::setInput(std::vector<double> &newInputs) {
	for (auto &node : nodes) {
		node.second->value = 0;
		node.second->activated = 0;
	}

	for (int i = 0; i < newInputs.size(); ++i) {
		nodes[i]->activated = newInputs[i];
	}
}

void NeuralNetwork::update() {
	std::vector<std::shared_ptr<Node>>	queue;
	std::shared_ptr<Node>			elem;

	for(int i = 0; i < config.input; ++i) {
		for(auto const &connection : nodes[i]->connectedTo)
			queue.emplace_back(connection->to);
	}


	for(int i = 0; i < this->brainCycle && !queue.empty(); ++i) {
		std::vector<std::shared_ptr<Node>> tmp;
		for(auto &node : queue) {
			node->activate();
			for(auto const &next_connec : node->connectedTo) {
				if(std::find(tmp.begin(), tmp.end(), next_connec->to) == tmp.end())
					tmp.push_back(next_connec->to);
			}
			queue = tmp;
		}
	}
	/*while(!queue.empty()) {
		elem = queue.front();
		queue.pop_front();

		for (auto &connectedTo : elem->connectedTo) {

			connectedTo->to->value += connectedTo->getWeight();
			connectedTo->to->nbConnectedFrom++;
	std::cout << "debug " << connectedTo->to->nbConnectedFrom << " " << connectedTo->to->totalConnectedFrom << std::endl;
			if (connectedTo->to->nbConnectedFrom == connectedTo->to->totalConnectedFrom - 1) {
				connectedTo->to->activate();
				queue.push_back(connectedTo->to);
			}
		}
	}*/
}

std::vector<double> NeuralNetwork::getOutput() {
	std::vector<double> outputs;
	outputs.reserve(config.output);

	for(int i = config.input + config.bias; i < config.input + config.bias + config.output; ++i) {
		outputs.emplace_back(nodes[i]->activated);
	}

	return outputs;
}

void NeuralNetwork::mutate() {
	createRandomConnection();
	createRandomNode();

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
		BEGIN:
		from = getRandomNodeFrom();
		to = getRandomNodeTo();
		for (const auto &item : from->connectedTo) {
			if (item->to->id == to->id)
				goto BEGIN;
		}
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

void NeuralNetwork::createRandomNode() {
	if (connections.empty())
		return;

	std::uniform_int_distribution<int> intg(0, connections.size() - 1);
	SConnection connection;
	SNode		node(new Node(++id));

	auto it = connections.begin();
	std::next(it, intg(gene));

	/// Creating the new Node
	SNode new_node(new Node());
	SConnection new_connection(new Connection(new_node, (*it)->to));
	new_connection->weight = 1.0;

	new_connection->from = new_node;
	new_connection->to = (*it)->to;
	new_connection->to->connectedFrom.remove(new_connection);

	(*it)->to = new_node;

	new_node->connectedFrom.push_back((*it));
	new_node->connectedTo.push_back(new_connection);

	new_connection->to->connectedFrom.remove((*it));
	this->connections.push_back(new_connection);
	this->nodes[id] = new_node;

}

void NeuralNetwork::randomiseConnectionWeight() {
	if (connections.empty())
		return;
	std::uniform_int_distribution<int>		intg(0, connections.size() - 1);
	std::uniform_real_distribution<double>		doubleg(-1, 1);

	auto it = connections.begin();
	std::next(it, intg(gene));
	(*it)->weight = doubleg(gene);
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

bool NeuralNetwork::save(std::string path) {
	std::ofstream out;
	out.open(path);
	if (!out.is_open())
		return false;

	out << nodes.size();
	for (auto &node : nodes) {
		node.second->save(out);
	}
	out << connections.size();
	for (auto &connection : connections) {
		connection->save(out);
	}

	return true;
}

bool NeuralNetwork::load(std::string path) {
	std::ifstream in;
	in.open(path);
	if (!in.is_open())
		return false;

	size_t size;
	in >> size;
	for (size_t i = 0; i < size; ++i) {
		SNode tmp(new Node());
		tmp->load(in);
		nodes[tmp->id] = tmp;
	}

	in >> size;
	for (size_t i = 0; i < size; ++i) {
		SConnection tmp(new Connection());
		tmp->load(in, *this);
		connections.push_back(tmp);

		nodes[tmp->from->id]->connectedTo.push_back(tmp);
		nodes[tmp->to->id]->connectedFrom.push_back(tmp);
	}

	return true;
}
