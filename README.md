# Hash Table Implementation in C++

This project implements a hash table using open addressing with linear probing and rehashing capabilities.

## Features

- **Open Addressing** with linear probing collision resolution
- **Tombstone handling** for deleted elements
- **Automatic rehashing** when load factor exceeds 0.7
- **Multiplicative hash function** using the golden ratio constant
- Comprehensive operations:
  - Insertion with collision handling
  - Search functionality
  - Deletion with tombstone marking
  - Table display for debugging

## Files

1. `hashtable.h` - Header file containing class definition and constants
2. `hashtable.cpp` - Implementation of hash table operations
3. `main.cpp` - Demonstration program showing usage

## How It Works

- The hash table uses a multiplicative hash function: `hash(key) = floor(size * (key * A - floor(key * A)))` where A is the golden ratio constant
- When inserting:
  - Checks for existing keys
  - Uses tombstones from previous deletions
  - Triggers rehash when load factor > 0.7
- Rehashing doubles the table size and reinserts all active elements

# Build and Run

g++ tokenizer.h tokenizer.cpp main.cpp -o calculator
./calculator
## Usage Example

```cpp
HashTable ht(5); // Create table with initial size 5

ht.insert(5);    // Insert values
ht.insert(15);
ht.insert(25);

ht.search(15);   // Returns true
ht.remove(15);   // Marks as deleted
ht.display();    // Shows current table state