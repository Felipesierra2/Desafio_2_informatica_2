#ifndef USUARIOS_H
#define USUARIOS_H

#include "Cancion.h"
#include <string>
#include <iostream>

class Usuarios {
private:
    std::string usuarios;
    std::string membresia;
    std::string ciudad;
    std::string pais;
    std::string fechaDeRegistro;

    long* favoritos;
    int favCount;
    int favCap;


    Usuarios* siguiendoa;

public:
    Usuarios(std::string usuario, std::string membresia, std::string ciudad,
             std::string pais, std::string fecha);
    ~Usuarios();

    std::string getusuarios() const;
    std::string getNombre() const;
    std::string getMembresia() const;
    std::string getCiudad() const;
    std::string getPais() const;
    std::string getFechaDeRegistro() const;
    std::string getNombreUsuarioQueSigue()const;

    void setMembresia(std::string nuevaMembresia);

    bool addFavorito(long id);
    void imprimirFavoritos() const;
    int getCantidadFavoritos() const;
    long getFavorito(int indice) const;

    bool seguirListaDe(Usuarios* otro);
    Usuarios* getUsuarioQueSigue() const;
    void guardarFavoritoEnArchivo(long idCancion, const Cancion* cancion);
    void cargarFavoritosDesdeArchivo();
    bool eliminarFavorito(long idCancion);
    void guardarEnArchivo(std::ofstream& archivo) const;


};

#endif



