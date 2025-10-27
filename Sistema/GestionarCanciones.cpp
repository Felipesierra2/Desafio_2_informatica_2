#include "GestionarCanciones.h"
#include "Credito.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

GestionarCanciones::GestionarCanciones() {
    capacidadMaxima = 20;
    cantidadCanciones = 0;
    listaCanciones = new Cancion*[capacidadMaxima];
    cargarCanciones();
}

GestionarCanciones::~GestionarCanciones() {
    for (int i = 0; i < cantidadCanciones; ++i)
        delete listaCanciones[i];
    delete[] listaCanciones;
}

void GestionarCanciones::redimensionarArreglo() {
    capacidadMaxima *= 2;
    Cancion** nuevo = new Cancion*[capacidadMaxima];
    for (int i = 0; i < cantidadCanciones; ++i)
        nuevo[i] = listaCanciones[i];
    delete[] listaCanciones;
    listaCanciones = nuevo;
    cout << "Capacidad de canciones aumentada a " << capacidadMaxima << endl;
}

void GestionarCanciones::cargarCanciones() {
    ifstream archivo("database/canciones.txt");

    if (!archivo.is_open()) {
        cout << "No se encontró 'database/canciones.txt'. Se creará al guardar." << endl;
        return;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string idStr, idAlbumStr, nombre, duracionStr, ruta, creditosStr, repStr;

        getline(ss, idStr, ';');
        getline(ss, idAlbumStr, ';');
        getline(ss, nombre, ';');
        getline(ss, duracionStr, ';');
        getline(ss, ruta, ';');
        getline(ss, creditosStr, ';');
        getline(ss, repStr, ';');

        long id = stol(idStr);
        long idAlbum = stol(idAlbumStr);
        float duracion = 0.0f;

        if (duracionStr.find(':') != string::npos) {
            int min = 0, seg = 0;
            char sep;
            stringstream sd(duracionStr);
            sd >> min >> sep >> seg;
            duracion = min + seg / 60.0f;
        } else {
            duracion = stof(duracionStr);
        }

        int reproducciones = 0;
        try {
            reproducciones = stoi(repStr);
        } catch (...) {
            cout << "Línea inválida en archivo: " << linea << endl;
            continue;
        }

        if (cantidadCanciones >= capacidadMaxima)
            redimensionarArreglo();

        Cancion* nueva = new Cancion(id, idAlbum, nombre, duracion, ruta, reproducciones);

        if (!creditosStr.empty()) {
            stringstream sc(creditosStr);
            string bloqueCredito;

            while (getline(sc, bloqueCredito, '|')) {
                stringstream sb(bloqueCredito);
                string cat, nom, ape, cod;
                getline(sb, cat, ':');
                getline(sb, nom, ':');
                getline(sb, ape, ':');
                getline(sb, cod, ':');

                if (!cat.empty() && !nom.empty() && !ape.empty() && !cod.empty()) {
                    Credito* c = new Credito(cat, nom, ape, cod);
                    nueva->agregarCredito(c);
                }
            }
        }

        listaCanciones[cantidadCanciones++] = nueva;
    }

    archivo.close();
    cout << "Se cargaron " << cantidadCanciones << " canciones correctamente." << endl;
}

void GestionarCanciones::guardarCanciones() {
    ofstream archivo("database/canciones.txt");

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo guardar 'database/canciones.txt'." << endl;
        return;
    }

    archivo << "id;id_album;nombre;duracion;ruta_audio;creditos;reproducciones\n";

    for (int i = 0; i < cantidadCanciones; ++i) {
        Cancion* c = listaCanciones[i];
        if (!c) continue;

        archivo << c->getIdCancion() << ";"
                << c->getIdAlbum() << ";"
                << c->getNombre() << ";";

        int min = static_cast<int>(c->getDuracion());
        int seg = static_cast<int>((c->getDuracion() - min) * 60);
        archivo << setw(2) << setfill('0') << min << ":"
                << setw(2) << setfill('0') << seg << ";";

        archivo << c->getRutaArchivo() << ";";


        bool primero = true;
        for (int j = 0; j < c->numCreditos; ++j) {
            Credito* cr = c->creditos[j];
            if (!cr) continue;
            if (!primero) archivo << "|";
            primero = false;
            archivo << cr->getCategoria() << ":"
                    << cr->getNombre() << ":"
                    << cr->getApellido() << ":"
                    << cr->getCodigoAfiliacion();
        }

        archivo << ";" << c->getVecesReproducida() << "\n";
    }

    archivo.close();
    cout << "Canciones guardadas correctamente." << endl;
}

Cancion* GestionarCanciones::buscarPorId(long id) const {
    for (int i = 0; i < cantidadCanciones; ++i) {
        if (listaCanciones[i] != nullptr &&
            listaCanciones[i]->getIdCancion() == id) {
            return listaCanciones[i];
        }
    }
    return nullptr;
}

Cancion* GestionarCanciones::buscarPorNombre(const std::string& nombre) const {
    for (int i = 0; i < cantidadCanciones; ++i) {
        if (listaCanciones[i] != nullptr) {
            std::string nombreCancion = listaCanciones[i]->getNombre();
            if (nombreCancion == nombre) {
                return listaCanciones[i];
            }
        }
    }
    return nullptr;
}

void GestionarCanciones::reproducirCancion(long id)
{
    Cancion* cancion = buscarPorId(id);

    if (cancion == nullptr)
    {
        std::cout << "Error: No se encontró la canción con ID " << id << std::endl;
        return;
    }

    cancion->incrementarReproduccion();

    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        ♪♫ REPRODUCIENDO AHORA ♫♪              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Canción:  " << cancion->getNombre() << std::endl;
    std::cout << "Duración: " << std::fixed << std::setprecision(2)
              << cancion->getDuracion() << " minutos" << std::endl;
    std::cout << "Reproducciones: " << cancion->getVecesReproducida() << std::endl;

    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;

    std::cout << "Progreso: [";
    int barraProgreso = 40;
    for (int i = 0; i < barraProgreso; i++)
    {
        std::cout << "█";
    }
    std::cout << "] 100%" << std::endl;

    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "\n✓ Reproducción completada exitosamente\n" << std::endl;
}

void GestionarCanciones::listarTodas() {
    if (cantidadCanciones == 0) {
        std::cout << "No hay canciones registradas." << std::endl;
        return;
    }

    std::cout << "\n=== LISTA DE CANCIONES ===\n";
    for (int i = 0; i < cantidadCanciones; ++i) {
        if (listaCanciones[i]) {
            std::cout << "ID: " << listaCanciones[i]->getIdCancion()
            << " | Nombre: " << listaCanciones[i]->getNombre()
            << " | Duración: " << listaCanciones[i]->getDuracion()
            << " | Reproducciones: " << listaCanciones[i]->getVecesReproducida()
            << std::endl;
        }
    }
    std::cout << "==========================\n";
}





