#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>

class Usuarios {
private:
    std::string usuarios;
    std::string membresia;
    std::string ciudad;
    std::string pais;
    std::string fechaDeRegistro;

public:
    // Constructor
    Usuarios(std::string usuario, std::string membresia, std::string ciudad,
             std::string pais, std::string fecha);

    // Getters
    std::string getusuarios() const;
    std::string getMembresia() const;
    std::string getCiudad() const;
    std::string getPais() const;
    std::string getFechaDeRegistro() const;

    // Setters
    void setMembresia(std::string nuevaMembresia);
};

#endif


