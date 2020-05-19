//
// Created by seb on 11/04/2020.
//

#ifndef ANN_API_API_HPP
#define ANN_API_API_HPP

#include <cpprest/http_listener.h>
#include <thread>
#include "../AI/src/NeuralNetwork.hpp"

class API {
public:
	API(web::http::uri addr);
	pplx::task<void>open(){return m_listener.open();}
	pplx::task<void>close(){return m_listener.close();}

	void update();

private:
	web::http::experimental::listener::http_listener m_listener;
    NNConfiguration config;
	NeuralNetwork ann;
    std::thread thread;
};


#endif //ANN_API_API_HPP
