//
// Created by seb on 11/04/2020.
//

#include <cpprest/details/basic_types.h>
#include <cpprest/uri_builder.h>

#include <memory>
#include "API.hpp"

int main () {
	utility::string_t port = U("34568");
	utility::string_t address = U("http://127.0.0.1:");
	std::unique_ptr<API> api;

	address.append(port);
	web::uri_builder uri(address);


	auto addr = uri.to_uri().to_string();
	api = std::make_unique<API>(addr);
	api->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);
	return 0;
}