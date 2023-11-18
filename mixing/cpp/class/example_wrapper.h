#ifndef __EXAMPLE_WRAPPER_H__
#define __EXAMPLE_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration of the C++ class
struct MyClass;

// Function to create an instance of the C++ class
struct MyClass* createMyClass();

// Function to call the C++ member function
void callPrintMessage(struct MyClass* obj);

// Function to destroy the C++ class instance
void destroyMyClass(struct MyClass* obj);

#ifdef __cplusplus
}
#endif

#endif /* __EXAMPLE_WRAPPER_H__ */