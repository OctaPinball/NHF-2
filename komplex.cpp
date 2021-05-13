#include <iostream>         // Valószínű, hogy a kiíráshoz majd kell
#include <iomanip>          // ... és ez is.
#include <cmath>            // az sqrt miatt kell.

#include "komplex.h"        // Ebben van a Komplex osztály, és néhány globális függvény deklarációja

///using namespace std;  // ha nagyon kell, akkor csak itt nyissuk ki a névteret, a headerben soha!

/// Előre elkészített tagfüggvények

/// 0, 1 és 2 paraméteres konstruktor
/// Figyelje meg, hogy a default argumentumokat CSAK a deklarációnál
/// adtuk meg!
Komplex::Komplex(double r, double im) {
    re = r; // ha nincs névütközés, nem kell kiírni a this-t
    this->im = im;
}






///---- Egy példa a konstans tagfüggvényre, ehhez hasonlóan kell
///     elkészíteni a gettereket az 1. feladatban (ELKESZULT=1)
/// Abszolút érték lekérdezése
/// @return - abszolút érték
double Komplex::abs() const { return sqrt(re*re + im*im); }


/// Egyenlőtlenség vizsgálat
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return hamis - ha a képzetes és a valós rész is azonos, egyébként false
bool Komplex::operator!=(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return !(*this == rhs_k);
}
/*
bool Komplex::operator==(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return (*this == rhs_k);
}
*/
bool Komplex::operator==(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return (this->im == rhs_k.im && this->re == rhs_k.re);
}






/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return eredeti (bal oldali) objektum ref., amihez hozzáadtuk rhd_d-t
Komplex& Komplex::operator+=(double rhs_d) {
    re += rhs_d;
    return *this;
}


// ------------------------ Eddig elkészítettük -------------------------
// TODO: A hiányzó tag- és globális függvények itt következnek


double Komplex::getRe() const { return re; }

double Komplex::getIm() const { return im; }



    // beállító függvények
    /// Valós részt beállító függvény
    /// @param r - valós rész
void Komplex::setRe(double r){re = r;}

    /// Képzetes részt beállító függvény
    /// @param im - képzetes rész
void Komplex::setIm(double i){im = i;}



    // összeadás, a + nem módosítja önmagát ezért konstans fv.
    /// Komplex + Komplex
    /// @param rhs_k - jobb oldali operandus (Komplex)
    /// @return egy új komplex adat - a két komplex adat összege
    Komplex Komplex::operator+(const Komplex& rhs_k) const{
        Komplex temp;
        temp.im = this->im + rhs_k.im;
        temp.re = this->re + rhs_k.re;
        return temp;
    }

    /// Komplex + double
    /// @param rhs_d - jobb oldali operandus (double)
    /// @return egy új komplex adat - a két adat összege
    Komplex Komplex::operator+(double rhs_d) const{
        Komplex temp;
        temp.im = this->im;
        temp.re = this->re + rhs_d;
        return temp;
    }

    /// Kiíáras egy ostream-re
/// @param os - bal oldali operandus (ostream)
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return ostream, hogy fűzhető legyen
std::ostream& operator<<(std::ostream& os, const Komplex& rhs_k) {
    std::ios_base::fmtflags ofmt = os.flags(); // régi flag elmentése
    os << std::noshowpos << rhs_k.getRe() << std::showpos << rhs_k.getIm() << 'j';
    os.flags(ofmt);   // flag visszaállítása
    return os;
}

/// Beolvasás egy istream-ről
/// @param is - bal oldali operandus (istream)
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return itsream, hogy fűzhető legyen
std::istream& operator>>(std::istream& is, Komplex& rhs_k) {
    double re, im;
    is >> re >> im; // beolvasunk
    rhs_k = Komplex(re, im);
    is.ignore(1);   // nagyon bízink benne, hogy ott a 'j'
    return is;
}

