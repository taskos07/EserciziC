#include <iostream>
#include <string>
#include <vector>

class Personaggio {
public:
    virtual void attacca() = 0;
    virtual void presentati() = 0;
    virtual ~Personaggio() = default;
};

class Guerriero : public Personaggio {
public:
    void attacca() override { std::cout << "Il guerriero colpisce con la spada.\n"; }
    void presentati() override { std::cout << "Sono un guerriero.\n"; }
};

class Mago : public Personaggio {
public:
    void attacca() override { std::cout << "Il mago lancia una palla di fuoco.\n"; }
    void presentati() override { std::cout << "Sono un mago.\n"; }
};

class Arciere : public Personaggio {
public:
    void attacca() override { std::cout << "L'arciere scocca una freccia.\n"; }
    void presentati() override { std::cout << "Sono un arciere.\n"; }
};

void turno(Personaggio* p) {
    p->presentati();
    p->attacca();
}