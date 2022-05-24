#include <iostream>
#include "add.h"

using namespace std;

int main(void)
{
    add obj;
    int result = obj.compute(12, 23);
    cout << "The Result = " << result << endl;
    return 0;
}