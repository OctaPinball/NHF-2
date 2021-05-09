#ifndef LIST_HPP
#define LIST_HPP


using std::cout;
using std::endl;


/// Lista osztálya
/** A lista pár kiemelt elemére mutató pointer, illetve a listát kezelő függvények kaptak itt helyet.
**/
template <typename T>
class list : public persistence
{
protected:

private:
    /// Első strázsára mutató pointer.
    node<T>* first;
    /// Utolsó strázsára mutató pointer.
    node<T>* last;
    /// Újonnan hozzáadott listaelemre mutató pointer. insertNode() és positionArrivalNode() függvények használják.
    node<T>* arrival;
    list(const list&);
    bool isEmpty();
    bool dataExist(T);
    void positionArrivalNode();


public:
    list();
    ~list();
    void insertNode(const T&);
    void deleteNode(T);
    void print(std::ostream&);
    void printInverse(std::ostream&);
    //void insertAtFirst(const T&);
    //void insertAtLast(const T&);
    int size();
    virtual int decode8(std::istream&);
    virtual void encode8(std::ostream&, int);
    virtual std::ostream& write(std::ostream&);
    virtual std::istream& read(std::istream&);
    virtual void writetofile(const char* filename);
    virtual void readfromfile(const char* filename);

    /// Az iterátor osztálya
    /** Az iterátort kezelő függvények itt kaptak helyet. Ezeknek nagyrésze operátor függvény.
    **/
    class iterator
    {

    public:
        /// Az iterátor listaelemre mutató pointere.
        node<T> * ptr;

        /// Az iterátor konstruktora
        iterator(node<T> * ptr = NULL)
            : ptr(ptr)
        {}
        /// Az iterátor ++ operátorának függvénye.
        /// A következő listaelemre állítja át az iterátort.
        ///@returns iterator
        iterator operator++(int)
        {
            if(ptr->next == NULL)
                throw std::out_of_range("Iterator kifutott a listabol!");
            iterator copy = *this; // !
            ptr = ptr->next;
            return copy;
        }

        /// Az iterátor -- operátorának függvénye.
        /// Az előző listaelemre állítja át az iterátort.
        ///@returns iterator
        iterator operator--(int)
        {
            if(ptr->prev == NULL)
                throw std::out_of_range("Iterator kifutott a listabol!");
            iterator copy = *this; // !
            ptr = ptr->prev;
            return copy;
        }

        /// Az iterátor * operátorának függvénye.
        /// Visszaadja az adott listaelem adatát.
        ///@returns T a listaelem adata
        T& operator*() const
        {
            return ptr->data;
        }

        /// Az iterátor == operátorának függvénye.
        /// Vizsgálja, hogy két iterátor egyenlő-e.
        ///@returns bool
        bool operator==(iterator a) const
        {
            return ptr == a.ptr;
        }

        /// Az iterátor != operátorának függvénye.
        /// Vizsgálja, hogy két iterátor különböző-e (nem egyenlő).
        ///@returns bool
        bool operator!=(iterator a) const
        {
            return ptr != a.ptr;
        }

        /// Az iterátor < operátorának függvénye.
        /// Vizsgálja, két iterátor egyenlőtlenségét.
        ///@returns bool
        bool operator<(iterator a) const
        {
            return ptr < a.ptr;
        }

        /// Az iterátor < operátorának függvénye.
        /// Vizsgálja, két iterátor egyenlőtlenségét.
        ///@returns bool
        bool operator>(iterator a) const
        {
            return ptr > a.ptr;
        }

    };

    /// Az iterátort az első strázsára állítja.
    iterator begin()
    {
        return iterator(first);
    }

    /// Az iterátort az utolsó strázsára állítja.
    iterator end()
    {
        return iterator(last);
    }

    /// Az iterátort az első listaelemre állítja.
    iterator firstData()
    {
        return iterator(first->next);
    }

    /// Az iterátort az utolsó listaelemre állítja.
    iterator lastData()
    {
        return iterator(last->prev);
    }

};

/// Lista konstruktora.
/// Létrehozza a strázsákat és értéket ad a pointereknek.
template <typename T>
list<T>::list()
{
    arrival = NULL;
    first = new node<T>;
    last = new node<T>;
    first->next = last;
    last->prev = first;
}

/// Lista destruktora.
/// Lebontja a listát. Iterátorral végigmegy a lista elemein, és egyesével törli őket.
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

/// Megnézi, hogy a lista üres-e.
/// @returns bool érték, mely igaz, ha a
template <typename T>
bool list<T>::isEmpty()
{
    if(first->next == last || last->prev == first)
        return true;
    return false;
}

