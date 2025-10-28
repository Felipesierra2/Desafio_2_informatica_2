#ifndef CREDITO_H
#define CREDITO_H

#include <string>
#include <iostream>

class Credito {
private:
    std::string categoria;
    std::string nombre;
    std::string apellido;
    std::string codigoAfiliacion;

public:
    Credito();
    Credito(const std::string& categoria,
            const std::string& nombre,
            const std::string& apellido,
            const std::string& codigoAfiliacion);

    std::string getCategoria() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCodigoAfiliacion() const;

    void setCategoria(const std::string& cat);
    void setNombre(const std::string& nom);
    void setApellido(const std::string& ape);
    void setCodigoAfiliacion(const std::string& cod);

    void mostrarCredito() const;
};

#endif

