#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <limits>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> isDeleted;
    int size;
    int count;
    static constexpr double A = 0.6180339887;
    static constexpr int EMPTY = std::numeric_limits<int>::min();
    static constexpr double MAX_LOAD_FACTOR = 0.7;

    int hash(int key) const;
    double loadFactor() const;
    bool needsRehash() const;

public:
    explicit HashTable(int tableSize);
    void insert(int key);
    bool search(int key) const;
    bool remove(int key);
    void display() const;
    void rehash();
};

#endif // HASHTABLE_H