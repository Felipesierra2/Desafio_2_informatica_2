#ifndef SISTEMA_H
#define SISTEMA_H

#include "Usuario.h"
#include "Artista.h"
#include "cancion.h"
#include "Publicidad.h"

class Usuarios;
class Artistas;
class Cancion;
class Publicidad;

class Sistema {
private:
    //Usuarios
    Usuarios** usuarios;
    int numUsuarios;
    int capacidadUsuarios;

    //Artistas
    Artistas** artistas;
    int numArtistas;
    int capacidadArtistas;

    //Canciones
    Cancion** canciones;
    int numCanciones;
    int capacidadCanciones;

    //Publicidad
    Publicidad** publicidad;
    int numPublicidad;

    //Redimensionamos
    bool tamUsuarios(int nuevo);
    bool tamArtistas(int nuevo);
    bool tamCanciones(int nuevo);
    bool tamPublicidad(int nuevo);

public:
    Sistema();
    ~Sistema();

    void cargarDatos();
    Usuarios* iniciarSesion(const char* sobreNombre);
    void reproduccionAleatoria(class Usuarios* u, int k);
    void medirRecursos();
    bool agregarUsuario(::Usuarios* u);
    Cancion* buscarCancionId(long id);

};

#endif

