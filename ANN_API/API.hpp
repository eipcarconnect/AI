//
// Created by seb on 11/04/2020.
//

#ifndef ANN_API_API_HPP
#define ANN_API_API_HPP

#include <cpprest/http_listener.h>

class API {
public:
	API(web::http::uri addr);
	pplx::task<void>open(){return m_listener.open();}
	pplx::task<void>close(){return m_listener.close();}

private:
	web::http::experimental::listener::http_listener m_listener;
};


#endif //ANN_API_API_HPP
