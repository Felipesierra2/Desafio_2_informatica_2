#include "Usuarios.h"
#include "Cancion.h"
#include <cstring>
#include <fstream>


Usuarios::Usuarios(std::string usuario, std::string membresia_, std::string ciudad_,
                   std::string pais_, std::string fecha) {
    usuarios = usuario;
    membresia = membresia_;
    ciudad = ciudad_;
    pais = pais_;
    fechaDeRegistro = fecha;

    favCap = 10000;
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

void Usuarios::guardarFavoritoEnArchivo(long idCancion, const Cancion* cancion) {
    if (cancion == nullptr) return;

    std::string nombreArchivo = "database/favoritos_" + getNombre() + ".txt";

    std::ifstream leer(nombreArchivo.c_str());
    std::string linea;
    while (std::getline(leer, linea)) {
        if (linea.find(std::to_string(idCancion)) != std::string::npos) {
            leer.close();
            return;
        }
    }
    leer.close();

    std::ofstream escribir(nombreArchivo.c_str(), std::ios::app);
    if (!escribir) {
        std::cout << "Error al abrir el archivo de favoritos.\n";
        return;
    }

    escribir << cancion->getIdCancion() << ";"
             << cancion->getNombre() << ";"
             << cancion->getDuracion() << ";"
             << cancion->getVecesReproducida() << "\n";

    escribir.close();
}

void Usuarios::cargarFavoritosDesdeArchivo() {
    std::string nombreArchivo = "database/favoritos_" + getNombre() + ".txt";
    std::ifstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return;
    }

    std::string linea;
    favCount = 0;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;


        char buffer[256];
        std::strncpy(buffer, linea.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';

        char* token = std::strtok(buffer, ";");
        if (token != nullptr) {
            long id = std::atol(token);
            if (favCount < favCap) {
                favoritos[favCount++] = id;
            }
        }
    }

    std::cout << "Contador favoritos: " << favCount << std::endl;
    archivo.close();
}

bool Usuarios::eliminarFavorito(long idCancion) {
    if (favCount == 0) {
        std::cout << "No tienes favoritos registrados.\n";
        return false;
    }

    bool encontrado = false;
    int pos = -1;

    for (int i = 0; i < favCount; ++i) {
        if (favoritos[i] == idCancion) {
            encontrado = true;
            pos = i;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "Esa canción no está en tus favoritos.\n";
        return false;
    }

    for (int j = pos; j < favCount - 1; ++j) {
        favoritos[j] = favoritos[j + 1];
    }
    favCount--;

    std::string nombreArchivo = "database/favoritos_" + getNombre() + ".txt";
    std::ifstream leer(nombreArchivo.c_str());
    if (!leer.is_open()) return true;

    std::ofstream temp("database/temp_favoritos.txt");
    if (!temp.is_open()) {
        std::cout << "Error al crear archivo temporal.\n";
        leer.close();
        return false;
    }

    std::string linea;
    std::string idStr = std::to_string(idCancion);

    while (std::getline(leer, linea)) {
        if (linea.find(idStr) == 0) continue;
        temp << linea << "\n";
    }

    leer.close();
    temp.close();

    std::remove(nombreArchivo.c_str());
    std::rename("database/temp_favoritos.txt", nombreArchivo.c_str());

    std::cout << "Canción eliminada de tus favoritos.\n";
    return true;
}



void Usuarios::imprimirFavoritos() const {
    const Usuarios* origen = (siguiendoa != nullptr) ? siguiendoa : this;

    if (origen->favCount == 0) {
        std::cout << "Lista de favoritos vacía.\n";
        return;
    }

    if (siguiendoa != nullptr) {
        std::cout << "Mostrando lista de favoritos de " << siguiendoa->getNombre() << ":\n";
    } else {
        std::cout << "Favoritos (" << favCount << "):\n";
    }

    for (int i = 0; i < origen->favCount; ++i) {
        std::cout << " - ID: " << origen->favoritos[i] << "\n";
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


std::string Usuarios::getNombreUsuarioQueSigue() const {
    if (siguiendoa == nullptr) return "Ninguno";
    return siguiendoa->getNombre();
}

void Usuarios::guardarEnArchivo(std::ofstream& archivo) const {
    archivo << usuarios << ";"
            << membresia << ";"
            << ciudad << ";"
            << pais << ";"
            << fechaDeRegistro;

    if (siguiendoa != nullptr) {
        archivo << ";siguiendo=" << siguiendoa->getNombre();
    }

    archivo << "\n";
}



