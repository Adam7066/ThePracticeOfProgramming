#include <iostream>
#include <sstream>
#include "String.h"

int main() {
    //Power By NTNU_import_magic Discord!!
    String s1, s2("abc"), s3(s2);
    std::cout << "------constructor-----\n";
    std::cout << "s1(): " << s1 << '\n';
    std::cout << "s2(\"abc\"): " << s2 << '\n';
    std::cout << "s3(s2): " << s3 << '\n';
    std::cout << "------information----\n";
    std::cout << "s3.size(): " << s3.size() << '\n';
    std::cout << "s3.c_ctr(): " << s3.c_str() << '\n';
    std::cout << "-------access--------\n";
    std::cout << "s3[2]: " << s3[2] << '\n';
    std::cout << "s3[2] = 'd';\n";
    s3[2] = 'd';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "-----operator+=------\n";
    std::cout << "s2 += s3;\n";
    s2 += s3;
    std::cout << "s2: " << s2 << '\n';
    std::cout << "----copy assignment----\n";
    std::cout << "s1 = s3;\n";
    s1 = s3;
    std::cout << "s1: " << s1 << '\n';
    std::cout << "----------swap--------\n";
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s1.size(): " << s1.size() << '\n';
    std::cout << "s1.capacity(): " << s1.capacity() << '\n';
    std::cout << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s2.size(): " << s2.size() << '\n';
    std::cout << "s2.capacity(): " << s2.capacity() << '\n';
    std::cout << '\n';
    std::cout << "s1.swap(s2);\n";
    s1.swap(s2);
    std::cout << '\n';
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s1.size(): " << s1.size() << '\n';
    std::cout << "s1.capacity(): " << s1.capacity() << '\n';
    std::cout << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s2.size(): " << s2.size() << '\n';
    std::cout << "s2.capacity(): " << s2.capacity() << '\n';
    std::cout << "--------plus----------\n";
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "s1 + ',' + ' ' + s2 + \", \" + s3: " << s1 + ',' + ' ' + s2 + ", " + s3 << '\n';
    std::cout << "-----relational-------\n";
    std::cout << "s1: " << s1 << '\n' << "s2: " << s2 << '\n';
    std::cout << "s1 == s2: " << ((s1 == s2) ? "True" : "False") << '\n';
    std::cout << "s1 != s2: " << ((s1 != s2) ? "True" : "False") << '\n';
    std::cout << "s1 < s2: " << ((s1 < s2) ? "True" : "False") << '\n';
    std::cout << "s1 <= s2: " << ((s1 <= s2) ? "True" : "False") << '\n';
    std::cout << "s1 > s2: " << ((s1 > s2) ? "True" : "False") << '\n';
    std::cout << "s1 >= s2: " << ((s1 >= s2) ? "True" : "False") << '\n';
    std::cout << "-----iostream-------\n";
    std::cout << "stringstream ss(\"123456789 12345\\n6789\");\n";
    std::stringstream ss("123456789 12345\n6789");
    std::cout << "ss >> s1 >> s2 >> s3;\n";
    ss >> s1 >> s2 >> s3;
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "--------clear---------\n";
    std::cout << "s3.clear();\n";
    s3.clear();
    std::cout << "s3.size(): " << s3.size() << '\n';
    std::cout << "s3.c_ctr(): " << s3.c_str() << '\n';
    return 0;
}