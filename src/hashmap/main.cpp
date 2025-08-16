#include <iostream>
#include "hashmap.hpp"

using namespace std;


int main(int argc, char ** argv)
{
    HashMap<string, int> map;
    map.insert("2", 2);
    map.insert("3", 3);
    map.insert("4", 4);
    map.insert("5", 5);
    map.insert("6", 6);
    map.insert("7", 7);
    map.insert("8", 8);
    map.insert("9", 9);
    map.insert("10", 10);
    map.insert("1", 1);
    map.insert("11", 11);
    map.insert("12", 12);
    map.insert("13", 13); // this will trigger rehashing

    


    map.printSorted();
}