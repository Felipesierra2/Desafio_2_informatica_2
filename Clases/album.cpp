#include "Album.h"
#include <cstring>
#include <iostream>

Album::Album(){
    idAlbum = 0;
    nombreCantante[0] = '\0';
    for (int i = 0; i <  4; i++){
        generos[i][0] = '\0';
    }
    fechaLanzamiento[0] = '\0';
    duracionAlbum = 0.0f;
    sello[0] = '\0';
    portada[0] = '\0';
    puntuacion = 0.0f;
    canciones = 0;
    numCanciones = 0;
    capacidadCanciones = 0;
}

