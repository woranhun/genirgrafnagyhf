/**
 * @file
 * @brief matrix header
 */

#ifndef GENIRGRAFNAGYHF_MATRIX_H
#define GENIRGRAFNAGYHF_MATRIX_H
#include <iostream>
#include <fstream>
#include "memtrace.h"
/**
 * @class mátrix osztály
 * @brief mátrix osztály
 * @tparam T a mátrix adatainak típusa
 */
template<typename T>
class Matrix{
    /**
     * @param ymax a mátrix magassága
     * @param xmax a mátrix szélessége
     * @param p 2D tömbre mutató pointer. A mátrix mérete y*x. A mátrix pointereket tárol.
     */
    size_t ymax;
    size_t xmax;
    T*** p;
public:
    Matrix():ymax(0),xmax(0),p(NULL){};
    Matrix(size_t y, size_t x):ymax(y),xmax(x){
        p= new T**[y];
        for (size_t i = 0; i < y; ++i) {
            p[i]= new T*[x];
            for (size_t j = 0; j < x; ++j) {
                p[i][j]= new T();
            }
        }
    };
    Matrix(std::ifstream& file){
        readMatrixFromFile(file);
    }
    void deleteMatrix(){
        if(p!=NULL){
            for (size_t i = 0; i < ymax; ++i) {
                for(size_t j =0; j < xmax; ++j){
                    deleteCell(i,j);
                }
                delete[] p[i];
            }
            delete[] p;
        }
    }
    size_t getxmax(){return xmax;}
    size_t getymax(){return ymax;}
    T(& operator[](size_t i)){return p[i];}
    const T(& operator[](size_t i)const)[]{return p[i];}
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mx){
        if(mx.p==NULL) return os;
        for (size_t i = 0; i < mx.ymax; ++i) {
            for (size_t j = 0; j < mx.xmax; ++j) {
                os<< *mx.p[i][j];
                os<< ' ';
            }
            os<<std::endl;
        }
        os<< std::endl;
        return os;
    }
    void deleteRow(size_t y);
    void deleteColumn(size_t x);
    void addRow(size_t y);
    void addColoum(size_t x);
    void deleteCell(size_t y, size_t x){
        if(p[y][x]!=NULL) delete p[y][x];
    }
    void setData(size_t y, size_t x, T mire){
        if(y>=ymax||x>=xmax) throw std::out_of_range("y or x value is greater than the size of the matrix");
        if(p[y][x]!=NULL) delete p[y][x];
        p[y][x] = new T(mire);
    }
    void createMatrix(size_t y, size_t x){
        if(p!=NULL){
            deleteMatrix();
        }
        p= new T**[y];
        for (size_t i = 0; i < y; ++i) {
            p[i]= new T*[x];
            for (size_t j = 0; j < x; ++j) {
                p[i][j]= NULL;
            }
        }
        xmax=x;
        ymax=y;
    }
    std::ofstream& saveMatrixToFile(std::ofstream& file);
    std::ifstream& readMatrixFromFile(std::ifstream& file){
        if(!file.is_open()) throw std::runtime_error("Can't open file!");
        std::string line;
        std::stringstream ss;
        std::getline(file, line);
        ss<<line;
        int y,x;
        ss >> y>>x;
        createMatrix(y,x);
        for (size_t i = 0; i < y; ++i) {
            std::getline(file, line);
            std::stringstream ss2;
            ss2 <<line;
            for (size_t j = 0; j < x; ++j) {
                T t;
                ss2>>t;
                setData(i,j, t);// így jó lesz az indexelés

            }
        }
        return file;
    }
    ~Matrix(){
        deleteMatrix();
    }



};

#endif //GENIRGRAFNAGYHF_MATRIX_H
