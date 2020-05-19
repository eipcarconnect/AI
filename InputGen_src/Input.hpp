//
// Created by seb on 08/05/19.
//

#pragma once

#include <fstream>


struct Input {
	Input() = default;
	Input(const double &speed, const double &acceleration, const double &wheelRotation):
		speed(speed),
		acceleration(acceleration),
		wheelRotation(wheelRotation) {
	};
	Input(const double speed, const double acceleration, const double wheelRotation):
		speed(speed),
		acceleration(acceleration),
		wheelRotation(wheelRotation) {
	};

	void save(std::ofstream &stream) {
		stream << this->speed << " ";
		stream << this->acceleration << " ";
		stream << this->wheelRotation << " ";
	}

	void load(std::ifstream &stream) {
		stream >> this->speed;
		stream >> this->acceleration;
		stream >> this->wheelRotation;
	}


	/// MAX SPEED 56 M/S -> 200 KM/H
	double	speed;
	/// MAX ACCELERATION 13 M/S²
	double	acceleration;
	/// MAX WHEEL ROTATION UNKNOWN -> -360° +360°
	double	wheelRotation;
};