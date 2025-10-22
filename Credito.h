#ifndef CREDITO_H
#define CREDITO_H

class Credito{
private:
    char nombre[50];
    char apellido[50];
    char codigoAfiliacion[11]; // 10 caracteres 1 -> '\0'
    char rol[20];    // "Productor", "Músico", "Compositor"

public:
    Credito();
    Credito(const char* nom, const char* ape, const char* cod, const char* rolP);
    ~Credito();

    void mostrarCredito()const;
};
#endif
