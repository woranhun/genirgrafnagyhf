/**
 * @file
 * @brief edge header
 */

#ifndef GENIRGRAFNAGYHF_EDGE_HPP
#define GENIRGRAFNAGYHF_EDGE_HPP
#include "memtrace.h"

#include "vertex.hpp"
/**
 * @class Edge
 * @brief Él osztály.
 * @tparam T az élek típusa
 */
template<typename T>
class Edge{
    /**
     * @param id az él azonosítója
     * @param src A forrás csúcs
     * @param dst A cél csúcs
     * @param connected Az él be van-e húzva
     * @param weight Az él súlya
     */
    size_t id;
    Vertex<T>* src;
    Vertex<T>* dst;
    bool connected;
    double weight;
public:
    Edge():id(0),src(NULL),dst(NULL),connected(false),weight(1){};
    Edge(size_t id,Vertex<T>* src,Vertex<T>* dst, bool connected=false,double weight=1):id(id),src(src),dst(dst),connected(connected),weight(weight){};
    Edge(const Edge<T>& e){
        *this=e;
    }
    Edge<T>& operator=(const Edge& e){
        if(this!=&e){
            this->connected=e.connected;
            this->id=e.id;
            this->src=e.src;
            this->dst=e.dst;
            this->weight=e.weight;
        }
        return *this;
    }
    size_t getID(){return id;}
    bool isConnected(){return connected;}
    Vertex<T>* getSource(){return this->src;}
    Vertex<T>* getDestination(){return this->dst;}
    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const Edge<F>& v);

};
template<typename F>
std::ostream& operator<<(std::ostream& os, const Edge<F>& v){
    os<<v.name;
    return os;
}

#endif //GENIRGRAFNAGYHF_EDGE_HPP
