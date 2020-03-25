#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

int main(int, char**) {
    mongocxx::instance inst{};
    // mongocxx::client conn{mongocxx::uri{}};
    mongocxx::client conn{mongocxx::uri{"mongodb+srv://<userAccount>:<Password>@cluster0-o0m91.mongodb.net/test?retryWrites=<Boolean>&w=majority"}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "simple changes";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}