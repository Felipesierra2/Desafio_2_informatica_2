#include "Cancion.h"
#include <iostream>
#include <iomanip>
using namespace std;

Cancion::Cancion()
    : idCancion(0), idAlbum(0), nombre(""), duracion(0.0f),
    rutaArchivo(""), vecesReproducida(0), creditos(nullptr),
    numCreditos(0), capacidadCreditos(3) {

    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; ++i)
        creditos[i] = nullptr;
}

Cancion::Cancion(long id, long idAlbm, const string& n, float d,
                 const string& ruta, int reproducciones)
    : idCancion(id), idAlbum(idAlbm), nombre(n), duracion(d),
    rutaArchivo(ruta), vecesReproducida(reproducciones),
    numCreditos(0), capacidadCreditos(3) {

    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; ++i)
        creditos[i] = nullptr;
}

Cancion::~Cancion() {
    for (int i = 0; i < numCreditos; ++i)
        delete creditos[i];
    delete[] creditos;
}

void Cancion::agregarCredito(Credito* c) {
    if (!c) return;
    if (numCreditos >= capacidadCreditos) return; // límite 3: productor, músico, compositor
    creditos[numCreditos++] = c;
}

void Cancion::mostrarCreditos() const {
    cout << "Créditos de '" << nombre << "':\n";
    if (numCreditos == 0) {
        cout << "  (sin créditos registrados)\n";
        return;
    }
    for (int i = 0; i < numCreditos; ++i)
        if (creditos[i]) creditos[i]->mostrarCredito();
}

void Cancion::mostrarCancion() const {
    cout << left << setw(12) << idCancion
         << setw(25) << nombre.substr(0, 23)
         << setw(8) << fixed << setprecision(2) << duracion
         << setw(10) << vecesReproducida
         << " | Álbum: " << idAlbum << endl;
}

void Cancion::incrementarReproduccion() {
    ++vecesReproducida;
}

