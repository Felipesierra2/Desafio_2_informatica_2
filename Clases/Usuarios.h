#ifndef USUARIOS_H
#define USUARIOS_H

#include "Cancion.h"

class Cancion;

class Usuarios {
private:
    char* usuarios;
    char* membresia;
    char* ciudad;
    char* pais;
    char* fechaDeRegistro;

    Cancion** favoritos;
    int numFavoritos;
    int capacidadFavoritos;

    static char* nuevoChar(const char* cade);

    bool redimensionarFav(int n);

public:
    Usuarios();
    Usuarios(const char* us, const char* tipo, const char* ciu, const char* pa, const char* fecha, int capFav);
    Usuarios(const Usuarios& otroUser);
    ~Usuarios();

    bool agregarFavorito(Cancion* c);
    bool agregarFavorito(int idCancion);
    bool quitarFavorito(int idCancion);
    void listaFavoritos() const;

    Usuarios& operator =(const Usuarios& otroUser);
    bool operator ==(const Usuarios& otroUser)const;


    const char* getusuarios() const { return usuarios; }
    const char* getMembresia() const { return membresia; }
    const char* getCiudad() const { return ciudad; }
    const char* getPais() const { return pais; }
    const char* getFechaDeRegistro() const { return fechaDeRegistro;}
};

#endif

