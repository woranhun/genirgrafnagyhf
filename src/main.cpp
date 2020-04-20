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

    std::ifstream g2f("g2f.txt");
    Graph<char> g2;
    g2.readAdjMatrixFromFile(g2f);
    Graph<char>::VertexSet* ret = g2.listNeighboursOfVertex(1);

    std::cout<<g2;

    delete ret;
    return 0;
}
