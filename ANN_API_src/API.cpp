//
// Created by seb on 11/04/2020.
//

#include <iomanip>
#include "API.hpp"
#include "../Helper/Config.hpp"
#include "../AI_src/src/NeuralData.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

API::API(web::http::uri addr): m_listener(addr), config(INPUT_SIZE, BIAS_SIZE, OUTPUT_SIZE), ann(config), thread([this](){
    using std::chrono::system_clock;

    while (true) {
        std::time_t tt = system_clock::to_time_t (system_clock::now());
        struct std::tm * ptm = std::localtime(&tt);
        ptm->tm_hour = ptm->tm_min = ptm->tm_sec = 0;
        ++ptm->tm_mday;
        std::this_thread::sleep_until(system_clock::from_time_t (mktime(ptm)));
        this->update();
    }

}) {
	this->m_listener.support(web::http::methods::POST, [this](web::http::http_request request){
		std::cout << request.extract_string().get() << std::endl;
        Concurrency::streams::streambuf<uint8_t> oui;
        request.body().read_to_end(oui);
		std::cout << oui << std::endl;

		std::string data_raw;
		char c;
		while ((c = oui.sbumpc()) > 0)
		    data_raw += c;
		std::istringstream data(data_raw);

        std::vector<double> input;
        input.reserve(INPUT_SIZE);
        for (int i = 0; i < INPUT_SIZE; ++i) {
            double tmp;
            data >> tmp;
            input.push_back(tmp);
        }

        ann.setInput(input);
        ann.update();
        auto out = ann.getOutput();

        std::string output;
        std::ostringstream outputfs(output);

        for (auto const &elem: out)
            outputfs << elem << " ";

		request.reply(web::http::status_codes::OK, output);
	});
}

void API::update() {
    ann.load(ANN_PATH);
}

#pragma clang diagnostic pop