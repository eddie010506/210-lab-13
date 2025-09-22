#include <iostream>
#include <vector>
#include <fstream>
#include <numeric> // for std::accumulate
#include <algorithm> // for std::for_each, std::max_element, std::min_element
#include <stdexcept> 

using namespace std;

//  constant for the inventory size. 
const size_t INVENTORY_SIZE = 30;

// helper function to print the contents of the array
void printInventory(const vector<int>& vec, const string& title) {
    cout << "\n--- " << title << " ---\n";
    cout << "Book ID | Stock\n";
    cout << "----------------\n";
    int id = 0;
    for (const auto& stock : vec) {
        cout << "  " << id++ << "\t|   " << stock << "\n";
    }
    cout << "----------------\n";
}

int main() {
    //declare a std::array to hold the book inventory.
    vector<int> inventory;

    // read from the external data file into the array.
    ifstream inputFile("inventory.txt");
    if (!inputFile) {
        cout << "Error: Could not open inventory.txt" << endl;
        return 1;
    }

    int stockValue;
    while (inputFile >> stockValue) {
        inventory.push_back(stockValue);
    }
    inputFile.close();

    cout << "Successfully loaded initial inventory from file.";
    printInventory(inventory, "Initial Inventory Status");

    // using Member Functions to Simulate Bookstore Operations
    cout << "\n*** DEMONSTRATING STD::VECTOR MEMBER FUNCTIONS ***\n";

    // size(), capacity(), max_size(), and empty() - Basic Info
    cout << "\n1. Checking Inventory Capacity:\n";
    cout << "   - We carry " << inventory.size() << " different book titles.\n";
    cout << "   - Current memory allocation can hold " << inventory.capacity() << " titles before needing to reallocate.\n";
    cout << "   - The maximum possible titles we can carry is " << inventory.max_size() << ".\n";
    if (!inventory.empty()) {
        cout << "   - The inventory vector is not empty.\n";
    }

    

    // at() - Safely checking stock for a specific book ID
    cout << "\n2. Safely Checking Stock for Book ID 5:\n";
    try {
        cout << "   - Stock for Book ID 5: " << inventory.at(5) << "\n";
        cout << "   - Attempting to access an invalid Book ID (99)...\n";
        inventory.at(99); // This will throw an exception
    } catch (const out_of_range& e) {
        cout << "   - CAUGHT ERROR: " << e.what() << " - Invalid Book ID.\n";
    }

    // operator[] - Unsafe (but faster) access
    cout << "\n3. Unsafe Access for Book ID 10 (using []):\n";
    cout << "   - Stock for Book ID 10: " << inventory[10] << "\n";

    // front() and back() - Checking first and last books in the list
    cout << "\n4. Checking First and Last Book Stock:\n";
    cout << "   - Stock of the first book (ID 0): " << inventory.front() << "\n";
    cout << "   - Stock of the last book (ID " << INVENTORY_SIZE - 1 << "): " << inventory.back() << "\n";

    // Using iterators (begin(), end()) with STL algorithms
    cout << "\n5. Analyzing Inventory with Iterators:\n";
    int totalStock = accumulate(inventory.begin(), inventory.end(), 0);
    cout << "   - Total number of all books in store: " << totalStock << "\n";

    // Using const iterators (cbegin(), cend()) to find min/max
    auto maxIt = max_element(inventory.cbegin(), inventory.cend());
    auto minIt = min_element(inventory.cbegin(), inventory.cend());
    cout << "   - Highest stock count for a single book: " << *maxIt << "\n";
    cout << "   - Lowest stock count for a single book: " << *minIt << "\n";

    cout << "\n6. Printing Inventory in Reverse Order (Book ID " << INVENTORY_SIZE - 1 << " to 0):\n";
    for_each(inventory.rbegin(), inventory.rend(), [](int stock){
        cout << "   - Stock: " << stock << "\n";
    });

    cout << "\n7. Simulating a 'Special Edition' restock...\n";
    fill(inventory.begin(), inventory.end(), 50);
    printInventory(inventory, "Inventory After Filling with 50");

    // swap() - A new shipment arrives, and we swap out the entire inventory display
    cout << "\n8. A new shipment arrived! Swapping inventories...\n";
    vector<int> newShipment;
    newShipment.push_back(5); // The new shipment is much smaller
    newShipment.push_back(10);
    newShipment.push_back(15);
    
    inventory.swap(newShipment);

    printInventory(inventory, "Inventory After SWAP (Now showing tiny new shipment)");
    printInventory(newShipment, "Old 'Special Edition' Stock (Now in newShipment vector)");

    // clear() - Emptying the vector
    cout << "\n9. End of day sale! Everything sold out.\n";
    inventory.clear();
    cout << "   - Current number of titles: " << inventory.size() << "\n";
    if (inventory.empty()) {
        cout << "   - The inventory is now empty.\n";
    }

    return 0;
}