#include "defs.h"


int main()
{

    TEST(list, printInt1){
        list<int> lista;
        lista.insertNode(1);
        lista.insertNode(2);
        lista.insertNode(3);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1, 2, 3, \n", stream.str().c_str());
    }END

    TEST(list, printInt2){
        list<int> lista;
        lista.insertNode(1);
        lista.insertNode(3);
        lista.insertNode(2);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1, 2, 3, \n", stream.str().c_str());
    }END

    TEST(list, printDouble1){
        list<double> lista;
        lista.insertNode(1.2);
        lista.insertNode(2.4);
        lista.insertNode(3.6);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1.2, 2.4, 3.6, \n", stream.str().c_str());
    }END

    TEST(list, printDouble2){
        list<double> lista;
        lista.insertNode(1.2);
        lista.insertNode(4.4);
        lista.insertNode(3.6);

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: 1.2, 3.6, 4.4, \n", stream.str().c_str());
    }END

    TEST(list, printChar1){
        list<char> lista;
        lista.insertNode('a');
        lista.insertNode('b');
        lista.insertNode('c');

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: a, b, c, \n", stream.str().c_str());
    }END

    TEST(list, printChar2){
        list<char> lista;
        lista.insertNode('a');
        lista.insertNode('d');
        lista.insertNode('c');

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: a, c, d, \n", stream.str().c_str());
    }END

    TEST(list, printString1){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("bravo");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: alpha, bravo, charlie, \n", stream.str().c_str());
    }END

    TEST(list, printString2){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("delta");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: alpha, charlie, delta, \n", stream.str().c_str());
    }END

    TEST(list, printandDelete){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.deleteNode("alpha");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: charlie, \n", stream.str().c_str());
    }END

    TEST(list, printInverse){
        list<const char*> lista;
        lista.insertNode("alpha");
        lista.insertNode("delta");
        lista.insertNode("charlie");

        std::stringstream stream;
        lista.printInverse(stream);
        EXPECT_STREQ("A lista elemei: delta, charlie, alpha, \n", stream.str().c_str());
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

    TEST(list, write){
        list<const char*> lista;
    lista.insertNode("alpha");
    lista.insertNode("charlie");
    lista.insertNode("echo");
    lista.insertNode("delta");
    lista.insertNode("foxtrot");
    lista.insertNode("golf");

        std::stringstream stream;
        lista.write(stream);
        EXPECT_STREQ("00000110000000000000000000000000000010000000000000000000000000000110110011010100010000000000000000000000000000000000000000000000000010000000000000000000000000000111100011010100010000000000000000000000000000000000000000000000000010000000000000000000000000000001001011010101010000000000000000000000000000000000000000000000000010000000000000000000000000001000010011010111010000000000000000000000000000000000000000000000000010000000000000000000000000001000100111010111010000000000000000000000000000000000000000000000000010000000000000000000000000001001000111010111010000000000000000000000000000000000000000000000", stream.str().c_str());
    }END

    TEST(list, read){
        list<const char*> lista;
        std::stringstream readstream;
        readstream << "00000110000000000000000000000000000010000000000000000000000000000110110011010100010000000000000000000000000000000000000000000000000010000000000000000000000000000111100011010100010000000000000000000000000000000000000000000000000010000000000000000000000000000001001011010101010000000000000000000000000000000000000000000000000010000000000000000000000000001000010011010111010000000000000000000000000000000000000000000000000010000000000000000000000000001000100111010111010000000000000000000000000000000000000000000000000010000000000000000000000000001001000111010111010000000000000000000000000000000000000000000000";
        lista.read(readstream);
        std::stringstream stream;
        lista.print(stream);
        EXPECT_STREQ("A lista elemei: alpha, charlie, delta, echo, foxtrot, golf, \n", stream.str().c_str());
    }END

    TEST(list, iter++){
        list<const char*> lista;
        auto iter = lista.firstData();
        EXPECT_ANY_THROW(iter++);
    }END

    TEST(list, iter--){
        list<const char*> lista;
        auto iter = lista.lastData();
        EXPECT_ANY_THROW(iter--);
    }END

    return 0;
}
