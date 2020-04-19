/**
 * @file
 * @brief vertex header
 */

#ifndef GENIRGRAFNAGYHF_VERTEX_H
#define GENIRGRAFNAGYHF_VERTEX_H
#include "memtrace.h"
/**
 * @class Csúcs osztály.
 * @brief Csúcs osztály.
 * @tparam T a csúcsok típusa
 */
template<typename T>
class Vertex{
    /**
     * @param data a csúcs értékének tárolója
     * @param name a csúcs neve
     */
    T* data;
    std::string name;
public:
    Vertex():data(new T){};
    /**
     * @brief Visszadja a csúcs értékét.
     * @return a visszadott adat
     */
    T getData(){return *data;};
    /**
     * @brief Beállítja a csúcs értékét a megadottra.
     * @param mit az adat, amire állítjuk a csúcs értékét
     */
    void setData(T mit){data=new T(mit);};

    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const Vertex<F>& v){
        os<<v.name;
        return os;
    }
    ~Vertex(){
        delete data;
    }


};
#endif //GENIRGRAFNAGYHF_VERTEX_H
