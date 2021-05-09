#ifndef NODE_H
#define NODE_H

#include "defs.h"

template <typename T>
class list;

/// A listaelemek osztálya
/** A listaelem adata és pointerei kaptak itt helyet.
**/
template <typename T>
class node
{
    friend class list<T>;

public:
        /// A listaelem adata.
        T data;
        /// A következő listaelemre mutató pointer.
        node<T>* next;
        /// Az előző listaelemre mutató pointer.
        node<T>* prev;
        node() : next(nullptr), prev(nullptr) {}
        node(const T& dataIn, node<T> *ptr = nullptr) :
            data(dataIn), next(ptr), prev(ptr) {}
};

#endif // NODE_H
