#include "example_wrapper.h"

int main()
{
    // Create an instance of the C++ class
    struct MyClass* obj = createMyClass();

    // Call the C++ member function from C
    callPrintMessage(obj);

    // Destroy the C++ class instance
    destroyMyClass(obj);

    return 0;
}
