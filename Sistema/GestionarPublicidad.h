#ifndef GESTIONAR_PUBLICIDAD_H
#define GESTIONAR_PUBLICIDAD_H

#include "Publicidad.h"
#include <iostream>

class GestionarPublicidad {
private:
    Publicidad* lista;
    int cantidad;
    int capacidad;

public:
    GestionarPublicidad();
    ~GestionarPublicidad();

    void agregarPublicidad(const Publicidad& p);
    int getCantidad() const;
    Publicidad* getPublicidad(int i);
};

#endif
