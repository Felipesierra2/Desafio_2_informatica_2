#ifndef SISTEMA_H
#define SISTEMA_H

#include "GestionarUsuarios.h"
#include "GestionarCanciones.h"

class Sistema {
private:
    GestionarUsuarios* gestionarUsuarios;
    GestionarCanciones* gestionarCanciones;

    Usuarios* usuarioAutenticado = nullptr;
public:
    Sistema();
    ~Sistema();
    void ejecutarAplicacion();
private:
    void mostrarMenuPrincipal();
    void manejarLogin();
    void manejarRegistro();
    void mostrarMenuUsuario(Usuarios* usuario);

    void cerrarsesion();
};

#endif

