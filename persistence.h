#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "defs.h"

class persistence
{
    public:
        //persistence();
        virtual std::ostream& write(std::ostream&) = 0;
        virtual std::istream& read(std::istream&) = 0;
        virtual int decode8(std::istream&) = 0;
        virtual void encode8(std::ostream&, int) = 0;
        virtual ~persistence() {}
};

#endif // PERSISTENCE_H
