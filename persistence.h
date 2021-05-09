#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "defs.h"

/// A perzisztenciáért felelős osztály
/** Itt kaptak helyet a perzisztenciával foglalkozó függvények.
**/
class persistence
{
    public:
        virtual std::ostream& write(std::ostream&) = 0;
        virtual std::istream& read(std::istream&) = 0;
        virtual int decode8(std::istream&) = 0;
        virtual void encode8(std::ostream&, int) = 0;
        virtual void writetofile(const char* filename) = 0;
        virtual void readfromfile(const char* filename) = 0;
        virtual ~persistence() {}
};

#endif // PERSISTENCE_H
