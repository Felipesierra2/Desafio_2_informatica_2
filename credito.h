#ifndef CREDITO_H
#define CREDITO_H

class Credito {
private:
    char nombre[30];
    char rol[15]; // Productor, Músico, Compositor

public:
    Credito();
    Credito(const char*, const char*);
    void mostrar() const;
};

#endif
