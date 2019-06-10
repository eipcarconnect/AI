//
// Created by seb on 09/06/19.
//

#include "Connection.hpp"
#include "Node.hpp"

Connection::Connection(std::shared_ptr<Node> &from, std::shared_ptr<Node> &to, double weight):
	from(from), to(to), weight(weight){
}

double Connection::getWeight() {
	return from->getActivated() * weight;
}
