#include <iostream>
#include "InputGeneration.hpp"

int main() {
	std::cout << "Hello, World!" << std::endl;

	InputGeneration inputGeneration("../inputs/", 10);
	inputGeneration.createAgressives();
	inputGeneration.createCalm();
	inputGeneration.createEco();
	inputGeneration.createNonEco();
	inputGeneration.close();

	return 0;
}