#include "Usuarios.h"
#include <algorithm>
#include <cctype>

// Constructor
Usuarios::Usuarios(std::string usuario, std::string membresia, std::string ciudad,
                   std::string pais, std::string fecha)
{
    this->usuarios = usuario;
    this->membresia = membresia;
    this->ciudad = ciudad;
    this->pais = pais;
    this->fechaDeRegistro = fecha;
}

// Getters
std::string Usuarios::getusuarios() const
{
    return usuarios;
}

std::string Usuarios::getMembresia() const
{
    return membresia;
}

std::string Usuarios::getCiudad() const
{
    return ciudad;
}

std::string Usuarios::getPais() const
{
    return pais;
}

std::string Usuarios::getFechaDeRegistro() const
{
    return fechaDeRegistro;
}

// Setter
void Usuarios::setMembresia(std::string nuevaMembresia)
{
    // Convertir a minúsculas para validación
    std::string membresiaLower = nuevaMembresia;
    for (size_t i = 0; i < membresiaLower.length(); i++)
    {
        membresiaLower[i] = tolower(membresiaLower[i]);
    }

    // Validar que sea premium o estandar
    if (membresiaLower == "premium" || membresiaLower == "estandar")
    {
        this->membresia = nuevaMembresia;
    }
}
