//
// Created by woranhun on 2020. 04. 20..
//

#ifndef GENIRGRAFNAGYHF_VERTEX_H
#define GENIRGRAFNAGYHF_VERTEX_H
template<typename V>
class Vertex{
    size_t id;
    V data;
public:
    Vertex():id(0),data(V()){};
    Vertex(size_t id):id(id),data(V()){};
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
};


#endif //GENIRGRAFNAGYHF_VERTEX_H
