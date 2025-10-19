#ifndef SISTEMA_H
#define SISTEMA_H

#include "usuario.h"
#include "Artistas.h"
#include "cancion.h"
#include "publicidad.h"

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
    Usuario* iniciarSesion(const char* name);
    void reproduccionAleatoria(class Usuario* u, int k);
    void medirRecursos();
    bool agregarUsuario(::Usuario* u);
    Cancion* buscarCancionId(long id);

};

#endif

