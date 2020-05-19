#include <iostream>
#include "InputGeneration.hpp"

int main() {
	InputGeneration inputGeneration("../InputGen/inputs/", 1000000);
	inputGeneration.createAgressives();
	inputGeneration.createCalm();
	inputGeneration.createEco();
	inputGeneration.createNonEco();
	inputGeneration.close();

	return 0;
}