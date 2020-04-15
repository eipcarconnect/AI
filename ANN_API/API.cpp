//
// Created by seb on 11/04/2020.
//

#include "API.hpp"

API::API(web::http::uri addr): m_listener(addr) {
	this->m_listener.support(web::http::methods::POST, [](web::http::http_request request){
		std::cout << request.extract_string().get() << std::endl;
//		Concurrency::streams::streambuf<uint8_t> oui;
//		request.body().read_to_end(oui);
//		std::cout << oui << std::endl;
		request.reply(web::http::status_codes::OK, "C EST LA P2T2 JACK");
	});
}
