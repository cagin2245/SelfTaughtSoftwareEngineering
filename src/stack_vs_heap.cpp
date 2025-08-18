#include <iostream>
using namespace std;

int main() {
    // STACK
    int stackArr[3] = {10, 20, 30};
    int* sp = stackArr;

    cout << "Stack adresleri:" << endl;
    for (int i=0; i<3; i++)
        cout << (sp+i) << " -> " << *(sp+i) << endl;

    // HEAP
    int* heapArr = new int[3]{100, 200, 300};
    int* hp = heapArr;

    cout << "\nHeap adresleri:" << endl;
    for (int i=0; i<3; i++)
        cout << (hp+i) << " -> " << *(hp+i) << endl;

    delete[] heapArr; // çok kritik
}
