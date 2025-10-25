#ifndef SISTEMA_H
#define SISTEMA_H

#include "Usuarios.h"
#include "Cancion.h"
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
    void registrarUsuario();
    void guardarUsuarios();
    void imprimirUsuarios();
    bool agregarUsuario(Usuarios* u);
    Usuarios* iniciarSesion(const char* nickName);
    void reproduccionAleatoria(class Usuarios* u, int k);
    void medirRecursos();
    Cancion* buscarCancionId(long id);

};

#endif

