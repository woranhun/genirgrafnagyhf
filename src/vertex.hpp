//
// Created by woranhun on 2020. 04. 20..
//

#ifndef GENIRGRAFNAGYHF_VERTEX_HPP
#define GENIRGRAFNAGYHF_VERTEX_HPP
#include "memtrace.h"
template<typename V>
class Vertex{
    size_t id;
    V data;
public:
    Vertex():id(0),data(V()){};
    Vertex(size_t id):id(id){
        V* v = new V();
        data= *v;
        delete v;
    };
    Vertex(size_t id, V& data):id(id),data(data){};
    Vertex(const Vertex& v){
        *this=v;
    }
    Vertex& operator=(Vertex& v){
        if(this!=&v){
            this->id=id;
            this->data=data;
        }
        return *this;
    }
    size_t getID(){
        return id;
    }
    /**
     * @bug UML-re felrakni
     *
     */
    void setData(V d){
        this->data=d;
    }
    /**
     * @bug UML-re felrakni
     * @return
     */
    V& getData(){
        return data;
    }
};


#endif //GENIRGRAFNAGYHF_VERTEX_HPP
