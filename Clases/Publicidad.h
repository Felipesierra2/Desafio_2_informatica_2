#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>

class Publicidad {
private:
    int idPublicidad;
    std::string mensaje;
    char categoria;
    int prioridad;

public:
    Publicidad();
    Publicidad(int id, const std::string& msg, char cat);

    int getId() const;
    std::string getMensaje() const;
    char getCategoria() const;
    int getPrioridad() const;
};

#endif

