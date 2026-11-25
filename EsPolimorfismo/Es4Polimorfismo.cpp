#include <iostream>
#include <string>
#include <vector>

class Notifica {
public:
    virtual void invia(std::string messaggio) = 0;
    virtual ~Notifica() = default;
};

class NotificaEmail : public Notifica {
public:
    void invia(std::string messaggio) override {
        std::cout << "Email inviata: " << messaggio << "\n";
    }
};

class NotificaSMS : public Notifica {
public:
    void invia(std::string messaggio) override {
        std::cout << "SMS inviato: " << messaggio << "\n";
    }
};

class NotificaPush : public Notifica {
public:
    void invia(std::string messaggio) override {
        std::cout << "Notifica push inviata: " << messaggio << "\n";
    }
};

class GestoreNotifiche {
    private:
    std::vector<Notifica*> canali;

public:
    void aggiungi(Notifica* n) {
        canali.push_back(n);
    }

    void inviaATutti(std::string messaggio) {
        for (Notifica* n : canali) {
            n->invia(messaggio);
        }
    }
};