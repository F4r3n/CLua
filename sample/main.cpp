#include <iostream>
#include <CLua.h>

int main() {
    std::cout << "Yop" << std::endl;
    // CLua::get().createTable("yop", "s", 1);
    CLua::get().init();
    
    CLua::get().createTable("test", "first", 1);
    
    try {
        CLua::get().loadFile("../sample/main.lua");
    } catch(std::string msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}