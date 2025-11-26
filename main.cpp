#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

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
    vector<list<Item>> table;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {
        // vector initialized with TABLE_SIZE default-constructed lists
    }

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

    void displayAll() {
        cout << "All Lost and Found Items:" << endl;
        for (const auto& chain : table) {
            for (const auto& item : chain) {
                cout << "ID: " << item.id
                     << ", Description: " << item.description
                     << ", Location: " << item.location
                     << ", Date: " << item.date
                     << ", Type: " << (item.isLost ? "Lost" : "Found") << endl;
            }
        }
    }
};

void printMenu() {
    cout << "\nLost and Found Tracker Menu:\n";
    cout << "1. Add Lost Item\n";
    cout << "2. Add Found Item\n";
    cout << "3. Search Item by ID\n";
    cout << "4. Search Item by Description\n";
    cout << "5. Display All Items\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    HashTable tracker;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 6) {
            cout << "Exiting Lost and Found Tracker. Goodbye!" << endl;
            break;
        }

        int id;
        string description, location, date;
        vector<Item> results;

        switch (choice) {
            case 1:
                cout << "Enter Lost Item ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Location: ";
                getline(cin, location);
                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);
                tracker.insertItem(Item(id, description, location, date, true));
                cout << "Lost item added successfully." << endl;
                break;

            case 2:
                cout << "Enter Found Item ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Location: ";
                getline(cin, location);
                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);
                tracker.insertItem(Item(id, description, location, date, false));
                cout << "Found item added successfully." << endl;
                break;

            case 3:
                cout << "Enter Item ID to search: ";
                cin >> id;
                cin.ignore();
                results = tracker.searchById(id);
                if (results.empty()) {
                    cout << "No items found with ID " << id << "." << endl;
                } else {
                    for (const auto& item : results) {
                        cout << "ID: " << item.id
                             << ", Description: " << item.description
                             << ", Location: " << item.location
                             << ", Date: " << item.date
                             << ", Type: " << (item.isLost ? "Lost" : "Found") << endl;
                    }
                }
                break;

            case 4:
                cout << "Enter Description keyword to search: ";
                getline(cin, description);
                results = tracker.searchByDescription(description);
                if (results.empty()) {
                    cout << "No items found matching description \"" << description << "\"." << endl;
                } else {
                    for (const auto& item : results) {
                        cout << "ID: " << item.id
                             << ", Description: " << item.description
                             << ", Location: " << item.location
                             << ", Date: " << item.date
                             << ", Type: " << (item.isLost ? "Lost" : "Found") << endl;
                    }
                }
                break;

            case 5:
                tracker.displayAll();
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
