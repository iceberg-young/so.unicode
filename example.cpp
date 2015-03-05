#include <iostream>
#include "include/unicode.hpp"

using namespace std;

int main() {
    string l{"\\uD801\\uDC02"};
    auto i = l.cbegin();
    cout << so::unicode::escape(u"\u1234\xD801\xDC02\u4321") << '\t' << so::unicode::escaped(i);
    return 0;
}
