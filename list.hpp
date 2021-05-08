#ifndef LIST_HPP
#define LIST_HPP


using std::cout;
using std::endl;


/// Delete node from list
/// Detailed explanation
/// @param dataIn Data of the node
/// @warning List must have at least one node!
/// @warning Must use existing data!
template <typename T>
class list : public persistence
{
protected:

private:
    node<T>* first;
    node<T>* last;
    bool isEmpty();
    bool dataExist(T);


public:
    list();
    ~list();
    //list (list& x);
    void insertNode(const T&);
    void deleteNode(T);
    //bool isEmpty();
    void print(std::ostream& os);
    void printInverse(std::ostream& os);
    void insertAtFirst(const T&);
    void insertAtLast(const T&);
    int size();
    virtual int decode8(std::istream&);
    virtual void encode8(std::ostream&, int);
    virtual std::ostream& write(std::ostream&);
    virtual std::istream& read(std::istream&);
    virtual void writetofile(const char* filename);
    virtual void readfromfile(const char* filename);
    class iterator
    {

    public:
        node<T> * ptr;

        iterator(node<T> * ptr = NULL)
            : ptr(ptr)
        {
        }

        iterator operator++(int)
        {
            if(ptr->next == NULL)
                throw std::out_of_range("Iterator kifutott a listabol!");
            iterator copy = *this; // !
            ptr = ptr->next;
            return copy;
        }

        iterator operator--(int)
        {
            if(ptr->prev == NULL)
                throw std::out_of_range("Iterator kifutott a listabol!");
            iterator copy = *this; // !
            ptr = ptr->prev;
            return copy;
        }

        T& operator*() const
        {
            return ptr->data;
        }

        bool operator==(iterator a) const
        {
            return ptr == a.ptr;
        }
        bool operator!=(iterator a) const
        {
            return ptr != a.ptr;
        }
        bool operator<(iterator a) const
        {
            return ptr < a.ptr;
        }
        bool operator>(iterator a) const
        {
            return ptr > a.ptr;
        }

    };

    iterator begin()
    {
        return iterator(first);
    }

    iterator end()
    {
        return iterator(last);
    }

    iterator firstData()
    {
        return iterator(first->next);
    }

    iterator lastData()
    {
        return iterator(last->prev);
    }

};


template <typename T>
list<T>::list()
{
    first = new node<T>;
    last = new node<T>;
    first->next = last;
    last->prev = first;
}


template <typename T>
list<T>::~list()
{
    auto iter = firstData();
    while (iter != last)
    {
        node<T>* temp = iter.ptr;
        iter++;
        delete temp;
    }
    delete first;
    delete last;
}


template <typename T>
bool list<T>::isEmpty()
{
    if(first->next == last || last->prev == first)
        return true;
    return false;
}

template <typename T>
bool list<T>::dataExist(T dataIn)
{
    auto iter = firstData();
    while(iter != last)
    {
        if(dataIn == iter.ptr->data)
            return true;
        iter++;
    }
    return false;
}


/// Delete node from list
/// Detailed explanation
/// @param dataIn Data of the node
/// @warning List must have at least one node!
/// @warning Must use existing data!
template <typename T>
void list<T>::deleteNode(T dataIn)
{
    if(isEmpty())
        throw std::length_error("A lista ures!");
    if(!(dataExist(dataIn)))
        throw std::invalid_argument("Nincs ilyen adat a listaban!");
    auto iter = firstData();
    while (iter != last)
    {
        if(dataIn == iter.ptr->data)
        {
            iter.ptr->next->prev = iter.ptr->prev;
            iter.ptr->prev->next = iter.ptr->next;
            node<T>* temp = iter.ptr;
            delete temp;
            break;
        }
        iter++;
    }
}

template <typename T>
void list<T>::insertNode(const T& dataIn)
{

    if(dataExist(dataIn))
    {
        throw std::invalid_argument("Van mar ilyen adat a listaban!");
    }

    if(isEmpty()) //if there is no nodes in the list simply insert at beginning
    {
        node<T> * newPtr = new node<T>(dataIn);
        first->next = newPtr;
        newPtr->prev = first;
        newPtr->next = last;
        last->prev = newPtr;
    }
    else  //otherwise
    {

        if(dataIn < first->next->data) //if the data of the new object is less than than the data of first node in list insert at beginning
        {
            insertAtFirst(dataIn);
        }
        else if(dataIn >= last->prev->data) //if the data of the new object is greater than than the data of last node in list insert at end
        {
            insertAtLast(dataIn);
        }
        else //the new node is being inserted in order but not at the beginning or end

        {
            auto iter = firstData();
            node<T> * newPtr = new node<T>(dataIn); //creates new node
            while(iter.ptr->next != last) //runs until the end of the list is reached
            {
                if((newPtr->data < iter.ptr->next->data) && (newPtr->data > iter.ptr->data)) //if the data of the new node is less the data in the next node and greater than the data in the current node, insert after current node
                {
                    newPtr->next = iter.ptr->next;
                    newPtr->prev = iter.ptr;
                    iter.ptr->next->prev = newPtr;
                    iter.ptr->next = newPtr;
                    break;
                }
                iter++; //moves to the next node in the list
            }
        }
    }
}

