#include "generation.h"

#include <QTimer>
#include <QTcpSocket>
#include <iostream>
#include <memory>

Generation::Generation(QTcpSocket *tcp)
{
    auto timer = new QTimer(this);

    createGenaration();
    auto it = generation.begin();
    std::cout << generation.size() << std::endl << std::endl;
    for (const auto &elem : (*it)->connections)
        std::cout << elem->weight << std::endl;
    std::cout << std::endl;
    ++it;
    for (const auto &elem : (*it)->connections)
        std::cout << elem->weight << std::endl;
    connect(timer, &QTimer::timeout, [tcp, this](){
        Stat tmp(2.0, -2.0, 0.0);
        std::vector<double> in = {1, 0.26, -0.7825};

        for (auto &elem : generation) {
            elem->setInput(in);
            elem->update();
            auto out = elem->getOutput();

            elem->fitnesse = out[0] + out[1];
        }

        for (auto &elem : generation) {
            if (elem->fitnesse > tmp.max)
                tmp.max = elem->fitnesse;
            if (elem->fitnesse < tmp.min)
                tmp.min = elem->fitnesse;
            tmp.moy += elem->fitnesse;
        }
        tmp.moy = tmp.moy / 1000.0;
        tcp->write((const char *) &tmp, sizeof(Stat));

        generation.sort([](const std::shared_ptr<NeuralNetwork> &first, const std::shared_ptr<NeuralNetwork> &second){return first->fitnesse < second->fitnesse;});
        for (auto &elem : generation) {
            if (elem->fitnesse < (*generation.begin())->fitnesse - 0.4)
                elem->randomiseConnectionWeight();
        }
    });
    timer->start(1000);
}

void Generation::createGenaration(int size) {
    NNConfiguration config(3, 1, 2);

    for (int i = 0; i < size; ++i) {
        std::shared_ptr<NeuralNetwork> tmp (std::make_shared<NeuralNetwork>(config));

        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();
        tmp->createRandomConnection();

        generation.emplace_back(tmp);
    }
}


/// TODO: implement load Data
void Generation::loadData(std::string path) {

}
