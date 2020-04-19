/**
 * @file
 * @brief matrix header
 */

#ifndef GENIRGRAFNAGYHF_MATRIX_H
#define GENIRGRAFNAGYHF_MATRIX_H

#include <iostream>
#include <fstream>
#include "memtrace.h"

template<typename T>
class Matrix;

template<typename T>
class MatrixRow;


/**
 * @class mátrix osztály
 * @brief mátrix osztály
 * @tparam T a mátrix adatainak típusa
 */
template<typename T>
class Matrix {
protected:
    /**
     * @param ymax a mátrix magassága
     * @param xmax a mátrix szélessége
     * @param p 2D tömbre mutató pointer. A mátrix mérete y*x. A mátrix pointereket tárol.
     */
    size_t ymax;
    size_t xmax;
    MatrixRow<T> *rows;
public:
    Matrix() : ymax(0), xmax(0), rows(NULL) {};

    Matrix(size_t y, size_t x) : ymax(y), xmax(x) {
        rows = new MatrixRow<T>[y];
        for (size_t i = 0; i < y; ++i) {
            rows[i] = MatrixRow<T>(xmax);
        }
        xmax = x;
        ymax = y;
    };

    Matrix(std::ifstream &file) {
        *this = readMatrixFromFile(file);
    }

    Matrix(const Matrix<T> &m) {
        *this = m;
    }

    Matrix<T> &operator=(const Matrix<T> &m) {
        if (this != &m) {
            delete[] rows;
            rows = new MatrixRow<T>[m.ymax];
            for (size_t i = 0; i < m.ymax; ++i) {
                rows[i] = MatrixRow<T>(m.rows[i]);
            }
            xmax = m.xmax;
            ymax = m.ymax;
        }
        return *this;
    }

    size_t getxmax() { return xmax; }

    size_t getymax() { return ymax; }

    MatrixRow<T> &operator[](size_t i) { return rows[i]; }

    const MatrixRow<T> &operator[](size_t i) const { return rows[i]; }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mx) {
        if (mx.rows == NULL) return os;
        for (size_t i = 0; i < mx.ymax; ++i) {
            for (size_t j = 0; j < mx.xmax; ++j) {
                os << mx.rows[i][j];
                os << ' ';
            }
            os << std::endl;
        }
        os << std::endl;
        return os;
    }

    void deleteRow(size_t y);

    void deleteColumn(size_t x);

    void addRow(size_t y);

    void addColoum(size_t x);

    void deleteCell(size_t y, size_t x) {
        rows[y][x] = T();
    }

    void setData(size_t y, size_t x, T mire) {
        rows[y][x] = T(mire);
    }

    std::ofstream &saveMatrixToFile(std::ofstream &file);

    std::ifstream &readMatrixFromFile(std::ifstream &file) {
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        std::string line;
        std::stringstream ss;
        std::getline(file, line);
        ss << line;
        int y, x;
        ss >> y >> x;
        *this = Matrix<T>(y, x);
        for (size_t i = 0; i < y; ++i) {
            std::getline(file, line);
            std::stringstream ss2;
            ss2 << line;
            for (size_t j = 0; j < x; ++j) {
                T t;
                ss2 >> t;
                setData(i, j, t);// így jó lesz az indexelés

            }
        }
        return file;
    }

    ~Matrix() {
            delete[] rows;
    }
};

template<typename T>
class MatrixRow {
    T *data;
    size_t xmax;
public:
    MatrixRow() : data(NULL), xmax(0) {};

    MatrixRow(size_t x) : xmax(x) {
        data = new T[x];
        for (size_t i = 0; i < x; ++i) {
            data[i] = T();
        }
    };

    MatrixRow(const MatrixRow<T> &mr) {
        //megdoglik
        xmax = mr.xmax;
        *this = mr;
    }

    MatrixRow<T> &operator=(const MatrixRow<T> &mr) {
        xmax = mr.xmax;
        data = new T[xmax];
        for (int i = 0; i < xmax; ++i) {
            data[i] = mr[i];
        }
        return *this;
    }

    T &operator[](size_t x) {
        return data[x];
    }

    const T &operator[](size_t x) const {
        return data[x];
    }

    ~MatrixRow() {
        delete[] data;
    }

};


#endif //GENIRGRAFNAGYHF_MATRIX_H
