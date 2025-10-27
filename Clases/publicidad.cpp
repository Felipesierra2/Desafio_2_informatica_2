#include "Publicidad.h"

Publicidad::Publicidad() {
    idPublicidad = 0;
    mensaje = "";
    categoria = 'C';
    prioridad = 1;
}

Publicidad::Publicidad(int id, const std::string& msg, char cat) {
    idPublicidad = id;
    mensaje = msg;
    categoria = cat;

    // Asignar prioridad según categoría
    if (cat == 'A') prioridad = 3;   // AAA
    else if (cat == 'B') prioridad = 2;
    else prioridad = 1;               // C
}

int Publicidad::getId() const { return idPublicidad; }
std::string Publicidad::getMensaje() const { return mensaje; }
char Publicidad::getCategoria() const { return categoria; }
int Publicidad::getPrioridad() const { return prioridad; }
