//
// Created by seb on 09/06/19.
//

#include <cmath>
#include "Node.hpp"

Node::Node() {

}

void Node::activate() {
	totalPower = 0;
	for (auto &item : connectedAt) {
		totalPower += item->getWeight();
	}
	activated = totalPower/(1.0 + fabs(totalPower));
}

double Node::getActivated() {
	return activated;
}

