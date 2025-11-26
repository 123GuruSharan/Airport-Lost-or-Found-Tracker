#include "Crow/include/crow.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

struct Item {
    int id;
    string description;
    string location;
    string date;
    bool isLost; // true if lost item, false if found item
    string reportedBy;
    string contactInfo;
    string tags;
    string notes;

    Item(int i, const string& desc, const string& loc, const string& d, bool lost,
         const string& reportedBy = "", const string& contactInfo = "", const string& tags = "", const string& notes = "")
        : id(i), description(desc), location(loc), date(d), isLost(lost),
          reportedBy(reportedBy), contactInfo(contactInfo), tags(tags), notes(notes) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<Item>> table;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insertItem(const Item& item) {
        int index = hashFunction(item.id);
        table[index].push_back(item);
    }

    vector<Item> searchById(int id) {
        int index = hashFunction(id);
        vector<Item> results;
        for (const auto& item : table[index]) {
            if (item.id == id) {
                results.push_back(item);
            }
        }
        return results;
    }

    vector<Item> searchByDescription(const string& desc) {
        vector<Item> results;
        for (const auto& chain : table) {
            for (const auto& item : chain) {
                if (item.description.find(desc) != string::npos) {
                    results.push_back(item);
                }
            }
        }
        return results;
    }
};

int main() {
    crow::SimpleApp app;
    HashTable tracker;

    CROW_ROUTE(app, "/report").methods("POST"_method)([&tracker](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }
        int id = body["id"].i();
        string description = body["description"].s();
        string location = body["location"].s();
        string date = body["date"].s();
        bool isLost = body["isLost"].b();
        string reportedBy = body.has("reportedBy") ? string(body["reportedBy"].s()) : "";
        string contactInfo = body.has("contactInfo") ? string(body["contactInfo"].s()) : "";
        string tags = body.has("tags") ? string(body["tags"].s()) : "";
        string notes = body.has("notes") ? string(body["notes"].s()) : "";

        tracker.insertItem(Item(id, description, location, date, isLost, reportedBy, contactInfo, tags, notes));
        return crow::response(200, "Item reported successfully");
    });

    CROW_ROUTE(app, "/search").methods("POST"_method)([&tracker](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }
        vector<Item> results;
        if (body.has("id")) {
            int id = body["id"].i();
            results = tracker.searchById(id);
        } else if (body.has("description")) {
            string desc = body["description"].s();
            results = tracker.searchByDescription(desc);
        } else {
            return crow::response(400, "Missing search parameters");
        }

        crow::json::wvalue res;
        res["results"] = crow::json::wvalue::list();
        int index = 0;
        for (const auto& item : results) {
            crow::json::wvalue jitem;
            jitem["id"] = item.id;
            jitem["description"] = item.description;
            jitem["location"] = item.location;
            jitem["date"] = item.date;
            jitem["isLost"] = item.isLost;
            jitem["reportedBy"] = item.reportedBy;
            jitem["contactInfo"] = item.contactInfo;
            jitem["tags"] = item.tags;
            jitem["notes"] = item.notes;
            res["results"][index++] = std::move(jitem);
        }
        return crow::response(res);
    });

    // New test route for form-urlencoded data
    CROW_ROUTE(app, "/test_report").methods("POST"_method)([&tracker](const crow::request& req){
        auto params = crow::query_string(req.body);
        int id = std::stoi(params.get("id") ? params.get("id") : "0");
        std::string description = params.get("description") ? params.get("description") : "";
        std::string location = params.get("location") ? params.get("location") : "";
        std::string date = params.get("date") ? params.get("date") : "";
        bool isLost = params.get("isLost") ? (std::string(params.get("isLost")) == "true") : false;
        std::string reportedBy = params.get("reportedBy") ? params.get("reportedBy") : "";
        std::string contactInfo = params.get("contactInfo") ? params.get("contactInfo") : "";
        std::string tags = params.get("tags") ? params.get("tags") : "";
        std::string notes = params.get("notes") ? params.get("notes") : "";

        tracker.insertItem(Item(id, description, location, date, isLost, reportedBy, contactInfo, tags, notes));
        return crow::response(200, "Test item reported successfully");
    });

    // Serve static files
    CROW_ROUTE(app, "/")([](const crow::request& req){
        std::ifstream ifs("index.html");
        if (!ifs) {
            return crow::response(404);
        }
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        return res;
    });

    CROW_ROUTE(app, "/favicon.ico")([](){
        std::ifstream ifs("favicon.ico");
        if (!ifs) {
            return crow::response(404);
        }
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "image/x-icon");
        return res;
    });

    CROW_ROUTE(app, "/<string>")([](const crow::request& req, std::string filename){
        std::ifstream ifs(filename);
        if (!ifs) {
            return crow::response(404);
        }
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        crow::response res(buffer.str());
        if (filename.size() > 5 && filename.substr(filename.size() - 5) == ".html") {
            res.set_header("Content-Type", "text/html");
        } else if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".css") {
            res.set_header("Content-Type", "text/css");
        }
        return res;
    });


    app.port(18080).multithreaded().run();
}
