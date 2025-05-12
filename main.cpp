#include "hashtable.h"
#include <iostream>

int main() {
    HashTable ht(5); // Create hash table with size 5
    
    // Insert test data
    ht.insert(5);
    ht.insert(15);
    ht.insert(25);
    ht.insert(35);
    ht.insert(45);
    ht.insert(55); // This should trigger rehashing
    
    // Display table contents
    ht.display();
    
    // Test search functionality
    std::cout << "\nSearch Results:" << std::endl;
    std::cout << "15: " << (ht.search(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "20: " << (ht.search(20) ? "Found" : "Not Found") << std::endl;

    // Test deletion
    ht.remove(15);
    ht.remove(25);
    
    // Display after deletions
    ht.display();
    
    // Insert more data
    ht.insert(65);
    ht.insert(75);
    
    // Final display
    ht.display();

    return 0;
}