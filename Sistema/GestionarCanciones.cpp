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
    getline(archivo, linea); // saltar encabezado

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

        // Conversión de "4:05" a minutos flotantes
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

        // Crear la canción
        if (cantidadCanciones >= capacidadMaxima)
            redimensionarArreglo();

        Cancion* nueva = new Cancion(id, idAlbum, nombre, duracion, ruta, reproducciones);

        // Parsear los créditos
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

