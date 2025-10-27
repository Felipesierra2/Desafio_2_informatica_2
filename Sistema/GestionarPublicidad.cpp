#include "GestionarPublicidad.h"

GestionarPublicidad::GestionarPublicidad() {
    capacidad = 50;
    cantidad = 0;
    lista = new Publicidad[capacidad];
}

GestionarPublicidad::~GestionarPublicidad() {
    delete[] lista;
}

void GestionarPublicidad::agregarPublicidad(const Publicidad& p) {
    if (cantidad < capacidad) {
        lista[cantidad++] = p;
    }
}

int GestionarPublicidad::getCantidad() const {
    return cantidad;
}

Publicidad* GestionarPublicidad::getPublicidad(int i) {
    if (i >= 0 && i < cantidad) return &lista[i];
    return nullptr;
}

