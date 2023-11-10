#include <iostream>
#include "Snowwoman.cpp"

int main() {
    Snowwoman& snowwoman = SnowwomanFabric::CreateSnowWoman(40);
    snowwoman.temperature = 20;
    snowwoman.PrintTemperature();
}