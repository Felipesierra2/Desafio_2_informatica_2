#ifndef GESTIONARUSUARIOS_H
#define GESTIONARUSUARIOS_H

#include "Artista.h"
#include "Publicidad.h"
#include "Usuarios.h"
#include <string>

class GestionarUsuarios
{
private:
    Usuarios** listaUsuarios;
    int cantidadUsuarios;
    int capacidadMaxima;

public:
    GestionarUsuarios();
    ~GestionarUsuarios();

    void CargarUsuarios();
    void GuardarUsuarios();
    void RedimensionarArreglo();

    Usuarios* Login(std::string nombreUsuario);
    bool Registrarse(std::string usuario, std::string membresia, std::string ciudad,
                     std::string pais, std::string fecha);
    bool CambiarMembresia(std::string nombreUsuario, std::string nuevaMembresia);
    Usuarios* buscarPorUsuario(const std::string& usuario);


    int BuscarUsuario(std::string nombreUsuario);
    void MostrarUsuarios();
};
#endif
