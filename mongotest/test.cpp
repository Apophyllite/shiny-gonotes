#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
//#include "/usr/local/include/bsoncxx/v_noabi/bsoncxx/builder/stream/document.hpp"

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

int main(int, char**) {
	mongocxx::instance inst{};
	//"mongodb+srv://<username>:<password>@<cluster-url>/test?retryWrites=true&w=majority"
	//mongodb://writer:miaoji1109@10.19.130.163:27017/
	auto uri = mongocxx::uri{"mongodb://writer:miaoji1109@10.19.130.163:27017/?authSource=store"};
	std::cout << uri.auth_mechanism() << std::endl;
	//mongocxx::client conn{mongocxx::uri{"mongodb://writer:miaoji1109@10.19.130.163:27017/"}};
	mongocxx::client conn{uri};

	bsoncxx::builder::stream::document document{};

	auto collection = conn["store"]["classic_play_offline"];

	try {
		int i = 0;
		auto cursor = collection.find({});
		for (auto&& doc : cursor) {
			i++;
			std::cout << bsoncxx::to_json(doc) << std::endl;
			if (i > 1) return 0;
		}
		/*
		   auto cursor = collection.find_one({});

		   if (cursor) {
		   std::cout << bsoncxx::to_json(*cursor) << std::endl;
		   } else {
		   std::cout << "has error" << std::endl;
		   }
		*/
	} catch (const std::exception& xcp) {
		std::cout << "connection failed: " << xcp.what() << "\n";
		return 1;
	}
	return 0;
}
