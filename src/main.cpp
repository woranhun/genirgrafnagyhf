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
    std::ifstream m1f("m1.txt");
    Matrix<int> m1;
    m1.readMatrixFromFile(m1f);
    std::cout<<m1;
    return 0;
}
