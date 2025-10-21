#ifndef USUARIO_H
#define USUARIO_H

#include "cancion.h"

class Cancion;

class Usuarios {
private:
    char usuarios[30];
    char tipoDeMembresia[30];
    char ciudad[30];
    char pais[30];
    char fechaDeRegistro[30];

    Cancion** favoritos;
    int numFavoritos;
    int capacidadFavoritos;

public:
    Usuarios();
    Usuarios(const char* us, const char* tipo, const char* ciu, const char* pa, const char* fecha, int capFav);
    Usuarios(const Usuarios& otroUser);
    ~Usuarios();


    bool agregarFavorito(Cancion* c);
    bool agregarFavorito(int idCancion);
    bool quitarFavorito(int idCancion);
    void listaFavoritos();

    Usuarios& operator =(const Usuarios& otroUser);
    bool operator ==(const Usuarios& otroUser);


    const char* getSobrenombre() const { return sobreNombre; }
};


