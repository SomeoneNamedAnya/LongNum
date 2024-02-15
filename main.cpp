#include <iostream>
#include "longnum.h"
using namespace std;

int main(){
    LongNum a("5.0");
    cout << a.GetLongNum() << endl;
    cout << PiCalculation(6).GetLongNum() << endl;
    return 0;
}
