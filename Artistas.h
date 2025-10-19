#ifndef ARTISTAS_H
#define ARTISTAS_H

#include "album.h"

#define MAX_ALBUMES_ARTISTA 20

class Artista {
private:
    char nombre[30];
    Album albums[MAX_ALBUMES_ARTISTA];
    int numAlbums;

public:
    Artista();
    Artista(const char*);
    void agregarAlbum(const Album&);
    void mostrarAlbums() const;
};

#endif

