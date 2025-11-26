#include "cpp-httplib/httplib.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace httplib;

struct Item {
    int id;
    string description;
    string location;
    string date;
    bool isLost; // true if lost item, false if found item

    Item(int i, const string& desc, const string& loc, const string& d, bool lost)
        : id(i), description(desc), location(loc), date(d), isLost(lost) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<vector<Item>> table;

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
    Server svr;
    HashTable tracker;

    svr.Post("/report", [&](const Request& req, Response& res) {
        auto body = req.body;
        // For simplicity, assume JSON parsing is done here (you can integrate a JSON library)
        // This is a placeholder for actual JSON parsing
        // Insert dummy item for demonstration
        tracker.insertItem(Item(1, "Sample Item", "Location A", "2024-01-01", true));
        res.status = 200;
        res.set_content("Item reported successfully", "text/plain");
    });

    svr.Post("/search", [&](const Request& req, Response& res) {
        auto body = req.body;
        // For simplicity, assume JSON parsing is done here (you can integrate a JSON library)
        // This is a placeholder for actual JSON parsing
        vector<Item> results = tracker.searchByDescription("Sample");
        string response = "Found " + to_string(results.size()) + " items";
        res.set_content(response, "text/plain");
    });

    cout << "Server started at http://localhost:18080\n";
    svr.listen("0.0.0.0", 18080);

    return 0;
}