template <typename T>
void list<T>::insertAtFirst(const T& dataIn)
{
    node<T> * newPtr = new node<T>(dataIn);
    first->next->prev = newPtr;
    newPtr->next = first->next;
    newPtr->prev = first;
    first->next = newPtr;
}

template <typename T>
void list<T>::insertAtLast(const T& dataIn)
{
    node<T> * newPtr = new node<T>(dataIn);
    last->prev->next = newPtr;
    newPtr->prev = last->prev;
    newPtr->next = last;
    last->prev = newPtr;
}

template <typename T>
void list<T>::print(std::ostream& os)
{

    if(isEmpty())
    {
        throw std::length_error("A lista ures!");
    }
    else
    {
        auto iter = firstData();
        os << "A lista elemei: ";
        while(iter.ptr != last) //prints until the end of the list is reached
        {
            os << iter.ptr->data << ", ";
            iter++; //moves to next node in list
        }
        //cout << os;
        os << endl;
    }
}


template <typename T>
void list<T>::printInverse(std::ostream& os)
{
    if(isEmpty())
    {
        throw std::length_error("A lista ures!");

    }
    else
    {
        auto iter = lastData();
        os << "A lista elemei: ";
        while(iter.ptr != first) //prints until the end of the list is reached
        {
            os << iter.ptr->data << ", ";
            iter--; //moves to next node in list
        }
        os << endl;
    }
}

template <typename T>
int list<T>::size()
{
    auto iter = firstData();
    int size = 0;
    while(iter.ptr != last)
    {
        iter++;
        size++;
    }
    return size;

}

template <typename T>
void list<T>::encode8(std::ostream& stream, int number)
{
        unsigned char* numberchar = (unsigned char*) &number;

        for (int i = 0; i < (int)sizeof(int); i++)
        {
            std::bitset<8> x(numberchar[i]);
            stream << x;
        }
}

template <typename T>
std::ostream& list<T>::write(std::ostream& stream)
{
    if(isEmpty())
    {
        throw std::length_error("A lista ures!");
    }
    else
    {
        int mainsize = size();
        encode8(stream, mainsize);
        auto iter = firstData();
        while(iter.ptr != last)
        {
            encode8(stream, sizeof(T));
            unsigned char* numberchar = (unsigned char*)&(iter.ptr->data);

            for (int i = 0; i < (int)sizeof(T); i++)
            {
                std::bitset<8> z(numberchar[i]);
                stream << z;
            }
            iter++;
        }
    }
    return stream;
}

/*
template <>
std::ostream& list<const char*>::write(std::ostream& stream)
{
    if (first->next == last || last->prev == first)
    {
        throw("A lista ures!");
    }
    else
    {
        int mainsize = size();
        encode8(stream, mainsize);
        auto iter = firstData();
        while (iter.ptr != last)
        {
            encode8(stream, (int)strlen(iter.ptr->data));
            unsigned char* numberchar = (unsigned char*)&(iter.ptr->data);

            for (int i = 0; i < sizeof(T); i++)
            {
                stream << numberchar[i];
            }
            iter++; //moves to next node in list
        }
        std::cout << std::endl;
    }
    return stream;
}
*/


template <typename T>
int list <T>::decode8(std::istream& stream)
 {
    unsigned char numberchar[sizeof(int)];

    for (int i = 0; i < (int)sizeof(int); i++)
    {
            std::bitset<8> z;
            stream >> z;
            numberchar[i] = (unsigned char)z.to_ulong();
    }
    return *(int*)numberchar;
 }

template <typename T>
std::istream& list <T>::read(std::istream& stream)
{
    int mainsize = decode8(stream);

    for(int i = 0; i < mainsize; i++)
    {
        int datasize = decode8(stream);

        unsigned char data[datasize];
        for (int i = 0; i < datasize; i++)
        {
            std::bitset<8> z;
            stream >> z;
            data[i] = (unsigned char)z.to_ulong();
        }
        insertNode(*(T*)data);
    }
    return stream;
}

template <typename T>
void list<T>::writetofile(const char* filename)
{
    std::ofstream file;
    file.open(filename, std::ios::binary);
    write(file);
    file.close();
}

template <typename T>
void list<T>::readfromfile(const char* filename)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);
    if(!file.is_open())
    {
        throw ("Filet nem lehet megnyitni");
    }
    read(file);
    file.close();
}

#endif // LIST_HPP_INCLUDED
