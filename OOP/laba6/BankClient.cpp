#include <iostream>

class BankClient {
    friend std::ostream& operator<<(std::ostream& os, const BankClient& bc);
    friend std::istream& operator>>(std::istream& is, BankClient& bc);
    private:   
    static int clientsAmount;
    int id;
    std::string name;
    std::string surname;
    std::string patronomic;
    std::string city;
    std::string street;
    int house;
    int flat;

    public:
    BankClient() {
        id = clientsAmount++;
        name = (id==0)?"Pyotr":"Genadiy";
        surname = (id==0)?"Pyotr":"Genadiy";
        patronomic = (id==0)?"Pyotr":"Genadiy";
        city = (id==0)?"Kazahstan":"Izumrudniy City";
        street = (id==0)?"Gogolya":"Razbitih lic";
        house = (id==0)?42:93;
        flat = (id==0)?42:93;
    }

    ~BankClient() {
        "Skazali opisat' destructor, nu ya i opsial";
    }

    bool operator!();
    friend BankClient& operator-(BankClient& bc);
    bool operator==(const BankClient& bc);
    friend bool operator+(const BankClient& bc1, const BankClient& bc2);
};

int BankClient::clientsAmount = 0;

bool BankClient::operator!() {
    if (house == flat) return true;
    return false;
}

BankClient& operator-(BankClient& bc) {
    bc.city = "Nigdegorod";
    return bc;
}

bool BankClient::operator==(const BankClient& bc) {
    if (flat == bc.flat) return true;
    return false;
}

bool operator+(const BankClient& bc1, const BankClient& bc2) {
    if (bc1.house == bc2.house && bc1.city == bc2.city && bc1.flat == bc2.flat && bc1.street == bc2.street) return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const BankClient& bc) {
    os<<bc.city<<" "<<bc.name<<" House: "<<bc.house<<" Flat: "<<bc.flat<<std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, BankClient& bc) {
    std::cout<<"Name: "; is>>bc.name;
    //std::cout<<"Surname: "; is>>bc.surname;
    //std::cout<<"Patronomic: "; is>>bc.patronomic;
    //std::cout<<"City: "; is>>bc.city;
    //std::cout<<"Street: "; is>>bc.street;
    std::cout<<"House: "; is>>bc.house;
    std::cout<<"Flat: "; is>>bc.flat;
    return is;
}