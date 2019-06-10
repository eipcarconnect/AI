//
// Created by seb on 09/06/19.
//

#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(NNConfiguration config) : config(config) {
	id = config.input + config.bias + config.output;

}

void NeuralNetwork::updateInput(std::vector<double> &newInputs) {

}
