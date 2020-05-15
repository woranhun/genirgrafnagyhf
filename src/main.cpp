/**
 * @file
 * @brief main.cpp forrás
*/
#include <iostream>

#include "memtrace.h"



#include "graph.hpp"
#include "ember.h"
int main() {
    std::ifstream t1f("g1f.txt");
    std::ifstream t1fdata("g1data.txt");
    Graph<Ember> t1(t1f);
    t1.readDataFromFile(t1fdata,Ember::CreateEmber);
    t1.saveAdjMatrixToFile("g1save.txt");
    std::cout << t1;

    std::ifstream t2f("g2f.txt");
    std::ifstream t2fdata("g2fdata.txt");
    Graph<char> t2(t2f);
    t2.readDataFromFile(t2fdata);
    std::cout << t2;

    std::ifstream t3f("g5f.txt");
    Graph<char> t3(t3f);
    Graph<char>::BFSSet *ret = t3.BFS(4);
    std::cout << t3;
    std::cout << *ret;
    delete ret;

    std::ifstream t4af("g6af.txt");
    Graph<char> t4a(t4af);
    std::cout << t4a;
    std::cout << t4a.isConnectedGraph() << std::endl;

    std::ifstream t4bf("g6bf.txt");
    std::ifstream t4bfdata("g6bdata.txt");
    Graph<Ember> t4b(t4bf);
    t4b.readDataFromFile(t4bfdata,Ember::CreateEmber);
    std::cout << t4b;
    std::cout << t4b.isConnectedGraph() << std::endl;

    return 0;
}