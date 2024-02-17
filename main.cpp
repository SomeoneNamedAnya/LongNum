#include <iostream>
#include "longnum.h"
#include <ctime>
using namespace LongNumLib;

int main(){
    clock_t start_time =  clock();
    LongNum pi = PiCalculation(100);
    clock_t end_time = clock();
    double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << search_time << std::endl;
    std::cout << pi.GetLongNum() << std::endl;
    return 0;
}
