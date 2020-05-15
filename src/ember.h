/**
 * @file
 * @brief ember.h header
 */

#ifndef GENIRGRAFNAGYHF_EMBER_H
#define GENIRGRAFNAGYHF_EMBER_H
#include <iostream>
#include <sstream>
#include <cstdlib>
/**
 * @class Ember ember.h osztály
 * @brief Ember osztály
 */
class Ember {
/**
 * @param nev A név
 * @param kor A kor
 */
std::string nev;
int kor;
public:
    /**
     * @brief Az Ember osztály alapértelmezett konstruktora
     */
    Ember():nev(""),kor(0){};
    /**
     * @brief Névből és korbol Embert hoz létre
     * @param nev A kapott név
     * @param kor A kapott kor
     */
    Ember(const std::string& nev, int kor):nev(nev),kor(kor){};
    /**
     * @brief Ember osztály másoló konstruktora
     * @param e A kapott Ember
     */
    Ember(Ember& e){
        nev=e.nev;
        kor=e.kor;
    }
    /**
     * @brief Az Ember osztály értékadás operátora
     * @param e A kapott ember
     * @return A kapott e-vel egyenlő lesz az objektum
     */
    Ember& operator=(const Ember& e);
    /**
     * @brief Ember osztály kiíratását megvalósító függvény
     * @param os ostream referencia
     * @param e A kapott ember
     * @return A keletkezett ostream referencia
     */
    friend std::ostream& operator<<(std::ostream& os,const Ember& e);
    /**
     * @brief Pontosvesszővel tagolt sorból Ember-t hoz létre
     * @param s A kapott sor
     * @return A létrehozott Emberre mutató pointer
     */
    static Ember* CreateEmber(const std::string& s);
};


#endif //GENIRGRAFNAGYHF_EMBER_H
