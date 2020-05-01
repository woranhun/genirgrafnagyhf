/**
 * @file
 * @brief main.cpp forrás
*/
#include <iostream>
#include <fstream>

#include "memtrace.h"
#include "gtest_lite.h"



#include "graph.h"
#include "matrix.h"

//gtest-t fordítási hibát dobott! ezért kivettem belőle.

/*
int main() {
    GTINIT(std::cin);       // Csak C(J)PORTA működéséhez kell
    TEST(Test1,  beolvasas){
        std::ifstream t1f("g1f.txt");
        std::ostringstream oss;
        Graph<char> t1(t1f);
        oss<<t1;
        EXPECT_EQ("vertices: 3 ; edges: 4\n"
                  "    0 1 2 \n"
                  "  ---------\n"
                  "0 | 0 1 0 \n"
                  "1 | 1 0 1 \n"
                  "2 | 0 1 0 \n",oss.str());
    }ENDM
    TEST(Test2, EdgesVerteces){
        std::ifstream t2f("g2f.txt");
        Graph<char> t2(t2f);
        EXPECT_EQ((size_t)6,t2.getNumberOfVertices());
        EXPECT_EQ((size_t)10,t2.getNumberOfEdges());

    }ENDM
    TEST(Test3,BFS){
        std::ifstream t3f("g5f.txt");
        std::ostringstream oss;
        Graph<char> t3(t3f);
        Graph<char>::BFSSet* ret = t3.BFS(4,1);
        oss<<*ret;
        EXPECT_EQ("4 0 1 5 2 7 6 3 \n",oss.str());
        delete ret;
    }ENDM
    TEST(Test4,osszefuggoe){
        std::ifstream t4af("g6af.txt");
        Graph<char> t4a(t4af);
        EXPECT_EQ(true,t4a.isConnectedGraph());

        std::ifstream t4bf("g6bf.txt");
        Graph<char> t4b(t4bf);
        EXPECT_EQ(false,t4b.isConnectedGraph());

    }ENDM

    GTEND(std::cerr);       // Csak C(J)PORTA működéséhez kell
    return 0;
}
*/
int main() {
    std::ifstream t1f("g1f.txt");
    Graph<char> t1(t1f);
    std::cout << t1;

    std::ifstream t2f("g2f.txt");
    Graph<char> t2(t2f);
    std::cout << t2.getNumberOfVertices() << std::endl;
    std::cout << t2.getNumberOfEdges() << std::endl;

    std::ifstream t3f("g5f.txt");
    Graph<char> t3(t3f);
    Graph<char>::BFSSet *ret = t3.BFS(4, 1);
    std::cout << *ret;
    delete ret;

    std::ifstream t4af("g6af.txt");
    Graph<char> t4a(t4af);
    std::cout << t4a.isConnectedGraph() << std::endl;

    std::ifstream t4bf("g6bf.txt");
    Graph<char> t4b(t4bf);
    std::cout << t4b.isConnectedGraph() << std::endl;

    return 0;
}