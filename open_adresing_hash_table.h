//
// Created by User on 20.03.2023.
//

#ifndef PROJEKT_2_OPEN_ADRESING_HASH_TABLE_H
#define PROJEKT_2_OPEN_ADRESING_HASH_TABLE_H

#include <iostream>

static int openAdresingCounter{0};

template<typename K, typename V>
class HashNode {
public:
    V value;
    K key;

    HashNode(K key, V value) {
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>
class OpenAdresingHashMap {
    HashNode<K, V> **data;
    int capacity;
    int numOfElements;
    HashNode<K, V> *dummy;


public:
    OpenAdresingHashMap() {
        // Initial capacity of hash array
        capacity = 20;
        numOfElements = 0;
        data = new HashNode<K, V> *[capacity];

        // Initialise all elements of array as NULL
        for (int i = 0; i < capacity; i++) {
            data[i] = nullptr;
        }

    }


    void insert(K key, V value);

    void deleteNode(K key);

    int scanFor(K key);

    V find(K key);

    int getCapacity() { return capacity; }

    int sizeofMap() { return numOfElements; }

    bool isEmpty() { return numOfElements == 0; }

    void display() const;

    HashNode<K, V> **newData(int newSize);
};

template<typename K, typename V>
HashNode<K, V> **OpenAdresingHashMap<K, V>::newData(int newSize) {

    auto NewData = new HashNode<K, V> *[newSize];
    for (int i = 0; i < newSize; i++) {
        NewData[i] = nullptr;
    }

    for (int i = 0; i < capacity; ++i) {
        if (data[i] != nullptr && data[i] != dummy) {
            auto key = data[i]->key;
            int firstIndex = std::hash<K>{}(key) % newSize;
            int s = 1;
            while (NewData[firstIndex] != nullptr) {
                firstIndex = (firstIndex + s) % newSize;
            }
            NewData[firstIndex] = data[i];
        }
    }
    capacity = newSize;
    return NewData;
}

template<typename K, typename V>
void OpenAdresingHashMap<K, V>::deleteNode(K key) {
    int i = scanFor(key);
    if (i != -1 && data[i] != nullptr && data[i] != dummy) {
        data[i] = dummy;
        numOfElements--;
        if (capacity > 1 &&
            (static_cast<double>(this->numOfElements * 4) < static_cast<double>(this->capacity) * 0.75)) {
            data = newData(capacity / 2);
        }
    }
}

template<typename K, typename V>
void OpenAdresingHashMap<K, V>::insert(K key, V value) {
    int i = scanFor(key);
    if (i == -1) {
        return;
    }
    auto newNode = new HashNode<K, V>(key, value);
    if (data[i] == nullptr || data[i] == dummy) {
        data[i] = newNode;
        numOfElements++;
        if (static_cast<double>(this->numOfElements * 1) > static_cast<double>(this->capacity) * 0.55) {
            data = newData(2 * capacity);
        }
    } else {
        data[i] = newNode;
    }
}

template<typename K, typename V>
V OpenAdresingHashMap<K, V>::find(K key) {
    int i = scanFor(key);
    if (i == -1 || data[i] == nullptr || data[i] == dummy) {
        return -1;
    }
    return data[i]->value;
}

template<typename K, typename V>
int OpenAdresingHashMap<K, V>::scanFor(K key) {

    int firstIndex = std::hash<K>{}(key) % capacity;
    int step = 1;
    int indexOfFirstDeletedCell = -1;
    int i = firstIndex;

    while (data[i] != nullptr) {
        openAdresingCounter++;
        if (data[i] == dummy) {
            if (indexOfFirstDeletedCell == -1) {
                indexOfFirstDeletedCell = i;
            }
        } else if (data[i]->key == key) {
            return i;
        }
        openAdresingCounter++;

        i = (i + step) % capacity;
        if (i == firstIndex) {
            return indexOfFirstDeletedCell;
        }
    }

    if (indexOfFirstDeletedCell != -1) {
        return indexOfFirstDeletedCell;
    }
    return i;
}

template<typename K, typename V>
void OpenAdresingHashMap<K, V>::display() const {
    for (int i = 0; i < capacity; i++) {
        if (data[i] != nullptr && data[i] != dummy) {
            std::cout << "key = " << data[i]->key << "  value = " << data[i]->value << std::endl;
        } else if (data[i] == dummy) {
            std::cout << "DUMMY " << "  value = DELETED" << std::endl;
        } else {
            std::cout << "NULL = " << "  value = NOTHING" << std::endl;
        }
    }
}

#endif //PROJEKT_2_OPEN_ADRESING_HASH_TABLE_H