/// Ellenörzi, hogy a paraméterként kapott adat már létezik-e a listában.
/// Iterátor segítségével végigmegy a listán. Amennyiben talál ugyanolyan elemet, igaz értékkel tér vissza.
/// @param dataIn Adat amelyet vizsgál a függvény
/// @returns Bool érték, ami igaz, ha a listában már megtalálható a paraméterként kapott dataIn, ellenkező esetben hamis értékkel tér vissza.
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


/// Elemet töröl a listából.
/** A paraméterként megadott elemet törli a listából, figyelve közben a kivételekre (lentebb).
/// @param dataIn A törlendő listaelem adata.
/// @warning Muszáj a litának legalább egy adattal rendelkeznie!
/// @warning Muszáj listában szereplő adatot megadni paraméterként!
**/
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

/// Új listaelemet ad a listához.
/// Létrehoz egy listaelemet a parameterkent kapott adattal, majd továbbadja a positionArrivalNode() függvénynek, amely beilleszti a listába.
/// @param dataIn Leendő listaelem adata.
template <typename T>
void list<T>::insertNode(const T& dataIn)
{
    node<T> * newPtr = new node<T>(dataIn);
    arrival = newPtr;
    positionArrivalNode();
}

/// Az újonnan létrehozott listaelemet (const char*) helyezi el a listában.
/// Részletes leírás megtekinthető a positionArrivalNode() általános értékekre vett függvényvariációnál.
template <>
void list<const char*>::positionArrivalNode()
{

    if(dataExist(arrival->data))
    {
        delete arrival;
        arrival = NULL;
        throw std::invalid_argument("Van mar ilyen adat a listaban!");
    }

    if(isEmpty())
    {
        first->next = arrival;
        arrival->prev = first;
        arrival->next = last;
        last->prev = arrival;
    }
    else
    {

        if(strcmp(arrival->data, first->next->data) < 0)
        {
            first->next->prev = arrival;
            arrival->next = first->next;
            arrival->prev = first;
            first->next = arrival;
        }
        else if(strcmp(arrival->data, last->prev->data) >= 0)
        {
            last->prev->next = arrival;
            arrival->prev = last->prev;
            arrival->next = last;
            last->prev = arrival;
        }
        else

        {
            auto iter = firstData();
            while(iter.ptr->next != last)
            {
                if((strcmp(arrival->data, iter.ptr->next->data) < 0) && (strcmp(arrival->data, iter.ptr->data)) > 0)
                {
                    arrival->next = iter.ptr->next;
                    arrival->prev = iter.ptr;
                    iter.ptr->next->prev = arrival;
                    iter.ptr->next = arrival;
                    break;
                }
                iter++;
            }
        }
    }
    arrival = NULL;
}

/// Az újonnan létrehozott listaelemet helyezi el a listában.
/** A listaelemet beilleszti a listába úgy, hogy a lista rendezett legyen.
 Előszőr megvizsgálja a, hogy a beilleszteni kívánt elem létezik-e már. Ezt a dataExist() függvénnyel teszi meg. Amennyiben a listaelem már létezik a függvény törli a beilleszteni kívánt listaelemet és kivételt dob.
 Ezek után megvizsgálja azokat a különleges eseteket amikor nincs elem a listában, illetve amikor a listaelem a lista valamely végére kerülne.
 Ha a listaelem nem felelt meg a fentebb említett feltételeknek, akkor az iterátor segítségével a függvény megtalálja a listaelem helyes pozícióját.
 @warning Muszáj még nem létező elemet használni.**/
template <typename T>
void list<T>::positionArrivalNode()
{

    if(dataExist(arrival->data))
    {
        delete arrival;
        arrival = NULL;
        throw std::invalid_argument("Van mar ilyen adat a listaban!");
    }

    if(isEmpty())
    {
        first->next = arrival;
        arrival->prev = first;
        arrival->next = last;
        last->prev = arrival;
    }
    else
    {

        if(arrival->data < first->next->data)
        {
            first->next->prev = arrival;
            arrival->next = first->next;
            arrival->prev = first;
            first->next = arrival;
        }
        else if(arrival->data >= last->prev->data)
        {
            last->prev->next = arrival;
            arrival->prev = last->prev;
            arrival->next = last;
            last->prev = arrival;
        }
        else

        {
            auto iter = firstData();
            while(iter.ptr->next != last)
            {
                if((arrival->data < iter.ptr->next->data) && (arrival->data > iter.ptr->data))
                {
                    arrival->next = iter.ptr->next;
                    arrival->prev = iter.ptr;
                    iter.ptr->next->prev = arrival;
                    iter.ptr->next = arrival;
                    break;
                }
                iter++;
            }
        }
    }
    arrival = NULL;
}


/*
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
*/


