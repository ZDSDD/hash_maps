#include <iostream>
#include <fstream>
#include <random>
#include "chained_hash_table.h"
#include "open_adresing_hash_table.h"

using std::cout;
using std::endl;

int main() {

    ///RANDOM NUMBER GENERATOR SETTINGS
    std::random_device rd;
    std::mt19937::result_type seed = rd();
    std::mt19937 gen(seed);
    std::uniform_int_distribution randomNumber(1, 100000000);
    ///RANDOM NUMBER GENERATOR SETTINGS

    ChainedHashMap<int, int> chainedMap;
    OpenAdresingHashMap<int, int> openMap;

    std::ofstream to_save_chain("chained.txt");
    std::ofstream to_save_open("open.txt");
    int i{1};
    while (chainedMap.numOfElements < 1000000) {
        int oldSize = chainedMap.numOfElements;
        int key{};
        int value{};

        ///Inserting element to the maps
        while (oldSize == chainedMap.numOfElements) {
            key = randomNumber(gen) % 10000000;
            value = randomNumber(gen);
            chainedMap.insert(key, value);
        }
        oldSize = openMap.sizeofMap();
        while (oldSize == openMap.sizeofMap()) {
            key = randomNumber(gen) % 10000000;
            value = randomNumber(gen);
            openMap.insert(key, value);
        }
        ///Inserting element to the maps

        key = randomNumber(gen) % 10000000;
        chainedCounter = 0;
        openAdresingCounter = 0;
        chainedMap.search(key);
        openMap.find(key);
        to_save_chain << i << ' ' << chainedCounter << ' ' << chainedMap.capacity << endl;
        to_save_open << i << ' ' << openAdresingCounter << ' ' << openMap.getCapacity() << endl;
        i++;
        //cout << i << ' ';
    }
    return 0;
}