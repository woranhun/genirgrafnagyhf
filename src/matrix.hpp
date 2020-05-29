/**
 * @file
 * @brief matrix header
 */

#ifndef GENIRGRAFNAGYHF_MATRIX_HPP
#define GENIRGRAFNAGYHF_MATRIX_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "memtrace.h"
/**
 * @class Matrix
 * @brief A mátrix osztály
 * @tparam T a mátrix adatainak típusa
 */
template<typename T>
class Matrix;
/**
 * @class MatrixRow
 * @brief A mátrix sora
 * @tparam T A mátrix sorának a típusa
 */
template<typename T>
class MatrixRow;


/**
 * @class Matrix
 * @brief mátrix osztály
 * @tparam T a mátrix adatainak típusa
 */
template<typename T>
class Matrix {
protected:
    size_t ymax; //!< A mátrix magassága
    size_t xmax; //!< A mátrix szélessége
    MatrixRow<T> *rows; //!< A mátrix sorait tároló lista
public:
    /**
     * @brief A mátrix default konstruktora
     */
    Matrix() : ymax(0), xmax(0), rows(NULL) {};
    /**
     * @brief A mátrix konstruktora
     * @param y A mátrix magassága
     * @param x A mátrix szélessége
     */
    Matrix(size_t y, size_t x) : ymax(y), xmax(x) {
        rows = new MatrixRow<T>[y];
        for (size_t i = 0; i < y; ++i) {
            rows[i] = MatrixRow<T>(xmax);
        }
        xmax = x;
        ymax = y;
    };
    /**
     * @brief A mátrix konstruktora fájl alapján
     * @param file A kapott fájl
     */
    Matrix(std::ifstream &file) {
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        std::string line;
        std::stringstream ss;
        std::getline(file, line);
        ss << line;
        ss >> ymax >> xmax;
        rows = new MatrixRow<T>[ymax];
        for (size_t i = 0; i < ymax; ++i) {
            rows[i] = MatrixRow<T>(xmax);
        }
        for (size_t i = 0; i < ymax; ++i) {
            std::getline(file, line);
            std::stringstream ss2;
            ss2 << line;
            for (size_t j = 0; j < xmax; ++j) {
                T t;
                ss2 >> t;
                setData(i, j, t);// így jó lesz az indexelés

            }
        }
    }
    /**
     * @brief A mátrix copy konstruktora
     * @param m A kapott mátrix
     */
    Matrix(const Matrix<T> &m) {
        *this = m;
    }
    /**
     * @brief A mátrix értékadó operátora
     * @param m A kapott mátrix
     * @return A keletkezett mátrix
     */
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
    /**
     * @brief Visszaadja a mátrix szélességét
     * @return A mátrix szélessége
     */
    size_t getxmax() { return xmax; }
    /**
     * @brief Visszaadja a mátrix magasságát
     * @return A mátrix magassága
     */
    size_t getymax() { return ymax; }
    /**
     * @brief Mátrix indexelő operátora
     * @param i A megfelelő sor kiválasztása
     * @return A mátrix megfelelő sora
     */
    MatrixRow<T> &operator[](size_t i) { return rows[i]; }
    /**
     * @brief Mátrix indexelő konstans operátora
     * @param i A megfelelő sor kiválasztása
     * @return A mátrix megfelelő sora
     */
    const MatrixRow<T> &operator[](size_t i) const { return rows[i]; }
    /**
     * @brief Mátrix kiírása
     * @param os A kapott ostream
     * @param mx A kapott mátrix
     * @return A keletkezett ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mx) {
        if (mx.rows == NULL) return os;
        for (size_t i = 0; i < mx.ymax; ++i) {
            for (size_t j = 0; j < mx.xmax; ++j) {
                os << std::setw(20) << mx.rows[i][j];
                os << ' ';
            }
            os << std::endl;
        }
        os << std::endl;
        return os;
    }
    /**
     * @brief Visszaállítja a mátrix celláját az alapértelmezett értékre
     * @param y A sor kiválasztása
     * @param x A soron belüli elem kiválasztása
     */
    void setToDefaultValue(size_t y, size_t x) {
        rows[y][x] = T();
    }
    /**
     * @brief felszabadítja a mátrix megfelelő celláját
     * @param t A felszabadítandó adat
     */
    static void freeCell(T& t){
        delete t;
    }
    /**
     * @brief Beállítja a mátrix adatát a megadott értékre
     * @param y A sor kiválasztása
     * @param x A soron belüli elem kiválasztása
     * @param mire A beállítandó érték
     */
    void setData(size_t y, size_t x, T mire) {
        rows[y][x] = mire;
    }
    /**
     * @brief Lefutatja a kapott függvényt a mátrix összes elemén
     * @tparam FUNC függvénytípus
     * @param func A kapott függvény
     * @return A függvénytípus
     */
    template<typename FUNC>
    FUNC executeOnEveryElement(FUNC func){
        for (size_t i = 0; i < ymax; ++i) {
            for (size_t j = 0; j < xmax; ++j) {
                func(rows[i][j]);
            }
        }
        return func;
    }
    /**
     * @brief A mátrixot elmenti fájlba
     * @param filename A kapott fájl neve
     */
    void saveMatrixToFile(const std::string& filename){
        std::ofstream file;
        file.open(filename.c_str());
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        file<< this->ymax <<" "<< this->xmax<<std::endl;
        for (size_t i = 0; i < ymax; ++i) {
            for (size_t j = 0; j < xmax; ++j) {
                file<< this->rows[i][j].isConnected()<<" ";
            }
            file<<std::endl;
        }
        file.close();
    }
    /**
     * @brief Mátrixot beolvassa fájlból
     * @param file A fájlra mutató referencia
     * @return visszadja a fájlt
     */
    std::ifstream &readMatrixFromFile(std::ifstream &file) {
        if (!file.is_open()) throw std::runtime_error("Can't open file!");
        std::string line;
        std::stringstream ss;
        std::getline(file, line);
        ss << line;
        size_t y, x;
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
    /**
     * @brief Mátrix destruktora
     */
    ~Matrix() {
            delete[] rows;
    }
};
/**
 * @class MatrixRow
 * @brief Mátrix sorait tároló osztály
 * @tparam T A mátrixban tárolandó adat
 */
template<typename T>
class MatrixRow {
    T *data; //!< A tárolandó adatokat tartalmazó lista
    size_t xmax; //!< A sor maximális mérete
public:
    /**
     * @brief A mátrix sorának default konstruktora
     */
    MatrixRow() : data(NULL), xmax(0) {};
    /**
     * @brief A mátrix sorának konstruktora méret alapján
     * @param x A kapott méret
     */
    MatrixRow(size_t x) : xmax(x) {
        data = new T[x];
        for (size_t i = 0; i < x; ++i) {
            data[i] = T();
        }
    };
    /**
     * @brief A mátrix sorának copy konstruktora
     * @param mr A kapott mátrix sor
     */
    MatrixRow(const MatrixRow<T> &mr) {
        xmax = mr.xmax;
        *this = mr;
    }
    /**
     * @brief A mátrix értékadó operátora
     * @param mr A kapott mátrix sor
     * @return A keletkezett mátrix sor
     */
    MatrixRow<T> &operator=(const MatrixRow<T> &mr) {
        if(this!=&mr){
            xmax = mr.xmax;
            data = new T[xmax];
            for (size_t i = 0; i < xmax; ++i) {
                data[i] = mr[i];
            }
        }
        return *this;
    }
    /**
     * @brief A mátrix sorának indexelő operátora
     * @param x melyik elem a sorban
     * @return Az adatra mutató referencia
     */
    T &operator[](size_t x) {
        return data[x];
    }
    /**
     * @brief A mátrix sorának indexelő konstans operátora
     * @param x melyik elem a sorban
     * @return Az adatra mutató referencia
     */
    const T &operator[](size_t x) const {
        return data[x];
    }
    /**
     * @brief A mátrix sor destruktora
     */
    ~MatrixRow() {
        delete[] data;
    }

};


#endif //GENIRGRAFNAGYHF_MATRIX_HPP
