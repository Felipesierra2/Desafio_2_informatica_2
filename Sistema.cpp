#include "Sistema.h"
#include <iostream>
#include <cstring>


using namespace std;

Sistema::Sistema(){
    usuarios = nullptr;
    artistas = nullptr;
    canciones = nullptr;
    publicidad = nullptr;

    numUsuarios = 0;
    capacidadUsuarios = 0;

    numArtistas = 0;
    capacidadArtistas = 0;

    numCanciones = 0;
    capacidadCanciones = 0;

    numPublicidad = 0;
}

//Liberamos memoria
Sistema::~Sistema(){
    if(usuarios != nullptr){
        for (int i = 0; i < numUsuarios; i++){
            delete usuarios[i];
        }
        delete[] usuarios;
    }

    if(artistas != nullptr){
        for (int i = 0; i < numArtistas; i++){
            delete artistas[i];
        }
        delete[] artistas;
    }

    if(canciones != nullptr){
        for (int i = 0; i < numCanciones; i++){
            delete canciones[i];
        }
        delete[] canciones;
    }

    if (publicidad != nullptr){
        for (int i = 0; i < numPublicidad; i++){
            delete publicidad[i];
        }
        delete[] publicidad;
    }
}

void Sistema::cargarDatos(){
    //Cargamos los datos acá
    std::cout << "Cargando Datos del sistema..." << std::endl;
}

Usuario* Sistema::iniciarSesion(const char* nickname)){
    //Interfaz de inicio de seccion
    for (int i = 0; i < numUsuarios; i++){
        if (strcmp(usuarios[i]->getNickName(), nickname) == 0) {
            return usuarios[i];
        }
    }
    std:: cout << "Interfaz del usuario" << std:: endl;
    return nullptr;
}

void Sistema::reproduccionAleatoria(class Usuario* u, int k){
    //Reproduccion aleatoria
    std::cout << "Reproduciendo " << K << " canciones para el usuario..." << std::endl;
}

void Sistema::medirRecursos(){
    //Acá va la logica para medir los recursos
    std::cout <<"Procesando recursos..." << std::endl;
}

bool Sistema::agregarUsuario(::Usuario* u){
    if(numUsuarios >= capacidadUsuarios){
        std::cout << "No hay espacio para mas usuarios " <<  std::endl;
        return false;
    }
    usuarios[numUsuarios++] = u;
    return true;
}

Cancion* Sistema::buscarCancionId(long id){
    for (int i = 0; i < numCanciones; i++) {
        // Suponiendo que Cancion tiene un método getId()
        if (canciones[i]->getId() == id) {
            return canciones[i];
        }
    }
    return nullptr;
}





