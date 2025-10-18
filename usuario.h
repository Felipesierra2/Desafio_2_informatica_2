#ifndef USUARIO_H
#define USUARIO_H

#include "cancion.h"

#define MAX_FAVORITOS 10000

class Usuario {
private:
    char nombre[30];
    char tipo[10]; // Premium / Estandar
    int favoritos[MAX_FAVORITOS];
    int numFavoritos;

public:
    Usuario();
    Usuario(const char*, const char*);
    void agregarFavorito(int idCancion);
    void mostrarFavoritos() const;
    bool esPremium() const;
};

#endif
