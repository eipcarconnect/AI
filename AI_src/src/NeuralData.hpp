//
// Created by seb on 09/06/19.
//

#pragma once


#include <cstddef>

struct NNConfiguration {
	NNConfiguration() = delete;
	NNConfiguration(size_t input, size_t bias, size_t output): input(input), bias(bias), output(output) {}

	size_t	input;
	size_t	bias;
	size_t	output;

};