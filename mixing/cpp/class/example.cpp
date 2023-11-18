#include "example.h"
#include <iostream>

MyClass::MyClass() 
{
    std::cout << "Create MyClass!" << std::endl;
}

MyClass::~MyClass() 
{
    std::cout << "Destroy MyClass!" << std::endl;
}

void MyClass::printMessage() 
{
    std::cout << "Hello from C++ class!" << std::endl;
}