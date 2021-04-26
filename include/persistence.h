#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "defs.h"

class persistence
{
    public:
        //persistence();
        virtual std::ostream write(std::ostream&) const = 0;
        virtual std::istream read(std:istream&) = 0;
        virtual ~persistence() {}
};

#endif // PERSISTENCE_H
