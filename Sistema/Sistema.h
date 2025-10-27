#ifndef SISTEMA_H
#define SISTEMA_H

#include "GestionarUsuarios.h"
#include "GestionarCanciones.h"
#include "GestionarPublicidad.h"


class Sistema {
private:
    GestionarUsuarios* gestionarUsuarios;
    GestionarCanciones* gestionarCanciones;
    GestionarPublicidad* gestionarPublicidad;

    int cancionesReproducidasSesion;
    long ultimoAnuncioMostradoId;

    void reiniciarContadoresSesion();
    std::string seleccionarAnuncioAleatorio();
    void reproducirConAnuncios(Usuarios* usuario, long id);

    Usuarios* usuarioAutenticado = nullptr;
public:
    Sistema();
    ~Sistema();
    void ejecutarAplicacion();

    void buscarCancionPorNombre();
    void buscarCancionPorId();
    void reproducirCancionUsuario(Usuarios* usuario);
    void agregarFavorito(Usuarios* usuario);
    void verFavoritos(Usuarios* usuario);
    void seguirUsuarioPremium(Usuarios* usuario);

    void mostrarMenuPrincipal();
    void manejarLogin();
    void manejarRegistro();
    void mostrarMenuUsuario(Usuarios* usuario);


    void cerrarsesion();
};

#endif

