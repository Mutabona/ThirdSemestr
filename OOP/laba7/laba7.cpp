#include <iostream>
#include <windows.h>

#include "Matrix.cpp"
const int elements = 3;

template<typename T>
void testMatrixFunctions();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    testMatrixFunctions<int>();
    testMatrixFunctions<char>();
    testMatrixFunctions<double>();
}

template<typename T>
void testMatrixFunctions() {
    Matrix<T> matrix(elements);
    matrix.PrintData();
    matrix.ProcessData(0, elements-1);
    matrix.PrintData();
}