//
// Created by seb on 09/06/19.
//

#include <iostream>
#include "src/NeuralNetwork.hpp"

int main() {
	NNConfiguration config(3, 1, 2);
	NeuralNetwork neat(config);
	std::vector<double> in = {0.85, 0.2, -0.67};

	neat.createRandomConnection();

	neat.setInput(in);
	neat.update();
	auto out = neat.getOutput();

	for (const auto &item : out) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
}