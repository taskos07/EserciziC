#include <iostream>
#include <string>
#include <vector>

class Veicolo {
public:
    virtual void muovi() = 0;
    virtual void descrizione() = 0;
    virtual ~Veicolo() = default;
};

class Auto : public Veicolo {
public:
    void muovi() override { std::cout << "L'auto accelera sull'asfalto.\n"; }
    void descrizione() override { std::cout << "Sono un'auto.\n"; }
};

class Bicicletta : public Veicolo {
public:
    void muovi() override { std::cout << "La bicicletta pedala sulla strada.\n"; }
    void descrizione() override { std::cout << "Sono una bicicletta.\n"; }
};

class Treno : public Veicolo {
public:
    void muovi() override { std::cout << "Il treno parte dal binario.\n"; }
    void descrizione() override { std::cout << "Sono un treno.\n"; }
};