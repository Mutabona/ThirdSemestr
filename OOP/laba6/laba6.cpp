#include <iostream>
#include "BankClient.cpp"

int main() {
    BankClient pyotr;
    std::cin>> pyotr;
    BankClient genadiy;
    std::cout<< pyotr;
    std::cout<< genadiy;
    std::cout<< "Flat = house Genadiy: " << !genadiy <<std::endl;
    std::cout<< "Flat = house ne Genadiy: " << pyotr.operator!() <<std::endl;
    std::cout<< -pyotr;
    std::cout<< "Genadiy flat = ne Genadiy flat: " <<(pyotr == genadiy) <<std::endl;
    std::cout<< "Genadiy adres = ne Genadiy adres: " <<(pyotr + genadiy) <<std::endl;
}
