#include <iostream>
#include <string>
#include <vector>

class MetodoPagamento {
public:
    virtual void paga(double importo) = 0;

    void pagaConCommissione(double importo, double percCommissione) {
        double totale = importo + importo * percCommissione / 100;
        std::cout << "Importo con commissione: " << totale << " euro. ";
        paga(totale);
    }

    virtual ~MetodoPagamento() = default;
};

class CartaCredito : public MetodoPagamento {
public:
    void paga(double importo) override {
        std::cout << "Pagato " << importo << " euro con carta di credito.\n";
    }
};

class PayPal : public MetodoPagamento {
public:
    void paga(double importo) override {
        std::cout << "Pagato " << importo << " euro con PayPal.\n";
    }
};

class Contanti : public MetodoPagamento {
public:
    void paga(double importo) override {
        std::cout << "Pagato " << importo << " euro in contanti.\n";
    }
};