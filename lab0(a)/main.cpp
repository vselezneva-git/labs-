#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>
using namespace std;

int main(){
    cout << "Hello World!" << endl; //hello world!

    cout << module1::getMyName() << endl; //john
    cout << module2::getMyName() << endl; //james
    cout << module3::getMyName() << endl;

    using namespace module1;
    cout << getMyName() << endl; //john
    cout << module2::getMyName() << endl; //james 

    using module2::getMyName;
    cout << getMyName() << endl; //james

    {
        using module3::getMyName;
        cout << getMyName() << endl; //peter
    }
}