/// A lista elemeit kiírja a paraméterként kapott ostream-re.
/** A lista elemeit a függvény az iterátor segítségével járja be, és írja ki az összes listaelemet a paraméterként kapott ostream-re.
@param os ide írja ki a függvény a listaelemeket
@warning Muszáj, hogy a lista rendelkezzen legalább egy elemmel.
**/
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
        while(iter.ptr != last)
        {
            os << iter.ptr->data << ", ";
            iter++;
        }
        os << endl;
    }
}

/// A lista elemeit kiírja fordított sorrendben a paraméterként kapott ostream-re.
/** A lista elemeit a függvény az iterátor segítségével járja be fordított sorrendben, és írja ki az összes listaelemet fordított sorrendben a paraméterként kapott ostream-re.
@parameter os ide írja ki a függvény a listaelemeket fordított sorrendben.
@warning Muszáj, hogy a lista rendelkezzen legalább egy elemmel.
**/
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

/// A lista elemeinek számát meghatározó függvény.
/** A listát az iterátor segítségével bejárja, és meghatározza az elemeinek a számát.
@returns integer ami a lista elemeinek a számát veszi fel.
**/
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

/// A paraméterként kapott integert írja át binárisan, és írja ki a paraméterként kapott ofstream-re.
/** A paraméterként kapott integert írja át binárisan (maximum 8 helyiérték), majd ezt írja ki a paraméterként kapott ostream-re.
@param stream ofstream melyre a függvény kiírja a bináris értéket.
@param number int érték melyet a függvény átalakít.
**/
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

/// Paraméterként kapott ostream-re kiírja a listát olyan rendszerben amiből újra fel lehet azt később építeni.
/** Paraméterként kapott ostream-re kiírja a listát (binárisan) olyan rendszerben amiből újra fel lehet azt később építeni.
A függvény először meghatározza a lista elemeinek a számát és elküldi az encode8() függvénynek, hogy binárissá alakítsa.
Ezek után minden egyes listaelemre meghatározza, hogy az adata mennyi karaktert tesz ki, majd ez után az encode8() függvény
hívásával binárisá alakítja és kiírja ostream-re. Utána a listaelem adatát alakítja binárisá és írja ki ostreamre. Az utolsó két
lépést addig ismétli ameddig a lista végére nem ér.
@parameter stream ostream melyre a függvény kiírja a listát binárisan.
@returns a paraméterként kapot ostream-el tér vissza.
@warning Muszáj, hogy a listának legyen legalább egy eleme.
@note Kiírás: <lista elemszáma> [<listaelem karakterszáma> <listaelem adata> <listaelem karakterszáma> <listaelem adata> stb...]
**/
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

/// A paraméterként kapot istream-ből kiolvassa majd integerré alakít 8 karaktert.
/** A paraméterként kapot istream-ből kiolvassa majd integerré alakít 8 karaktert, majd ezzel az integerrel visszatér a függvény.
@parameter stream istream melyről a függvény beolvassa binárisan az integert.
@returns az átalakított maximum 8 helyiértékű integert adja vissza.
**/
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


/// Paraméterként kapott istream-ből beolvassa és felépíti a listát.
/** Paraméterként kapott istream-ből beolvassa és felépíti a listát.
A függvény először beolvassa a lista elemeinek a számát a decode8() függvény segítségével.
Ezután beolvassa a következő listaelem karakszámát a decode8() függvény segítségével.
Utána a listaelem adatát olvassa be és hozza létre az insertNode() segítségvel. Az utolsó két
lépést addig ismétli ameddig a lista fel nem épül teljesen (ezt segítí az elején beolvasott lista elemszám).
@parameter stream istream melyről a függvény beolvassa a listát binárisan.
@returns a paraméterként kapot istream-el tér vissza.
@note Beolvasás: <lista elemszáma> [<listaelem karakterszáma> <listaelem adata> <listaelem karakterszáma> <listaelem adata> stb...]
**/
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

/// Fájlba írja a listát.
/** Fájlba írja a listát a write() segítségével. Előtte megnyitja a praméterként kapott fájlnévvel ellátott fájlt, majd a kiírás után bezárja azt.
@parameter filename a fájl nevét tartalmazza
**/
template <typename T>
void list<T>::writetofile(const char* filename)
{
    std::ofstream file;
    file.open(filename, std::ios::binary);
    write(file);
    file.close();
}

/// Fájlból olvas be listát.
/** Fájlból olvas be listát a read() függvény segítségével. A paraméterként kapott fájlnévvel ellátott fájlt megnyitja előtte, illetve utána bezárja azt.
@parameter filename a fájl nevét tartalmazza.
@warning A függvény amennyiben nem tudja megynitni a fájlt, kivételt dob.
**/
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
