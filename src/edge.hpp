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
    size_t id; //!< Az él azonosítója
    Vertex<T>* src;//!< A forrás csúcs
    Vertex<T>* dst;//!< A cél csúcs
    bool connected;//!< Az él be van-e húzva
    double weight;//!< Az él súlya
public:
    /**
     * @brief Az Él default konstruktora
     */
    Edge():id(0),src(NULL),dst(NULL),connected(false),weight(1){};
    /**
     * @brief Az Él konstruktora
     * @param id Az Él id-je
     * @param src A forrás csúcsra mutató pointer
     * @param dst A cél csúcsra mutató pointer
     * @param connected Be van-e húzva az él?
     * @param weight Az éj súlya
     */
    Edge(size_t id,Vertex<T>* src,Vertex<T>* dst, bool connected=false,double weight=1):id(id),src(src),dst(dst),connected(connected),weight(weight){};
    /**
     * @brief Az Él copy konstruktora
     * @param e A másik él
     */
    Edge(const Edge<T>& e){
        *this=e;
    }
    /**
     * @brief Az Él értékadó operátora
     * @param e A másik él
     * @return A keletkezett él
     */
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
    /**
     * @brief visszadja az él IDjét
     * @return Az ID
     */
    size_t getID(){return id;}
    /**
     * @brief Visszadja, hogy az él be van-e húzva
     * @return igen/nem
     */
    bool isConnected(){return connected;}
    /**
     * @brief Visszadja az él forráscsúcsát
     * @return A csúcsra mutató pointer
     */
    Vertex<T>* getSource(){return this->src;}
    /**
     * @brief Visszadja az él célcsúcsát
     * @return A csúcsra mutató pointer
     */
    Vertex<T>* getDestination(){return this->dst;}
    /**
     * @brief Az él kiírása
     * @tparam F Az él típusa
     * @param os A kapott ostream
     * @param e A kapott él
     * @return A keletkezett ostream
     */
    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const Edge<F>& e);

};
/**
 * @brief Az él kiírása
 * @tparam F Az él típusa
 * @param os A kapott ostream
 * @param e A kapott él
 * @return A keletkezett ostream
 */
template<typename F>
std::ostream& operator<<(std::ostream& os, const Edge<F>& e){
    os<<e.name;
    return os;
}

#endif //GENIRGRAFNAGYHF_EDGE_HPP
