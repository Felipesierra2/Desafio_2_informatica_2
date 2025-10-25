#ifndef ALBUM_H
#define ALBUM_H

#include "Cancion.h"


class Album{
private:
    int idAlbum; //2 digitos, parte del id de la cancion
    char nombreCantante[50]; //Personaje asociado
    char generos[4][20]; //Hasta 4 generos
    char fechaLanzamiento[15];
    float duracionAlbum;
    char sello[50]; // sello discografico
    char portada[128]; //Rura .png
    float puntuacion; //1.0 - 10.0
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

