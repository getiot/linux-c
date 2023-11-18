#include "example.h"

// Implementation of the C functions

extern "C" {
    struct MyClass* createMyClass() {
        return new MyClass();
    }

    void callPrintMessage(struct MyClass* obj) {
        obj->printMessage();
    }

    void destroyMyClass(struct MyClass* obj) {
        delete obj;
    }
}
