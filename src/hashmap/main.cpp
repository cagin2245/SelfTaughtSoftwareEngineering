#include <iostream>
#include "hashmap.hpp"

using namespace std;


int main(int argc, char ** argv)
{
    HashMap<string, int> map;
    map.insert("2",3.345);
    map.insert("3",4);    
    map.insert("4",5);

    map.print();
}