/**
 * @file
 * @brief graph.h header
 */

#ifndef GENIRGRAFNAGYHF_GRAPH_H
#define GENIRGRAFNAGYHF_GRAPH_H
#include <iostream>

#include "memtrace.h"

#include "matrix.h"
#include "edge.h"
#include "vertex.h"


/**
 * @class Graph graph.h osztály
 * @brief Graph osztály
 * @tparam T a csúcsok típusa
 */
template<typename T>
class Graph{
    /**
     * @param v a csúcsok száma
     * @param e az élek száma
     * @param adjMatrix a gráfhoz tartozó szomszédsági mátrix
     */
    size_t numofv;
    size_t numofe;
    Matrix< Edge<T> > adjMatrix;
public:
    Graph():numofv(0),numofe(0),adjMatrix(Matrix<Edge<T> >()){};
    /**
     * @brief Visszadja a csúcsok számát.
     * @return csúcsok száma
     */
    size_t getNumberOfVertices(){return numofv;}
    /**
     * @brief Visszadja az élek számát.
     * @return élek száma
     */
    size_t getNumberOfEdges(){return numofe;}
    /**
     * @brief Visszadja, hogy összefüggő-e a gráf, ehhez a BFS algoritmust fogja használni.
     * @return összefüggő -e a gráf
     */
    bool isConnectedGraph();
    /**
     * @brief Kirajzolja a gráf szomszédsági mátrixát.
     * @param os ostream
     * @param g a gráf
     * @return ostream
     */
    template<typename F>
    friend std::ostream& operator<<(std::ostream& os,Graph<F>& g){
        os<<"vertices: "<<g.getNumberOfVertices()<<" ; edges: "<<g.getNumberOfEdges()<<std::endl;
        os<<"    ";
        for (size_t k = 0; k < g.adjMatrix.getxmax(); ++k) {
            os<<k<<" ";
        }
        os<<std::endl<<"  ";
        for (size_t k = 0; k < g.adjMatrix.getxmax(); ++k) {
            os<<"---";
        }
        os<<std::endl;
        for (size_t i = 0; i < g.adjMatrix.getxmax(); ++i) {
            os<<i<<" | ";
            for (size_t j = 0; j < g.adjMatrix.getymax(); ++j) {
                if(g.adjMatrix[i][j].isConnected()){
                    if(g.adjMatrix[i][j].getName()=="")os<<"1"<<" ";
                    else os<< g.adjMatrix[i][j].getName() << ' ';
                }
                else os<<"0"<<' ';
            }

            os<<std::endl;
        }
        return os;
    };
    /**
     * @brief Hozzáad egy csúcsot a gráfhoz.
     * @param v a hozzáadandó gráf
     * @return nincs
     */
    void addEdge(Edge<T> v);
    /**
     * @brief Eltávolít egy csúcsot a gráfból
     * @param v az eltávolítandó gráf
     * @return nincs
     */
    void removeEdge(Edge<T> v);
    /**
     * @brief Felsorolja a csúcs szomszédjait.
     * @param os ostream
     * @param v a kiválasztott csúcs
     * @return ostream
     */
    size_t* listNeighboursOfVertex(size_t v){
        size_t n=0;
        for (size_t i = 0; i < numofv; ++i) {
            if(adjMatrix[v][i].isConnected())n++;
        }
        size_t* ret = new size_t[n];
        size_t c=0;
        for (size_t j = 0; j < numofv; ++j) {
            if(adjMatrix[v][j].isConnected())ret[c++]=adjMatrix[v][j].getId();
        }
        return ret;
    };


    void readAdjMatrixFromFile(std::ifstream& file){
        Matrix<bool>m(file);
        adjMatrix = Matrix<Edge<T> >(m.getymax(),m.getxmax());
        size_t idval=0;
        for (size_t i = 0; i < m.getymax(); ++i) {
            numofv++;
            for (size_t j = 0; j < m.getxmax(); ++j) {
                adjMatrix.setData(i, j, Edge<T>(idval++, m[i][j]));
                if(m[i][j])numofe++;
            }
        }
        numofe=numofe/2;
    }

    Edge<T>& operator[](size_t id){
        for (size_t i = 0; i < numofv; ++i) {
            for (size_t j = 0; j < numofv; ++j) {
                if(adjMatrix[i][j].getId()==id)return adjMatrix[i][j];
            }
        }
    }
    const Edge<T>& operator[](size_t id)const{
        for (size_t i = 0; i < numofv; ++i) {
            for (size_t j = 0; j < numofv; ++j) {
                if(adjMatrix[i][j].getId()==id)return adjMatrix[i][j];
            }
        }
    }
};

#endif //GENIRGRAFNAGYHF_GRAPH_H
