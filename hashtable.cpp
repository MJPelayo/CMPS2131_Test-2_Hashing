#include "hashtable.h"
#include <iostream>
#include <cmath>

HashTable::HashTable(int tableSize) : size(tableSize), count(0) {
    table.resize(size, EMPTY);
    isDeleted.resize(size, false);
}

int HashTable::hash(int key) const {
    double fractional = key * A - floor(key * A);
    return floor(size * fractional);
}

double HashTable::loadFactor() const {
    return static_cast<double>(count) / size;
}

bool HashTable::needsRehash() const {
    return loadFactor() > MAX_LOAD_FACTOR;
}

void HashTable::insert(int key) {
    if (needsRehash()) {
        rehash();
    }

    int index = hash(key);
    int originalIndex = index;
    int firstTombstone = -1;

    do {
        if (table[index] == EMPTY && !isDeleted[index]) {
            if (firstTombstone != -1) {
                index = firstTombstone;
            }
            table[index] = key;
            isDeleted[index] = false;
            count++;
            std::cout << "Inserted " << key << " at index " << index 
                      << " (Load factor: " << loadFactor() << ")" << std::endl;
            return;
        }
        else if (isDeleted[index] && firstTombstone == -1) {
            firstTombstone = index;
        }
        else if (table[index] == key && !isDeleted[index]) {
            std::cout << "Key " << key << " already exists at index " << index << std::endl;
            return;
        }

        index = (index + 1) % size;
    } while (index != originalIndex);

    if (firstTombstone != -1) {
        table[firstTombstone] = key;
        isDeleted[firstTombstone] = false;
        count++;
        std::cout << "Inserted " << key << " at tombstone index " << firstTombstone << std::endl;
    }
    else {
        std::cout << "Hash table is full! Rehashing..." << std::endl;
        rehash();
        insert(key);
    }
}

bool HashTable::search(int key) const {
    int index = hash(key);
    int originalIndex = index;

    do {
        if (table[index] == key && !isDeleted[index]) {
            return true;
        }
        if (table[index] == EMPTY && !isDeleted[index]) {
            return false;
        }
        index = (index + 1) % size;
    } while (index != originalIndex);

    return false;
}

bool HashTable::remove(int key) {
    int index = hash(key);
    int originalIndex = index;

    do {
        if (table[index] == key && !isDeleted[index]) {
            isDeleted[index] = true;
            count--;
            std::cout << "Deleted " << key << " from index " << index << std::endl;
            return true;
        }
        if (table[index] == EMPTY && !isDeleted[index]) {
            return false;
        }
        index = (index + 1) % size;
    } while (index != originalIndex);

    return false;
}

void HashTable::display() const {
    std::cout << "\nHash Table Contents (Size: " << size 
              << ", Count: " << count 
              << ", Load factor: " << loadFactor() << "):" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ": ";
        if (isDeleted[i]) {
            std::cout << "DELETED";
        }
        else if (table[i] == EMPTY) {
            std::cout << "EMPTY";
        }
        else {
            std::cout << table[i];
        }
        std::cout << std::endl;
    }
}

void HashTable::rehash() {
    std::vector<int> oldEntries;
    for (int i = 0; i < size; i++) {
        if (table[i] != EMPTY && !isDeleted[i]) {
            oldEntries.push_back(table[i]);
        }
    }

    size *= 2;
    table.assign(size, EMPTY);
    isDeleted.assign(size, false);
    count = 0;

    for (int key : oldEntries) {
        insert(key);
    }
    std::cout << "Rehashed table to size " << size << std::endl;
}