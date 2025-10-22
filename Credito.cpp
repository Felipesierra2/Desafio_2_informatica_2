#include <iostream>
#include <cstring>
#include "Credito.h"

Credito::Credito(){
    nombre[0] = '\0';
    apellido[0] = '0';
    codigoAfiliacion[0] = '\0';
    rol[0] = '\0';
}


Credito::Credito(const char* nom, const char* ape, const char* cod, const char* rolP){
    strncpy(nombre, nom, sizeof(nombre) - 1 );
    nombre[sizeof(nombre) - 1] = '\0';

    strncpy(apellido, ape, sizeof(apellido) - 1);
    apellido[sizeof(apellido) - 1] = '\0';

    strncpy(codigoAfiliacion, cod, sizeof(codigoAfiliacion) - 1);
    codigoAfiliacion[sizeof(codigoAfiliacion) - 1] = '\0';

    strncpy(rol, rolP, sizeof(rol) - 1);
    rol[sizeof(rolP)] = '\0';

}

Credito::~Credito(){
    //No hace nada demomento
}

void Credito::mostrarCredito() const{
    std::cout << "Crédito:\n";
    std::cout << "  Nombre: " << nombre << " " << apellido << "\n";
    std::cout << "  Código de afiliación: " << codigoAfiliacion << "\n";
    std::cout << "  Rol: " << rol << "\n";
}
