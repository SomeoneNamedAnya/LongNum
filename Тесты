#include <iostream>
#include <longnum.h>

int main ()
{
    bool is_ok = true;
    //Проверка работы функции по рассчету числа пи

    LongNum pi = pi_calculation(4);
    if (pi.getLongNum() != "3.1415") {
        std::cout << "Error: " << pi.getLongNum() << " " << "3.1415\n";
        is_ok = false;
    }
    // Проверка +
    LongNum first_1("5"), second_1("11110.005"), ans_1;
    LongNum first_2("-15.15"), second_2("3"), ans_2;


    ans_2 = first_2 + second_2;
    ans_1 = first_1 + second_1;

    if (ans_1.getLongNum() != "11115.005") {
        std::cout << "Error: " << ans_1.getLongNum() << " " << "11115.005\n";
        is_ok = false;
    }
    if (ans_2.getLongNum() != "-12.15") {
        std::cout << "Error: " << ans_2.getLongNum() << " " << "-12.15\n";
        is_ok = false;
    }

    // Проверка -

    ans_1 = first_1 - second_1;
    ans_2 = first_2 - second_2;

    if (ans_1.getLongNum() != "-11105.005") {
        std::cout << "Error: " << ans_1.getLongNum() << " " << "11115.005\n";
        is_ok = false;
    }

    if (ans_2.getLongNum() != "-18.15") {
        std::cout << "Error: " << ans_2.getLongNum() << " " << "-18.15\n";
        is_ok = false;
    }
    // Проверка *

    ans_1 = first_1 * second_1;
    ans_2 = first_2 * second_2;

    if (ans_1.getLongNum() != "55550.025") {
        std::cout << "Error: " << ans_1.getLongNum() << " " << "55550.025\n";
        is_ok = false;
    }
    if (ans_2.getLongNum() != "-45.45") {
        std::cout << "Error: " << ans_2.getLongNum() << " " << "-45.45\n";
        is_ok = false;
    }

    // Проверка /

    ans_1 = second_1 / first_1;
    ans_2 = first_2.Div(second_2, 5);

    if (ans_1.getLongNum() != "2222.001") {
        std::cout << "Error: " << ans_1.getLongNum() << " " << "2222.001\n";
        is_ok = false;
    }
    if (ans_2.getLongNum() != "-5.05") {
        std::cout << "Error: " << ans_2.getLongNum() << " " << "-5.05\n";
        is_ok = false;
    }

    // Проверка операций сравнения

    LongNum first_3("5.678"), second_3("5.678");
    if (!(first_3 == second_3)) {
        std::cout << "Error. (Not equel): " << first_3.getLongNum()
        << " and " << second_3.getLongNum();
        is_ok = false;
    }

    if (first_3 < second_3) {
        std::cout << "Error. (First < second) : " << first_3.getLongNum()
        << " and " << second_3.getLongNum();
        is_ok = false;
    }

    if (!(first_1 != second_1)) {
        std::cout << "Error. (Equal) : " << first_1.getLongNum()
        << " and " << second_1.getLongNum();
        is_ok = false;
    }

    if (!(second_2 > first_2)) {
        std::cout << "Error. (First <= second) : " << second_2.getLongNum()
        << " and " << first_2.getLongNum();
        is_ok = false;
    }

    if (is_ok) {

        std::cout << "OK";

    }
    return 0;
}
