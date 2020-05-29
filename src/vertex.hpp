/**
 * @file
 * @brief vertex header
 */

#ifndef GENIRGRAFNAGYHF_VERTEX_HPP
#define GENIRGRAFNAGYHF_VERTEX_HPP
#include "memtrace.h"
/**
 * @class Vertex
 * @brief A csúcs osztály
 * @tparam V
 */
template<typename V>
class Vertex{
    size_t id; //!< A csúcs azonosítója
    V data; //!< A csúcshoz tartozó adat
public:
    /**
     * @brief A csúcs default konstruktora
     */
    Vertex():id(0),data(V()){};
    /**
     * @brief A csúcs konstruktora
     * @param id a kapott azonosító
     */
    Vertex(size_t id):id(id){
        V* v = new V();
        data= *v;
        delete v;
    };
    /**
     * @brief A csúcs konstruktora
     * @param id A kapott azonosító
     * @param data A kapott adat
     */
    Vertex(size_t id, V& data):id(id),data(data){};
    /**
     * @brief A csúcs copy konstruktora
     * @param v A kapott csúcs
     */
    Vertex(const Vertex& v){
        *this=v;
    }
    /**
     * @brief A csúcs értékadó operátora
     * @param v A kapott csúcs
     * @return A keletkezett csúcs
     */
    Vertex& operator=(Vertex& v){
        if(this!=&v){
            this->id=id;
            this->data=data;
        }
        return *this;
    }
    /**
     * @brief Visszadja a csúcs azonosítóját
     * @return A csúcs azonosítója
     */
    size_t getID(){
        return id;
    }
    /**
     * @brief Beállítja a csúcs adatát a kapott értékre
     * @param d A kapott érték
     */
    void setData(V d){
        this->data=d;
    }
    /**
     * @brief Visszadja a csúcs adatát
     * @return A csúcs adata
     */
    V& getData(){
        return data;
    }
};


#endif //GENIRGRAFNAGYHF_VERTEX_HPP
