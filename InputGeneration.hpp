//
// Created by seb on 08/05/19.
//

#ifndef AI_INPUTGENERATION_HPP
#define AI_INPUTGENERATION_HPP


#include <string>
#include <fstream>
#include <random>

using Range = std::uniform_real_distribution<double>;

class InputGeneration {
public:
	InputGeneration() = delete;
	InputGeneration(const std::string &, const size_t &);

	void close();

	void createAgressives();
	void createCalm();
	void createEco();
	void createNonEco();

private:
	double getRandNumber(Range &range);

private:
	size_t		size;
	std::ofstream	agressive;
	std::ofstream	calm;
	std::ofstream	eco;
	std::ofstream	nonEco;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<double> rand;

};


#endif //AI_INPUTGENERATION_HPP
