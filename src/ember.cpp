/**
 * @file
 * @brief ember.cpp kód
 */


#include "ember.h"
/**
 * @brief Az Ember osztály értékadás operátora
 * @param e A kapott ember
 * @return A kapott e-vel egyenlő lesz az objektum
 */
Ember& Ember::operator=(const Ember& e){
    if(this!=&e){
        nev=e.nev;
        kor=e.kor;
    }
    return *this;
}
/**
 * @brief Ember osztály kiíratását megvalósító függvény
 * @param os ostream referencia
 * @param e A kapott ember
 * @return A keletkezett ostream referencia
 */
std::ostream& operator<<(std::ostream& os,const Ember& e){
    os<<"Nev: "<<e.nev<<" Kor: "<<e.kor;
    return os;
}
/**
 * @brief Pontosvesszővel tagolt sorból Ember-t hoz létre
 * @param s A kapott sor
 * @return A létrehozott Emberre mutató pointer
 */
Ember* Ember::CreateEmber(const std::string& s){
    int kor;
    std::string nev;
    std::stringstream ss(s);
    std::string korstr;
    std::getline(ss, nev, ';');
    std::getline(ss, korstr, ';');
    kor=std::atoi(korstr.c_str());
    return new Ember(nev,kor);
}