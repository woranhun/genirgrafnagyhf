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

    std::ifstream g1f("g1f.txt");
    Graph<char> g1;
    g1.readAdjMatrixFromFile(g1f);
    size_t* ret = g1.listNeighboursOfVertex(1);
    std::cout<<g1;

    std::cout<<g1[ret[0]].getId();

    delete[] ret;
    return 0;
}
