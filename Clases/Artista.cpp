#include <cstring>
#include <iostream>
#include "Artista.h"
#include "Album.h"


using namespace std;

Artista::Artista() {
    idArtista = 0;
    edad = 0;
    seguidores = 0;
    posicionTendencia = 0;
    numAlbumes = 0;
    capacidadAlbumes = 0;
    albumes = nullptr;

    // Inicializamos país con cadena vacía
    pais[0] = '\0';
}

Artista::Artista(int id, int edadA, const char* p, int seg, int pos, int capAlb) {
    idArtista = id;
    edad = edadA;
    seguidores = seg;
    posicionTendencia = pos;
    numAlbumes = 0;
    capacidadAlbumes = capAlb;

    if (capacidadAlbumes > 0) {
        albumes = new Album*[capacidadAlbumes];
        for (int i = 0; i < capacidadAlbumes; i++) {
            albumes[i] = nullptr;
        }
    } else {
        albumes = nullptr;
    }


    if (p != nullptr) {
        strncpy(pais, p, sizeof(pais) - 1);
        pais[sizeof(pais) - 1] = '\0';
    } else {
        pais[0] = '\0';
    }
}

Artista::Artista(const Artista& otro) {
    idArtista = otro.idArtista;
    edad = otro.edad;
    seguidores = otro.seguidores;
    posicionTendencia = otro.posicionTendencia;
    numAlbumes = otro.numAlbumes;
    capacidadAlbumes = otro.capacidadAlbumes;

    strncpy(pais, otro.pais, sizeof(pais) - 1);
    pais[sizeof(pais) - 1] = '\0';

    if (capacidadAlbumes > 0) {
        albumes = new Album*[capacidadAlbumes];
        for (int i = 0; i < numAlbumes; i++) {
            albumes[i] = otro.albumes[i]; // copia superficial
        }
    } else {
        albumes = nullptr;
    }
}


bool Artista::agregarAlbum(Album* a) {
    if (numAlbumes >= capacidadAlbumes) {
        cout << "No hay espacio para más álbumes en el catálogo." << endl;
        return false;
    }
    albumes[numAlbumes++] = a;
    return true;
}
