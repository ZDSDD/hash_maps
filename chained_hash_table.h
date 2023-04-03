//
// Created by User on 19.03.2023.
//

#ifndef PROJEKT_2_CHAINED_HASH_TABLE_H
#define PROJEKT_2_CHAINED_HASH_TABLE_H

#include <iostream>

static int chainedCounter{0};

// Linked List
template<typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node *next;

    Node(K key, V value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }

    Node(Node &obj) {
        this->key = obj.key;
        this->value = obj.value;
        this->next = nullptr;
    }

    ~Node() {
        Node *head = this;
        while (head != nullptr) {
            Node *currNode = head;
            head = head->next;
            delete currNode;
        }
    }
};

template<typename K, typename V>
class ChainedHashMap {
public:
    int numOfElements{}, capacity{};
    Node<K, V> **data;

    ChainedHashMap() {
        capacity = 1;
        numOfElements = 0;
        data = new Node<K, V> *[this->capacity];
        data[0] = nullptr;
    }

    float getLoadFactor() {
        if (capacity == 0)capacity++;
        return (float) (numOfElements + 1) / (float) (capacity);
        // number of elements in hash table / total numbers of buckets
    }

    void rehashingUp();

    void insert(K key, V value);

    V search(K key);

    void deleteKey(K key);

    void display() const;

    void rehashingDown();
};

template<typename K, typename V>
void ChainedHashMap<K, V>::deleteKey(K key) {
    if (search(key) == -1)return;
    if (numOfElements < (capacity) / 4) {
        this->rehashingDown();
    }
    size_t bucketIndex = std::hash<K>{}(key) % this->capacity;

    auto *n = data[bucketIndex];
    Node<K, V> *last = nullptr;
    numOfElements--;
    while (n != nullptr) {
        if (n->key == key) {
            if (last == nullptr) {
                data[bucketIndex] = n->next;
                return;

            } else {
                last->next = n->next;
                return;
            }
        }
        last = n;
        n = n->next;
    }
}

template<typename K, typename V>
void ChainedHashMap<K, V>::display() const {
    for (int i = 0; i < capacity; ++i) {
        auto *runner = data[i];
        if (data[i] != nullptr) {
            std::cout << '[' << data[i]->key << "]:";
        } else {
            std::cout << "[NULL] : ";
        }
        while (runner != nullptr) {
            std::cout << runner->value << " -> ";
            runner = runner->next;
        }
        std::cout << '\n';
    }
}

template<typename K, typename V>
void ChainedHashMap<K, V>::rehashingUp() {
    numOfElements = 0;
    int oldCapacity = this->capacity;
    Node<K, V> **temp = this->data; // temp is holding current array

    this->capacity = oldCapacity * 2;
    this->data = new Node<K, V> *[this->capacity]; // points to new array of doubled numOfElements

    for (int i = 0; i < this->capacity; i++) {
        data[i] = nullptr;
    }
    for (int i = 0; i < oldCapacity; i++) // copying all the previous values in new array
    {
        Node<K, V> *currBucketHead = temp[i];
        while (currBucketHead != nullptr) // copying whole linked list
        {
            this->insert(currBucketHead->key,
                         currBucketHead->value); // insert function have now updated hash function as capacity is doubled
            currBucketHead = currBucketHead->next;
        }
    }
    delete[] temp; // deleting old array from heap memory
}

template<typename K, typename V>
void ChainedHashMap<K, V>::rehashingDown() {
    numOfElements = 0;
    int oldCapacity = this->capacity;
    Node<K, V> **temp = this->data; // temp is holding current array

    this->capacity = oldCapacity / 2;
    this->data = new Node<K, V> *[this->capacity];

    for (int i = 0; i < this->capacity; i++) {
        data[i] = nullptr;
    }
    for (int i = 0; i < oldCapacity; i++) // copying all the previous values in new array
    {
        Node<K, V> *currBucketHead = temp[i];
        while (currBucketHead != nullptr) // copying whole linked list
        {
            this->insert(currBucketHead->key,
                         currBucketHead->value); // insert function have now updated hash function as capacity is doubled
            currBucketHead = currBucketHead->next;
        }
    }
    delete[] temp; // deleting old array from heap memory
}

template<typename K, typename V>
void ChainedHashMap<K, V>::insert(K key, V value) {

    if (this->getLoadFactor() > 40) {
        this->rehashingUp();
    }
    size_t bucketIndex = std::hash<K>{}(key) % this->capacity;

    auto *n = data[bucketIndex];
    Node<K, V> *last = nullptr;
    while (n != nullptr) {
        if (n->key == key) {
            n->value = value;
            return;
        }
        last = n;
        n = n->next;
    }
    numOfElements++;
    auto *newNode = new Node<K, V>(key, value);

    if (last == nullptr) {
        data[bucketIndex] = newNode;
    } else {
        last->next = newNode;
    }
}

template<typename K, typename V>
V ChainedHashMap<K, V>::search(K key) {
    size_t bucketIndex = std::hash<K>{}(key) % this->capacity;
    Node<K, V> *bucketHead = this->data[bucketIndex];
    while (bucketHead != nullptr) {
        chainedCounter++;
        if (bucketHead->key == key) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
    return -1;
}

#endif //PROJEKT_2_CHAINED_HASH_TABLE_H
