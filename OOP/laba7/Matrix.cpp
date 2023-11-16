#include <iostream>

template<typename T>
class Matrix {
    int elements;
    T **data;

    void Fill() {
        for (int i = 0; i < elements; i++) {
            for (int j = 0; j < elements; j++) {
                data[i][j] = 64 + i*j;
            }
        }
    }

    public:
    Matrix(int _elements) {
        elements = _elements;
        data = new T*[elements];
        for (int i = 0; i < elements; i++) {
            data[i] = new T[elements];
        }
        Fill();
    }

    void PrintData() {
        for (int i = 0; i < elements; i++) {
            for (int j = 0; j < elements; j++) {
                std::cout<<data[i][j]<<" ";
            }
            std::cout<<"\n";
        }
        std::cout<<"\n";
    }

    void ProcessData(int n, int m) {
        for (int i = 0; i < elements; i++) {
            T temp = data[n][i];
            data[n][i] = data[m][i];
            data[m][i] = temp;
        }
    }
};