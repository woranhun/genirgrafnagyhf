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
     * @brief Hozzáad egy élet a gráfhoz.
     * @param e a hozzáadandó él
     * @return nincs
     */
    void addEdge(Edge<T> e);
    /**
     * @brief Eltávolít egy élet a gráfból
     * @param e az eltávolítandó él
     * @return nincs
     */
    void removeEdge(Edge<T> e);

    class VertexSet{
    protected:
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
        Vertex<T>* getData(size_t index){
            return data[index];
        }
        size_t getLen(){
            return len;
        }
        void add(Vertex<T>* v){
            data[len++]=v;
        }
        virtual ~VertexSet(){
            delete[] data;
        }
    };
    class BFSSet: public VertexSet{
        long* distance;
        Vertex<T>** prevVertex;
        size_t prevVertexLen;
    public:
        BFSSet():VertexSet(),distance(NULL),prevVertex(NULL),prevVertexLen(0){};
        BFSSet(size_t len):VertexSet(len),prevVertex(new Vertex<T>*[len]),prevVertexLen(0){
            distance = new long[len];
            for (size_t i = 0; i < len; ++i) {
                distance[i]= -1;
            }
        };
        BFSSet(const BFSSet& bs){
            *this= bs;
        }
        BFSSet& operator=(const BFSSet& bs){
            if(this!=&bs){
                this->len=bs.len;
                for (size_t i = 0; i <bs.len; ++i) {
                    this->distance[i]=bs.distance[i];
                    this->prevVertex[i]=bs.prevVertex[i];
                    this->data[i]=bs.data[i];
                    this->prevVertexLen=bs.prevVertexLen;
                }
            }
            return *this;
        }

        void setDistance(size_t kinek,long mire){
            distance[kinek]=mire;
        }
        long getDistance(size_t kinek){
            return distance[kinek];
        }
        void addprevVertex(Vertex<T>* v){
            prevVertex[prevVertexLen++]=v;
        }
        friend std::ostream& operator<<(std::ostream& os, const BFSSet& bfss){
            for (size_t i = 0; i < bfss.len; ++i) {
                os<< bfss.data[i]->getID()<<" ";
            }
            os<<std::endl;
            return os;
        }
        ~BFSSet(){
            delete[] distance;
            delete[] prevVertex;
        }
    };

    Vertex<T>* getVertexFromID(size_t id){
        for (size_t i = 0; i < numofv; ++i) {
            if(verteces[i]->getID()==id) return verteces[i];
        }
        return NULL;
    }
    BFSSet* BFS(size_t honnan, size_t hova){
        // OPTIMALIZALNI KELL A KILEPEST
        BFSSet* bfs = new BFSSet(getNumberOfVertices());
        size_t j =0;
        size_t k =0;
        bfs->setDistance(honnan, 0);
        bfs->add(getVertexFromID(honnan));
        while(true){
            VertexSet* neighboursOfk =listNeighboursOfVertex(bfs->getData(k)->getID());
            for (size_t v = 0; v < neighboursOfk->getLen(); ++v) {
                int tmp=0;
                if(bfs->getDistance(neighboursOfk->getData(v)->getID())==-1){
                    tmp++;
                    j++;
                    bfs->add(neighboursOfk->getData(v));
                    bfs->setDistance(neighboursOfk->getData(v)->getID(),bfs->getDistance(bfs->getData(k)->getID())+1);
                    bfs->addprevVertex(bfs->getData(k));
                }
                //if(tmp==0&&v==neighboursOfk->getLen()-1){
                if(v==neighboursOfk->getLen()-1){
                    if(j==k){
                        delete neighboursOfk;
                        return bfs;
                    }else k++;
                }
            }
            delete neighboursOfk;
        }

        return bfs;
    }
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
