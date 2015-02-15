#include <iostream>

using namespace std;

int main() {
    char o = -5;
    char16_t h = o;
    char32_t x = h;
    cout << hex
      << int(o) << '\t'
      << int(h) << '\t'
      << int(x) << endl;
    return 0;
}
