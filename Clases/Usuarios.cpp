#include "Usuarios.h"
#include <cstring>

Usuarios::Usuarios(std::string usuario, std::string membresia_, std::string ciudad_,
                   std::string pais_, std::string fecha) {
    usuarios = usuario;
    membresia = membresia_;
    ciudad = ciudad_;
    pais = pais_;
    fechaDeRegistro = fecha;

    favCap = 10000;                // según el enunciado
    favoritos = new long[favCap];
    favCount = 0;

    siguiendoa = nullptr;
}

Usuarios::~Usuarios() {
    delete[] favoritos;
}

std::string Usuarios::getusuarios() const { return usuarios; }
std::string Usuarios::getNombre() const { return usuarios; }
std::string Usuarios::getMembresia() const { return membresia; }
std::string Usuarios::getCiudad() const { return ciudad; }
std::string Usuarios::getPais() const { return pais; }
std::string Usuarios::getFechaDeRegistro() const { return fechaDeRegistro; }

void Usuarios::setMembresia(std::string nuevaMembresia) { membresia = nuevaMembresia; }

bool Usuarios::addFavorito(long id) {
    if (favCount >= favCap) return false;

    for (int i = 0; i < favCount; ++i) {
        if (favoritos[i] == id) return false;
    }

    favoritos[favCount++] = id;
    return true;
}

void Usuarios::imprimirFavoritos() const {
    if (favCount == 0) {
        std::cout << "Lista de favoritos vacía.\n";
        return;
    }
    std::cout << "Favoritos (" << favCount << "):\n";
    for (int i = 0; i < favCount; ++i) {
        std::cout << " - ID: " << favoritos[i] << "\n";
    }
}

int Usuarios::getCantidadFavoritos() const {
    return favCount;
}

long Usuarios::getFavorito(int indice) const {
    if (indice < 0 || indice >= favCount) return -1;
    return favoritos[indice];
}

bool Usuarios::seguirListaDe(Usuarios* otro) {
    if (otro == nullptr) {

        siguiendoa = nullptr;
        return true;
    }

    if (otro == this) return false;

    siguiendoa = otro;
    return true;
}

Usuarios* Usuarios::getUsuarioQueSigue() const {
    return siguiendoa;
}

