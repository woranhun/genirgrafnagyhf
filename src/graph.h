/**
 * @file
 * @brief graph.h header
 */

#ifndef GENIRGRAFNAGYHF_GRAPH_H
#define GENIRGRAFNAGYHF_GRAPH_H
#include <iostream>

#include "memtrace.h"

#include "matrix.h"
#include "vertex.h"


/**
 * @class Graph graph.h osztály
 * @brief Graph osztály
 * @tparam T a csúcsok típusa
 */
//template<typename T>
//class Graph{
//    /**
//     * @param v a csúcsok száma
//     * @param e az élek száma
//     * @param adjMatrix a gráfhoz tartozó szomszédsági mátrix
//     */
//    size_t v;
//    size_t e;
//    Matrix< Vertex<T> >* adjMatrix;
//public:
//    Graph():v(0),e(0),adjMatrix(new Matrix<Vertex<T> >){};
//    ~Graph(){
//        delete adjMatrix;
//    }
//    /**
//     * @brief Visszadja a csúcsok számát.
//     * @return csúcsok száma
//     */
//    size_t getNumberOfVertices(){return v;}
//    /**
//     * @brief Visszadja az élek számát.
//     * @return élek száma
//     */
//    size_t getNumberOfEdges(){return e;}
//    /**
//     * @brief Visszadja, hogy összefüggő-e a gráf, ehhez a BFS algoritmust fogja használni.
//     * @return összefüggő -e a gráf
//     */
//    bool isConnectedGraph();
//    /**
//     * @brief Kirajzolja a gráf szomszédsági mátrixát.
//     * @param os ostream
//     * @param g a gráf
//     * @return ostream
//     */
//    template<typename F>
//    friend std::ostream& operator<<(std::ostream& os,Graph<F>& g){
//        os<<*g.adjMatrix;
//        return os;
//    };
//    /**
//     * @brief Hozzáad egy csúcsot a gráfhoz.
//     * @param v a hozzáadandó gráf
//     * @return nincs
//     */
//    void addVertex(Vertex<T> v);
//    /**
//     * @brief Eltávolít egy csúcsot a gráfból
//     * @param v az eltávolítandó gráf
//     * @return nincs
//     */
//    void removeVertex(Vertex<T> v);
//    /**
//     * @brief Felsorolja a csúcs szomszédjait.
//     * @param os ostream
//     * @param v a kiválasztott csúcs
//     * @return ostream
//     */
//    std::ostream& showNeighboursOfVertex(std::ostream& os, Vertex<T> v);
//
//    void readAdjMatrixFromFile(std::ifstream& file){
//        if(adjMatrix!=NULL) delete adjMatrix;
//        adjMatrix = new Matrix<Vertex<T> >();
//        Matrix<bool>m(file);
//        for (size_t i = 0; i < m.getymax(); ++i) {
//            for (size_t j = 0; j < m.getxmax(); ++j) {
//                //if(m[i][j]) adjMatrix[i][j]=new Vertex<T>;
//            }
//        }
//    }
//};

#endif //GENIRGRAFNAGYHF_GRAPH_H
