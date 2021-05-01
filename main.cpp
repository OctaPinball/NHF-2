//#include "memtrace.h"
#include "defs.h"


//using namespace std;

int main()
{

    TEST(list, printInt1){
        list<int> lista;
        lista.insertNode(1);
        lista.insertNode(2);
        lista.insertNode(3);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1 2 3 \n", stream.str().c_str());
    }END

    TEST(list, printInt2){
        list<int> lista;
        lista.insertNode(1);
        lista.insertNode(3);
        lista.insertNode(2);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1 2 3 \n", stream.str().c_str());
    }END

    TEST(list, printDouble1){
        list<double> lista;
        lista.insertNode(1.2);
        lista.insertNode(2.4);
        lista.insertNode(3.6);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1.2 2.4 3.6 \n", stream.str().c_str());
    }END

    TEST(list, printDouble2){
        list<double> lista;
        lista.insertNode(1.2);
        lista.insertNode(4.4);
        lista.insertNode(3.6);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1.2 3.6 4.4 \n", stream.str().c_str());
    }END

    TEST(list, printChar1){
        list<char> lista;
        lista.insertNode('a');
        lista.insertNode('b');
        lista.insertNode('c');

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: a b c \n", stream.str().c_str());
    }END

    TEST(list, printChar2){
        list<char> lista;
        lista.insertNode('a');
        lista.insertNode('d');
        lista.insertNode('c');

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: a c d \n", stream.str().c_str());
    }END

    TEST(list, printString1){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("bravo");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: alpha bravo charlie \n", stream.str().c_str());
    }END

    TEST(list, printString2){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("delta");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: alpha charlie delta \n", stream.str().c_str());
    }END

    TEST(list, printandDelete){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.deleteNode("alpha");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: charlie \n", stream.str().c_str());
    }END

    TEST(list, printInverse){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("delta");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.printInverse(stream);
        EXPECT_STREQ("A lista elemei: delta charlie alpha \n", stream.str().c_str());
    }END

    TEST(list, errorDuplicate){
        list<const char*> lista;
        lista.insertNode("alpha");

        EXPECT_ANY_THROW(lista.insertNode("alpha"));
    }END

    TEST(list, errorDelete1){
        list<const char*> lista;

        EXPECT_ANY_THROW(lista.deleteNode("alpha"));
    }END

    TEST(list, errorDelete2){
        list<const char*> lista;
        lista.insertNode("delta");

        EXPECT_ANY_THROW(lista.deleteNode("alpha"));
    }END

    TEST(list, errorPrint){
        list<const char*> lista;

        std::stringstream stream;
        EXPECT_ANY_THROW(lista.print(stream));
    }END



    std::ostream & stream = std::cout;
    cout << "INT LISTA:" << endl;
    list<int> intList;
    if(intList.isEmpty())
        cout << "Ures" << endl;
    else
        cout << "Nem ures" << endl;
    intList.insertNode(1);
    intList.insertNode(2);
    intList.insertNode(4);
    intList.insertNode(3);
    intList.insertNode(5);
    intList.insertNode(34);
    intList.insertNode(15);
    intList.print(stream);
    if(intList.isEmpty())
        cout << "Ures" << endl;
    else
        cout << "Nem ures" << endl;


    cout << "\nSTRING LISTA:" << endl;
    list<const char*> charList;
    if(charList.isEmpty())
        cout << "Ures" << endl;
    else
        cout << "Nem ures" << endl;
    charList.insertNode("alpha");
    charList.insertNode("charlie");
    charList.insertNode("bravo");
    charList.insertNode("echo");
    charList.deleteNode("bravo");
    charList.insertNode("delta");
    charList.insertNode("foxtrot");
    charList.insertNode("golf");
    //charList.~list();
    charList.print(stream);
    if(charList.isEmpty())
        cout << "Ures" << endl;
    else
        cout << "Nem ures" << endl;
    cout << endl;

    list<const char*> lista;
    lista.insertNode("alpha");
    lista.insertNode("charlie");
    lista.insertNode("bravo");
    lista.deleteNode("bravo");
    lista.insertNode("echo");
    lista.insertNode("delta");
    lista.insertNode("foxtrot");
    lista.insertNode("golf");
    lista.print(stream);
    int size = lista.size();
    cout << size << endl;

    std::string s = "00000006";
    std::stringstream geek(s);
    int x = 0;
    geek >> x;
    cout << "Value of x : " << x << endl;

    std::ofstream testfilew;
    testfilew.open("test3.txt", std::ios::binary);
    charList.write(testfilew);
    testfilew.close();


    
    std::ifstream testfile;
    testfile.open("test3.txt", std::ios::binary);
    list<const char*> newlist;
    newlist.read(testfile);
    testfile.close();
    newlist.print(stream);
    
    //newlist.print(stream);

    //charList.~list();
    //memtrace::mem_dump(charList, charList(sizeof));
    return 0;
}
