#ifndef GESTIONARCANCIONES_H
#define GESTIONARCANCIONES_H

#include "Cancion.h"
#include <string>

class GestionarCanciones {
private:
    Cancion** listaCanciones;
    int cantidadCanciones;
    int capacidadMaxima;

    void redimensionarArreglo();

public:
    GestionarCanciones();
    ~GestionarCanciones();

    void cargarCanciones();
    void guardarCanciones();
    void mostrarCanciones() const;
    void listarTodas();
    Cancion* buscarPorId(long id) const;
    Cancion* buscarPorNombre(const std::string& nombre) const;
    void reproducirCancion(long id);
};

#endif

