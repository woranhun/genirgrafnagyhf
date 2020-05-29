/**
 * @file
 * @brief graph.h header
 */

#ifndef GENIRGRAFNAGYHF_GRAPH_HPP
#define GENIRGRAFNAGYHF_GRAPH_HPP
#include <iostream>

#include "memtrace.h"

#include "matrix.hpp"
#include "edge.hpp"
#include "vertex.hpp"


/**
 * @class Graph
 * @brief Graph osztály
 * @tparam T a csúcsok típusa
 */
template<typename T>
class Graph{
    size_t numofv; //!< A csúcsok száma
    size_t numofe; //!< Az élek száma
    Matrix< Edge<T> > adjMatrix; //!< A gráfhoz tartozó szomszédsági mátrix
    Vertex<T>** verteces; //!< A gráfhoz tartozó csúcsok
    bool isDataUploaded; //!<A gráf fel van-e töltve adatokkal
public:
    /**
     * @brief Grapf default konstruktora
     */
    Graph():numofv(0),numofe(0),adjMatrix(Matrix<Edge<T> >()),verteces(NULL),isDataUploaded(false){};
    /**
     * @brief a Graph konstruktora fájlból
     * @param file a szomszédsági mátrix fájlja
     */
    Graph(std::ifstream& file){
        this->numofv=0;
        this->numofe=0;
        readAdjMatrixFromFile(file);
    }
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
    bool isConnectedGraph(){
        Graph<T>::BFSSet* ret = this->BFS();
        bool isConn= ret->getLen()==this->getNumberOfVertices();
        delete ret;
        return isConn;
    }
    /**
     * @brief Kirajzolja a gráf szomszédsági mátrixát.
     * @param os ostream
     * @param g a gráf
     * @return ostream
     */
    template<typename F>
    friend std::ostream& operator<<(std::ostream& os,Graph<F>& g);
    /**
     * @brief Beállít egy élet a megadott értékekre
     * @param y melyik sor
     * @param x a soron belül melyik elem
     * @param con az él be van-e húzva
     * @param src forráscsúcs
     * @param dst célcsúcs
     */
    void setEdge(size_t y, size_t x,bool con, Vertex<T>* src,Vertex<T>* dst){
        if(!this->adjMatrix[y][x]&&con)numofe++;
        else if(this->adjMatrix[y][x]&&!con) numofe--;
        adjMatrix[y][x]->connected = con;
        adjMatrix[y][x]->src=src;
        adjMatrix[y][x]->dst=dst;
    }
    /**
     * @class VertexSet
     * @brief Csúcsok halmazának tárolására alkalmas osztály
     */
    class VertexSet{
    protected:
        size_t len; //!< Vertex set aktuális mérete
        Vertex<T>** data; //!< Az adatokat tároló tömb
    public:
        /**
         *@brief A csúcshalmaz default konstruktora
         */
        VertexSet():len(0),data(NULL){};
        /**
         * @brief A csúcshalmaz méret alapján történő konstruktora. Itt a méret a halmaz méretét jelenti
         * @param len A halmaz mérete
         */
        VertexSet(size_t len):len(0),data(new Vertex<T>*[len]){};
        /**
         * @brief A halmaz copy ctorja
         * @param vs A halmaz, amit másolni szeretnénk.
         */
        VertexSet(const VertexSet& vs){
            *this = vs;
        }
        /**
         * @brief A halmaz = operatora
         * @param vs az egyenlőségjel jobb oldalán lévő halmazra mutató referencia
         * @return Az új halmaz
         */
        VertexSet& operator=(const VertexSet& vs){
            if(this!=&vs){
                for (size_t i = 0; i < vs.len; ++i) {
                    data[i]=vs.data[i];
                    len=vs.len;
                }
            }
            return *this;
        }
        /**
         * @brief visszaadja a kért csúcsot
         * @param index a csúcs id-je
         * @return a kért csúcs
         */
        Vertex<T>* getVertex(size_t index){
            return data[index];
        }
        /**
         * @brief visszaadja a set aktuális méretét
         * @return a méret
         */
        size_t getLen(){
            return len;
        }
        /**
         * @brief Hozzáad a halmazhoz egy új csúcsot
         * @param v a csúcsra mutató pointer
         */
        void add(Vertex<T>* v){
            data[len++]=v;
        }
        /**
         * @brief A halmaz osztály destruktora. A csúcsok felszabadítását a Gráf végzi.
         */
        virtual ~VertexSet(){
            delete[] data;
        }
    };
    /**
     * @class BFSSet
     * @brief BFS algoritmushoz készült tároló. A VerexSet-ből származik.
     */
    class BFSSet: public VertexSet{
        long* distance; //!<  csúcs távolsága a kezdőcsúcstól
        Vertex<T>** prevVertex; //!< Lista, amely minden csúcshoz hozzárendelő az őt megelőző csúcs azonosítóját
        size_t prevVertexLen; //!< Tárolja a lista aktuális méretét
    public:
        /**
         * @brief BFSSet default konstruktora
         */
        BFSSet():VertexSet(),distance(NULL),prevVertex(NULL),prevVertexLen(0){};
        /**
         * @brief Max méretet beállító konstruktora
         * @param len maximális méret
         */
        BFSSet(size_t len):VertexSet(len),prevVertex(new Vertex<T>*[len]),prevVertexLen(0){
            distance = new long[len];
            for (size_t i = 0; i < len; ++i) {
                distance[i]= -1;
            }
        };
        /**
         * @brief BFSSet másoló konstruktora
         * @param bs a másik BFSSet
         */
        BFSSet(const BFSSet& bs){
            *this= bs;
        }
        /**
         * @brief BFSSet értékadó operátora
         * @param bs a másik BFSSet
         * @return visszaadja a keletkezett BFSSetet
         */
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
        /**
         * @brief Beállítja a csúcs távolságát
         * @param kinek a megfelelő csúcs
         * @param mire a távolság érték
         */
        void setDistance(size_t kinek,long mire){
            distance[kinek]=mire;
        }
        /**
         * @brief Visszaadja a csúcs távolságát a kezdőponttól mérve
         * @param kinek a megfelelő csúcs
         * @return a távolság értéke
         */
        long getDistance(size_t kinek){
            return distance[kinek];
        }
        /**
         * @brief A PrevVertex listának a végéhez hozzáad egy elemet
         * @param v A hozzáadandó csúcsra mutató pointer
         */
        void addPrevVertex(Vertex<T>* v){
            prevVertex[prevVertexLen++]=v;
        }
        /**
         * @brief A BFSSet << operátora
         * @param os A kapott ostream
         * @param bfss A kapott BFSSet
         * @return A keletkezett ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const BFSSet& bfss){
            for (size_t i = 0; i < bfss.len; ++i) {
                os<< bfss.data[i]->getID()<<" ";
            }
            os<<std::endl;
            return os;
        }
        /**
         * @brief A BFSSet destruktora
         */
        ~BFSSet(){
            delete[] distance;
            delete[] prevVertex;
        }
    };
    /**
     * @brief Visszaad egy csúcsra mutató pointert, amit ID alapján határoz meg
     * @param id Az ID amit a felhasználótól kapunk
     * @return A csúcsra mutató pointer
     */
    Vertex<T>* getVertexFromID(size_t id){
        for (size_t i = 0; i < numofv; ++i) {
            if(verteces[i]->getID()==id) return verteces[i];
        }
        return NULL;
    }
    /**
     * @brief Visszadja a kapott ID alapján a megfelelő csúcshoz tartozó adatot
     * @param id A kapott ID
     * @return A csúcs adata
     */
    T getDataFromID(size_t id){
        return verteces[id]->getData();
    }
    /**
     * @brief BFS alkogritmus
     * @param honnan csúcs id, ahonnan az algoritmus indul
     * @return visszad egy BFSSet-re mutató pointert. A felszabadítás a felhasználó dolga.
     */
    BFSSet* BFS(size_t honnan=0){
        BFSSet* bfs = new BFSSet(getNumberOfVertices());
        size_t j =0; // eddig bejárt csúcsok száma
        size_t k =0; // jelenlegi katív csúcs sorszáma
        bfs->setDistance(honnan, 0);
        bfs->add(getVertexFromID(honnan));
        while(true){
            VertexSet* neighboursOfk =listNeighboursOfVertex(bfs->getVertex(k)->getID());
            for (size_t v = 0; v < neighboursOfk->getLen(); ++v) {
                if(bfs->getDistance(neighboursOfk->getVertex(v)->getID())==-1){
                    j++;
                    bfs->add(neighboursOfk->getVertex(v));
                    bfs->setDistance(neighboursOfk->getVertex(v)->getID(),bfs->getDistance(bfs->getVertex(k)->getID())+1);
                    bfs->addPrevVertex(bfs->getVertex(k));
                }
                if(v==neighboursOfk->getLen()-1){
                    if(j==k){
                        delete neighboursOfk;
                        return bfs;
                    }else k++;
                }
            }
            delete neighboursOfk;
        }
    }
    /**
     * @brief Megkeresi a kapott csúcs szomszédait
     * @param v  a kapott csúcs
     * @return VertexSet*-ot ad vissza. A felszabadítás a felhasználó dolga
     */
    VertexSet* listNeighboursOfVertex(size_t v){
        VertexSet* vs = new VertexSet(numofv);
        for (size_t i = 0; i < numofv; ++i) {
            if(adjMatrix[v][i].isConnected()) vs->add(adjMatrix[v][i].getDestination());
        }
        return vs;
    }
    /**
     * @brief Beolvas egy szomszédsági mátrixot és beállítja azt a gráfnak
     * @param file A file-ra mutató ifstream
     */
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
    /**
     * @brief Elmenti a szomszédsági mátrixot a megadott nevő fájlba.
     * @param file A kapott fájlnév
     */
    void saveAdjMatrixToFile(const std::string& file){
        adjMatrix.saveMatrixToFile(file);
    }
    /**
     * @brief Beolvassa a csúcs adatait fájlból
     * @param file A beolvasandó file
     */
    void readDataFromFile(std::ifstream& file){
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        for (size_t i = 0; i < numofv; ++i) {
            std::string line;
            std::stringstream ss;
            std::getline(file, line);
            ss << line;
            T tempdata;
            ss>> tempdata;
            verteces[i]->setData(tempdata);
        }
        isDataUploaded=true;
    }
    /**
     * @brief Beolvassa a csúcs adatait fájlból, majd meghívja miden soron a kapott függvényt.
     * @tparam FUNC A kapott függvény típusa
     * @param file A kapott file
     * @param f A kapott fügvény, amely létrehozza a T objektumot a kapott sor alapján.
     */
    template<class FUNC>
    void readDataFromFile(std::ifstream& file,FUNC f){
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        for (size_t i = 0; i < numofv; ++i) {
            std::string line;
            std::getline(file, line);
            T* tempptr = f(line);
            T tempdata = *tempptr;
            verteces[i]->setData(tempdata);
            delete tempptr;
        }
        isDataUploaded=true;
    }
    /**
     * @brief A gráf destruktora
     */
    ~Graph(){
        for (size_t i = 0; i < numofv; ++i) {
           delete verteces[i];
        }
        delete[] verteces;
    }
};
/**
 * @brief A gráf kiírását végző függvény
 * @tparam F A gráf ilyen adatokat tárol
 * @param os ostream referencia
 * @param g A kapott gráf
 * @return A keletkezett ostream referencia
 */
template<typename F>
std::ostream& operator<<(std::ostream& os,Graph<F>& g){
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
    if(g.isDataUploaded){
        os<<"A csucsokhoz tartozo adatok:"<<std::endl;
        for (size_t i = 0; i < g.adjMatrix.getxmax(); ++i) {
            os<<i<<"->"<< g.getDataFromID(i)<<"; ";
        }
    }
    os<<std::endl;

    return os;
};

#endif //GENIRGRAFNAGYHF_GRAPH_HPP
