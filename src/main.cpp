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

    std::ifstream gf("g5f.txt");
    Graph<char> g;
    g.readAdjMatrixFromFile(gf);
    std::cout<<g;
    Graph<char>::BFSSet* ret = g.BFS(4,1);
    std::cout<<*ret;


    delete ret;

    return 0;
}
