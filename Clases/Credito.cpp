#include "Credito.h"
#include <iostream>

using namespace std;

Credito::Credito()
    : categoria(""), nombre(""), apellido(""), codigoAfiliacion("") {}

Credito::Credito(const string& categoria,
                 const string& nombre,
                 const string& apellido,
                 const string& codigoAfiliacion)
    : categoria(categoria),
    nombre(nombre),
    apellido(apellido),
    codigoAfiliacion(codigoAfiliacion) {}

string Credito::getCategoria() const { return categoria; }
string Credito::getNombre() const { return nombre; }
string Credito::getApellido() const { return apellido; }
string Credito::getCodigoAfiliacion() const { return codigoAfiliacion; }

void Credito::setCategoria(const string& cat) { categoria = cat; }
void Credito::setNombre(const string& nom) { nombre = nom; }
void Credito::setApellido(const string& ape) { apellido = ape; }
void Credito::setCodigoAfiliacion(const string& cod) { codigoAfiliacion = cod; }

void Credito::mostrarCredito() const {
    cout << "  [" << categoria << "] "
         << nombre << " " << apellido
         << " | Código: " << codigoAfiliacion << endl;
}

