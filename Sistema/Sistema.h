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

    Usuarios* usuarioAutenticado;
public:
    Sistema();
    ~Sistema();
    void ejecutarAplicacion();

    void buscarCancionPorNombre();
    void buscarCancionPorId();
    void reproducirCancionUsuario(Usuarios* usuario);

    void verFavoritos(Usuarios* usuario);
    void agregarFavorito(Usuarios* usuario);
    void seguirListaDeOtroUsuario(Usuarios* actual, Usuarios* otro);
    void eliminarFavorito(Usuarios* usuario);

    void cargarUsuarios();
    void cargarSeguimientos();
    Usuarios* buscarUsuarioPorNombre(const std::string& nombre);


    void mostrarMenuPrincipal();
    void manejarLogin();
    void manejarRegistro();
    void mostrarMenuUsuario(Usuarios* usuario);

};

#endif

