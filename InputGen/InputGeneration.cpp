//
// Created by seb on 08/05/19.
//

#include "InputGeneration.hpp"
#include "Input.hpp"
#include <iostream>

InputGeneration::InputGeneration(const std::string &folder, const size_t &size): size(size), rd(), gen(rd()){
	this->agressive.open(folder + "agressive.txt");
	if (!this->agressive.is_open()){
		std::cerr << "Couldn\'t open file \'" << folder + "agressive.txt" << "\' !";
		return ;
	}

	this->calm.open(folder + "calm.txt");
	if (!this->calm.is_open()){
		std::cerr << "Couldn\'t open file \'" << folder + "calm.txt" << "\' !";
		return ;
	}

	this->eco.open(folder + "eco.txt");
	if (!this->eco.is_open()){
		std::cerr << "Couldn\'t open file \'" << folder + "eco.txt" << "\' !";
		return ;
	}

	this->nonEco.open(folder + "noneco.txt");
	if (!this->nonEco.is_open()){
		std::cerr << "Couldn\'t open file \'" << folder + "noneco.txt" << "\' !";
		return ;
	}

}

void InputGeneration::close() {
	this->agressive.close();
	this->calm.close();
	this->eco.close();
	this->nonEco.close();
}

void InputGeneration::createAgressives() {
	Range speed(0.0, 1.0);
	Range acceleration(0.75, 1.0);
	Range wheel1(0.0, 0.45);
	Range wheel2(-0.45, 0.0);
	this->agressive << this->size << "\n";
	Input input;

	for (size_t i = 0; i < size / 2; ++i) {
		input.speed = getRandNumber(speed);
		input.acceleration = getRandNumber(acceleration);
		input.wheelRotation = getRandNumber(wheel1);
		input.save(this->agressive);

		this->agressive << "\n";
	}

	for (size_t i = 0; i < size / 2; ++i) {
		input.speed = getRandNumber(speed);
		input.acceleration = getRandNumber(acceleration);
		input.wheelRotation = getRandNumber(wheel2);
		input.save(this->agressive);

		this->agressive << "\n";
	}
}

void InputGeneration::createCalm() {
	Range speed(0.0, 0.65);
	Range acceleration(0.0, 0.25);
	Range wheel(-1.0, 1.0);
	this->calm << this->size << "\n";
	Input input;

	for (size_t i = 0; i < size; ++i) {
		input.speed = getRandNumber(speed);
		input.acceleration = getRandNumber(acceleration);
		input.wheelRotation = getRandNumber(wheel);
		input.save(this->calm);

		this->calm << "\n";
	}
}

void InputGeneration::createEco() {
	Range speed(0.0, 0.55);
	Range acceleration(0.0, 0.10);
	Range wheel(-1.0, 1.0);
	this->eco << this->size << "\n";
	Input input;

	for (size_t i = 0; i < size; ++i) {
		input.speed = getRandNumber(speed);
		input.acceleration = getRandNumber(acceleration);
		input.wheelRotation = getRandNumber(wheel);
		input.save(this->eco);

		this->eco << "\n";
	}
}

void InputGeneration::createNonEco() {
	Range speed(0.0, 1.0);
	Range acceleration(0.85, 0.10);
	Range wheel(-1.0, 1.0);
	this->nonEco << this->size << "\n";
	Input input;

	for (size_t i = 0; i < size; ++i) {
		input.speed = getRandNumber(speed);
		input.acceleration = getRandNumber(acceleration);
		input.wheelRotation = getRandNumber(wheel);
		input.save(this->nonEco);

		this->nonEco << "\n";
	}
}

double InputGeneration::getRandNumber(Range &range) {
	return (range(gen));
}


