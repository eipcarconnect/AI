//
// Created by seb on 09/06/19.
//

#include <iostream>
#include "generation.h"
#include <QCoreApplication>

#include <QTcpSocket>
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost(QHostAddress(QHostAddress::LocalHost), 4343);

    Generation gen(&socket, "EIP_AI");

    return a.exec();
}


/*int main(){
	NeuralNetwork neat(config);
	std::vector<double> in = {1, 0.26, -0.7825};

	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();
	neat.createRandomConnection();

	neat.setInput(in);
	neat.update();
	neat.save("test.dat");
	auto out = neat.getOutput();

	std::cout << "je suis un test" << std::endl;
	for (const auto &item : out) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
}*/
