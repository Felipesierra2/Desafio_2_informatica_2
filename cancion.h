#ifndef CANCION_H
#define CANCION_H

#include "credito.h"

#define MAX_CREDITOS 10

class Cancion {
private:
    char id[10];
    char titulo[30];
    int duracion; // segundos
    int numReproducciones;
    Credito creditos[MAX_CREDITOS];
    int numCreditos;

public:
    Cancion();
    Cancion(const char*, const char*, int);
    void reproducir();
    void mostrarInfo() const;
};

#endif

