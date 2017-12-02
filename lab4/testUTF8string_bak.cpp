#include <iostream>

#include "UTF8string.hpp"

using namespace std;

int main(int argc, char **argv) {
    // 
    // Expected output:
    // ---------------
    // test contains: Mais où sont les neiges d'antan?
    // length in bytes of test: 33
    // number of characters (one 2-byte character): 32
    // position of "sont": 9
    // test2 before replacement: Всё хорошо́, что хорошо́ конча́ется
    // test2 after replacement: Всё просто, что просто конча́ется
    //
    UTF8string test = UTF8string("Mais où sont les neiges d'antan?");
    // UTF8string test = UTF8string();
    UTF8string test2 = UTF8string("Всё хорошо́, что хорошо́ конча́ется");
    cout << "test contains: " << test.value() << endl;
    cout << "length in bytes of test: " << test.bytes() << endl;
    cout << "number of characters (one 2-byte character): " << test.length()
                                                            << endl;
    cout << "position of \"sont\": " << test.find("sont") << endl;
    cout << "position of \"a\": " << test.find("a") << endl;

    cout << "length in bytes of test2: " << test2.bytes() << endl;
    cout << "number of characters: " << test2.length() << endl;
    cout << "test2 before replacement: " << test2.value() << endl;
    test2.replace("хорошо́", "просто");
    cout << "test2 after replacement: " << test2.value() << endl;

    cout << endl;




    return 0;
}
