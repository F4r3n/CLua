#include <iostream>
#include <CLua.h>

int main() {
    std::cout << "Yop" << std::endl;
    CLua::get().createTable("yop", "s", 1);
    return 0;
}