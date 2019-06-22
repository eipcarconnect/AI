//
// Created by seb on 09/06/19.
//

#include <iostream>
#include "src/NeuralNetwork.hpp"

int main() {
	NNConfiguration config(3, 1, 2);
	NeuralNetwork neat(config);
	std::vector<double> in = {0.5, 0.5, 0.5};

	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();

	neat.setInput(in);
	neat.update();
	auto out = neat.getOutput();

	for (const auto &item : out) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	for (const auto &item : neat.connections) {
		std::cout << item->from->id << '-' << item->to->id << std::endl;
	}
}