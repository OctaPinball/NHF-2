#ifndef LIST_HPP
#define LIST_HPP

//using namespace std;

using std::cout;
using std::cin;
using std::endl;

template <typename T>
list<T>::list()
{
    first = new node<T>;
    last = new node<T>;
    first->next = last;
    last->prev = first;
}

/*
template <typename T>
list<T>::~list()
{
    auto iter = first;
    while (iter != last)
    {
        node<T>* temp = iter;
        iter = iter->next;
        delete temp;
        iter++;
    }
}
*/

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

template <typename T>
void list<T>::deleteNode(T dataIn)
{
    if(isEmpty())
        throw("A lista ures!");
    if(!(dataExist(dataIn)))
        throw("Nincs ilyen adat a listaban!");
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
        throw("Van mar ilyen adat a listaban!");
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

                    /*
                    node<T> * next = iter->nextPtr;
                    iter->nextPtr = newPtr; //current nodes next pointer now points to the new node
                    newPtr->nextPtr = next; //the new nodes next pointer now points the node previously after the current node
                    */
                    break;
                }
                iter++; //moves to the next node in the list
            }
        }
    }
}

template <typename T>
void list<T>::insertAtFirst(T dataIn)
{
    node<T> * newPtr = new node<T>(dataIn);
    first->next->prev = newPtr;
    newPtr->next = first->next;
    newPtr->prev = first;
    first->next = newPtr;
}

template <typename T>
void list<T>::insertAtLast(T dataIn)
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
        throw("A lista ures!");

    }
    else
    {
        auto iter = firstData();
        os << "A lista elemei: ";
        while(iter.ptr != last) //prints until the end of the list is reached
        {
            //os << iter.ptr->data << ' ';
            std::cout << iter.ptr->data;
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
        throw("A lista ures!");

    }
    else
    {
        auto iter = lastData();
        os << "A lista elemei: ";
        while(iter.ptr != first) //prints until the end of the list is reached
        {
            os << iter.ptr->data << ' ';
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
        std::string mainsizeString = std::to_string(number);
        for (std::size_t i = 0; i < 8 - mainsizeString.size(); i++)
        {
            std::bitset<8> mainsizeBi('0');
            stream << mainsizeBi;
        }
        for (std::size_t i = 0; i < mainsizeString.size(); i++)
        {
            std::bitset<8> mainsizeBi(mainsizeString.c_str()[i]);
            stream << mainsizeBi;
        }
}

template <typename T>
std::ostream& list<T>::write(std::ostream& stream)
{
    if(first->next == last || last->prev == first)
    {
        throw("A lista ures!");
    }
    else
    {
        int mainsize = size();
        encode8(stream, mainsize);


        auto iter = firstData();
        while(iter.ptr != last) //prints until the end of the list is reached
        {
            std::stringstream ss;
            std::string data;
            ss << iter.ptr->data;
            ss >> data;

            int datasize = data.size();
            encode8(stream, datasize);

            //std::string data = std::to_string(iter.ptr->data);
            for (std::size_t i = 0; i < data.size(); ++i)
            {
                std::bitset<8> b(data.c_str()[i]);
                stream << b;
                //std::cout << b << std::endl;
            }
            //std::string bString = "11001100";
            //std::bitset<8> b(bString);

            iter++; //moves to next node in list
        }
        //stream << endl;
    }
    return stream;
}

template <typename T>
int list <T>::decode8(std::istream& stream)
 {
    std::stringstream mainsizeStream;
    for(int i = 0; i < 8; i++)
    {
        std::bitset<8> x;
        stream >> x;
        unsigned char mainsizeStringunit = (unsigned char) x.to_ulong();
        mainsizeStream << mainsizeStringunit;
    }
    int mainsize = 0;
    mainsizeStream >> mainsize;
    return mainsize;
 }

template <typename T>
std::istream& list <T>::read(std::istream& stream)
{
    int mainsize = decode8(stream);
    cout << "Size: " << mainsize << endl;



    for(int i = 0; i < mainsize; i++)
    {
        int datasize = decode8(stream);
        cout << "Size: " << datasize << endl;
        //std::bitset<64> y;
        //stream >> y;
        //int datasize = (int)(y.to_ullong());

        unsigned char* data;
        data = new unsigned char[datasize + 1];
        for(int j = 0; j < datasize; j++)
        {
            std::bitset<8> z;
            stream >> z;
            data[j] = (unsigned char)z.to_ulong();
            std::cout << data[j] << std::endl;
        }
        data[datasize] = '\0';
        T elem = *((T*)data);
        insertNode(elem);
        std::cout << data << std::endl;
        //std::cout << "check" << std::endl;
        delete[] data;
    }
    return stream;
}


#endif // LIST_HPP_INCLUDED
