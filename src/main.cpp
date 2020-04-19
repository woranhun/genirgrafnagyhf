/**
 * @file
 * @brief main.cpp forrás
*/
#include <iostream>
#include <fstream>

#include "memtrace.h"

#include "graph.h"
#include "matrix.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Graph<int> g1;
    std::ifstream g1f("g1.txt");
    g1.readAdjMatrixFromFile(g1f);
    std::cout<<g1;
    return 0;
}
