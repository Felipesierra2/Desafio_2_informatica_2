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

Album::Album(int idA, char* namC, const char gen[][20], int numGeneros,
             const char* fecha, const char* selloDisc, const char* port, float punt ){

    idAlbum = idA;
    strncpy(nombreCantante, namC, sizeof(nombreCantante) - 1 );
    nombreCantante[sizeof(nombreCantante) - 1] = '\0';

    for (int i = 0; i < 4; i++){
        if (i < numGeneros)
            strncpy(generos[i], gen[i], sizeof(generos[i]) - 1);
        else
            generos[i][0] = '\0';
    }

    strncpy(fechaLanzamiento, fecha, sizeof(fechaLanzamiento) - 1);
    fechaLanzamiento[sizeof(fechaLanzamiento) - 1] = '\0';

    strncpy(sello, selloDisc, sizeof(sello) - 1);
    sello[sizeof(sello) - 1] = '\0';

    strncpy(portada, port, sizeof(portada) - 1);
    portada[sizeof(portada) - 1] = '\0';

    duracionAlbum = 0.0f;
    puntuacion = punt;
    canciones = 0;
    numCanciones = 0;
    capacidadCanciones = 0;
}

Album::Album(const Album& otroAlbum){
    idAlbum = otroAlbum.idAlbum;
    strcpy(nombreCantante, otroAlbum.nombreCantante);
    for(int i = 0; i < 4; i++){
        strcpy(generos[i], otroAlbum.generos[i]);
    }
    strcpy(fechaLanzamiento, otroAlbum.fechaLanzamiento);
    strcpy(sello, otroAlbum.sello);
    strcpy(portada, otroAlbum.portada);

    puntuacion = otroAlbum.puntuacion;
    duracionAlbum = otroAlbum.duracionAlbum;
    numCanciones = otroAlbum.numCanciones;
    capacidadCanciones = otroAlbum.capacidadCanciones;

    if(capacidadCanciones < 4){
        canciones = new Cancion[capacidadCanciones];
        for(int i = 0; i < numCanciones; i++){
            canciones[i] = otroAlbum.canciones[i];
        }
    }else{
        canciones = 0;
    }
}

Album::~Album(){
    if(canciones){
        delete[] canciones;
    }
}

bool Album::agregarCancion(Cancion* c){
    if(!c) return false;

    if(numCanciones == capacidadCanciones){
        int nuevaCapacidad = (capacidadCanciones == 0) ? 2: capacidadCanciones*2;
        Cancion* aux = new Cancion[nuevaCapacidad];
        for(int i = 0; i < numCanciones; i++)
            aux[i] = canciones[i];

        if (canciones) delete[] canciones;
        canciones = aux;
        capacidadCanciones = nuevaCapacidad;
    }

    canciones[numCanciones] = *c;
    numCanciones++;
    duracionAlbum += c -> getDuracion();// Supongamos que Cancion tiene getDuracion()
    return true;
}

void Album::listarCanciones()const{
    std::cout << "\nAlbum [" << idAlbum << "] - " << nombreCantante << "\n";
    std::cout << "Puntuacion: " << puntuacion << " / 10\n ";
    std::cout << "Duracion Album: " << duracionAlbum << "min\n";
    std::cout << "Canciones (" << numCanciones << "):\n";

    for(int i = 0; i < numCanciones; i++){
        std::cout << "  -  " << (i + 1) << ".  " << canciones[i].getNombre() << "\n";// Supongamos que Cancion tiene getNombre()
    }
}

