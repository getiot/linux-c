#include <iostream>

extern "C" void printMessage();

void printMessage()
{
    std::cout << "Hello from C++ class!" << std::endl;
}
