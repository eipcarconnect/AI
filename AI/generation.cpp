#include "generation.h"
#include "../Helper/Config.hpp"

#include <QTimer>
#include <QTcpSocket>
#include <iostream>
#include <memory>

Generation::Generation(QTcpSocket *tcp, std::string name): name(name)
{
    auto timer = new QTimer(this);

    createGenaration();
    connect(timer, &QTimer::timeout, [tcp, this](){
        //TrainingNetMessage tmp("stat", 2.0, -2.0, 0.0);
        Stat tmp(2.0, -2.0, 0.0);
        std::vector<double> in = {1, 0.26, -0.7825};

        for (auto &elem : generation) {
            elem->setInput(in);
            elem->update();
            auto out = elem->getOutput();

            elem->fitnesse = out[0] + out[1];
        }

        generation.sort([](std::shared_ptr<NeuralNetwork> first, std::shared_ptr<NeuralNetwork> second){
            return first->fitnesse > second->fitnesse;
        });

        for (auto &elem : generation) {
            /*if (elem->fitnesse > tmp.stat.max)
                tmp.stat.max = elem->fitnesse;
            if (elem->fitnesse < tmp.stat.min)
                tmp.stat.min = elem->fitnesse;
            tmp.stat.moy += elem->fitnesse;*/
            if (elem->fitnesse > tmp.max)
                tmp.max = elem->fitnesse;
            if (elem->fitnesse < tmp.min)
                tmp.min = elem->fitnesse;
            tmp.moy += elem->fitnesse;
        }
        //tmp.stat.moy = tmp.stat.moy / 1000.0;
        tmp.moy = tmp.moy / this->size;
        //tcp->write((const char *) &tmp, sizeof(TrainingNetMessage));
        tcp->write((const char *) &tmp, sizeof(Stat));

        generation.sort([](const std::shared_ptr<NeuralNetwork> &first, const std::shared_ptr<NeuralNetwork> &second){return first->fitnesse < second->fitnesse;});
        for (auto &elem : generation) {
            if (elem->fitnesse < (*generation.begin())->fitnesse - 0.4)
                elem->randomiseConnectionWeight();
        }
    });
    connect(tcp, &QTcpSocket::readyRead, [tcp, this](){
        auto buffer = QString(tcp->readAll()).toStdString();
        std::cout << "Received message from SERVER: " << buffer<< std::endl;

        if (buffer == "save_ann") {
            auto best = generation.front();

            best->save(ANN_PATH);

            std::ifstream t(ANN_PATH);
            std::string str((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());
            TrainingNetMessage tmp(MessageType::Save, this->name, str);
            std::cout << "LOOK AT ME" << str << std::endl;
        }
    });
    timer->start(1000);
}

void Generation::createGenaration(int size) {
    this->size = size;
    NNConfiguration config(INPUT_SIZE,
                           BIAS_SIZE,
                           OUTPUT_SIZE);

    for (int i = 0; i < this->size; ++i) {
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
    Q_UNUSED(path)
}
