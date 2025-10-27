#ifndef CANCION_H
#define CANCION_H

#include "Credito.h"
#include <string>
#include <iostream>

class Cancion {
private:
    long idCancion;
    long idAlbum;
    std::string nombre;
    float duracion;
    std::string rutaArchivo;
    int vecesReproducida;

    Credito** creditos;
    int numCreditos;
    int capacidadCreditos;

public:
    Cancion();
    Cancion(long id, long idAlbm, const std::string& nombre, float duracion,
            const std::string& ruta, int reproducciones = 0);

    ~Cancion();

    friend class GestionarCanciones;

    // =============================GETTERS=========================//
    long getIdCancion() const;
    long getIdAlbum() const;
    std::string getNombre() const;
    float getDuracion() const;
    std::string getRutaArchivo() const;
    int getVecesReproducida() const;

    //======================SETTERS============================///
    void setIdCancion(long id);
    void setIdAlbum(long idAlbm);
    void setNombre(const std::string& n);
    void setDuracion(float d);
    void setRutaArchivo(const std::string& ruta);
    void setVecesReproducida(int v);

    // =================== CRÉDITOS ====================== //
    void agregarCredito(Credito* c);
    void mostrarCreditos() const;

    void mostrarCancion() const;
    void incrementarReproduccion();
    std::string obtenerArtista();
    std::string obtenerAlbum();
    int obtenerAnio();
    std::string obtenerGenero();

};

#endif




