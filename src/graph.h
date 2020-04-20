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
    Vertex<T>** verteces;
public:
    Graph():numofv(0),numofe(0),adjMatrix(Matrix<Edge<T> >()),verteces(NULL){};
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
                os<< g.adjMatrix[i][j].isConnected()<<" ";
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

    class VertexSet{
        Vertex<T>** data;
        size_t len;
    public:
        VertexSet():len(0),data(NULL){};
        VertexSet(size_t len):len(0),data(new Vertex<T>*[len]){};
        VertexSet(const VertexSet& vs){
            *this = vs;
        }
        VertexSet& operator=(const VertexSet& vs){
            if(this!=&vs){
                for (size_t i = 0; i < vs.len; ++i) {
                    data[i]=vs.data[i];
                    len=vs.len;
                }
            }
            return *this;
        }
        void add(Vertex<T>* v){
            data[len++]=v;
        }
        ~VertexSet(){
            delete[] data;
        }
    };

    /**
     * @brief Felsorolja a csúcs szomszédjait.
     * @param os ostream
     * @param v a kiválasztott csúcs
     * @return ostream
     */
    VertexSet* listNeighboursOfVertex(size_t v){
        VertexSet* vs = new VertexSet(numofv);
        for (size_t i = 0; i < numofv; ++i) {
            if(adjMatrix[v][i].isConnected()) vs->add(adjMatrix[v][i].getDestination());
        }
        return vs;
    }


    void readAdjMatrixFromFile(std::ifstream& file){
        Matrix<bool>m(file);
        adjMatrix = Matrix<Edge<T> >(m.getymax(),m.getxmax());
        verteces = new Vertex<T>*[m.getymax()];
        size_t idval=0;
        for (size_t i = 0; i < m.getymax(); ++i) {
            verteces[i]= new Vertex<T>(i);
            numofv++;
        }
        for (size_t i = 0; i < m.getymax(); ++i) {
            for (size_t j = 0; j < m.getxmax(); ++j) {
                adjMatrix.setData(i, j, Edge<T>(idval++, verteces[i],verteces[j],m[i][j]));
                if(m[i][j])numofe++;
            }
        }
    }
    ~Graph(){
        for (size_t i = 0; i < numofv; ++i) {
           delete verteces[i];
        }
        delete[] verteces;
    }
};

#endif //GENIRGRAFNAGYHF_GRAPH_H
