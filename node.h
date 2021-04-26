#ifndef NODE_H
#define NODE_H

#include "defs.h"

template <typename T>
class list;

template <typename T>
class node
{
    friend class list<T>;

public:
        T data;
        node<T>* next;
        node<T>* prev;
        node() : next(nullptr), prev(nullptr) {}
        node(const T& dataIn, node<T> *ptr = nullptr) :
            data(dataIn), next(ptr), prev(ptr) {}
};

#endif // NODE_H
