#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>

class Publicidad {
private:
    int idPublicidad;
    std::string mensaje;
    char categoria;  // 'C', 'B' o 'A' (para AAA)
    int prioridad;   // 1, 2 o 3 según la categoría

public:
    Publicidad();
    Publicidad(int id, const std::string& msg, char cat);

    int getId() const;
    std::string getMensaje() const;
    char getCategoria() const;
    int getPrioridad() const;
};

#endif // PUBLICIDAD_H


