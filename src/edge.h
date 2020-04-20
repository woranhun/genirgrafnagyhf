/**
 * @file
 * @brief vertex header
 */

#ifndef GENIRGRAFNAGYHF_EDGE_H
#define GENIRGRAFNAGYHF_EDGE_H
#include "memtrace.h"
/**
 * @class Csúcs osztály.
 * @brief Csúcs osztály.
 * @tparam T a csúcsok típusa
 */
template<typename T>
class Edge{
    /**
     * @param data a csúcs értékének tárolója
     * @param name a csúcs neve
     */
    T data;
    std::string name;
    bool connected;
    size_t id;
public:
    Edge(bool connected=false):data(T()),connected(connected),name(std::string()){};
    Edge(size_t id, bool connected=false):data(T()),id(id),connected(connected),name(std::string()){};

    Edge(const Edge<T>& v){
        *this=v;
    }
    Edge<T>& operator=(const Edge& v){
        if(this!=&v){
            this->data=v.data;
            this->name=v.name;
            this->connected=v.connected;
            this->id=v.id;
        }
        return *this;
    }
    /**
     * @brief Visszadja a csúcs értékét.
     * @return a visszadott adat
     */
    T getData(){return data;}
    /**
     * @brief Beállítja a csúcs értékét a megadottra.
     * @param mit az adat, amire állítjuk a csúcs értékét
     */
    void setData(T mit){data= T(mit);}
    size_t getId(){return id;}
    bool isConnected(){return connected;}
    std::string getName()const {return name;}
    void setName(const std::string& s){
        name=s;
    }
    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const Edge<F>& v){
        os<<v.name<<"A;";
        return os;
    }

};
#endif //GENIRGRAFNAGYHF_EDGE_H
