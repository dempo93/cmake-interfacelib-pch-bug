#include <iostream>
#include <string>
#include <lib1.h>

int main() {
    std::string a{"Hello, "};
    std::string b{"World!"};
    std::cout << concat(a,b) << std::endl;
    return 0;
}
