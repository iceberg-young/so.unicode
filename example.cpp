#include <iostream>
#include "include/unicode.hpp"

using namespace std;

int main() {
    cout << so::escape(u"\u1234\uB801\uBC02\u4321");
    return 0;
}
