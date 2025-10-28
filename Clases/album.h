#ifndef ALBUM_H
#define ALBUM_H

#include "Cancion.h"


class Album{
private:
    int idAlbum;
    char nombreCantante[50];
    char generos[4][20];
    char fechaLanzamiento[15];
    float duracionAlbum;
    char sello[50];
    char portada[128];
    float puntuacion;
    Cancion* canciones;
    int numCanciones;
    int capacidadCanciones;

public:
    Album();
    Album(int idA, char* namC, const char gen[][20], int numGeneros,
          const char* fecha, const char* selloDisc, const char* port, float punt );
    Album(const Album& otroAlbum);
    ~Album();

    bool agregarCancion(Cancion* c);
    void listarCanciones() const;
};

#endif

