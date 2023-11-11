#include <iostream>
#include <string.h>

class SnowwomanFabric;

class Snowwoman {
    friend class SnowwomanFabric;
    private:
    std::string name;
    int age;

    Snowwoman(const int _age = 18, const int _temperature = -2, const std::string _name = "snegurochka"): age(_age), temperature(_temperature), name(_name) {}
    Snowwoman(const Snowwoman& sw) {}

    void PrintInformation() {
        std::cout<< "My name is " << name <<" and i'm " << age << " years old" << std::endl;
    }

    public:
    int temperature;

    void PrintTemperature() {
        printf("My temperature is %dC\n", temperature);
    }
};

class SnowwomanFabric {
    private:
    SnowwomanFabric() {}

    public:
    static Snowwoman& CreateSnowWoman(int age = 18, int temperature = -2) {
        std::string name;
        if (age < 30) name = "snegurochka";
        else name = "ded moroz";
        Snowwoman* snowwoman = new Snowwoman(age, temperature, name);
        snowwoman->PrintInformation();
        snowwoman->PrintTemperature();
        return *snowwoman;
    }
};