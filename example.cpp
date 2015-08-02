#include <iostream>
#include "include/utf.hpp"

using namespace std;

int main() {
    string l{"\\uD801\\uDC02"};
    auto i = l.cbegin();
    cout << so::utf::escape(u"\u1234\xD801\xDC02\u4321") << '\t' << so::utf::escaped(i);
    return 0;
}
