#ifndef ALBUM_H
#define ALBUM_H

#include "cancion.h"

#define MAX_CANCIONES_ALBUM 20
#define MAX_GENEROS 4

class Album {
private:
    char codigo[10];
    char nombre[30];
    char generos[MAX_GENEROS][20];
    Cancion canciones[MAX_CANCIONES_ALBUM];
    int numCanciones;

public:
    Album();
    Album(const char*, const char*);
    void agregarCancion(const Cancion&);
    void mostrarCanciones() const;
};

#endif

