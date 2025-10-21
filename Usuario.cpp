#include "Usuario.h"
#include <iostream>
#include <cstring>

using namespace std;

Usuarios::Usuarios(){
    usuarios[0] = '\0';
    tipoDeMembresia[0] = '\0';
    ciudad[0] = '\0';
    pais[0] = '\0';
    fechaDeRegistro[0] = '\0';

    favoritos = nullptr;
    numFavoritos = 0;
    capacidadFavoritos = 0;

}

Usuarios::Usuarios(const char* us, const char* tipo, const char* ciu, const char* pa, const char* fecha, int capFav){
    strncpy(usuarios, us, sizeof(usuarios) - 1);
    usuarios[sizeof(usuarios) - 1] = '\0';

    strncpy(tipoDeMembresia, tipo, sizeof(tipoDeMembresia) - 1);
    tipoDeMembresia[sizeof(tipoDeMembresia) - 1];

    strncpy(ciudad, ciu, sizeof(ciudad) - 1);
    ciudad[sizeof(ciudad) - 1] = '\0';

    strncpy(pais,pa, sizeof(pais) - 1);
    pais[sizeof(pais) - 1] = '\0';

    strncpy(fechaDeRegistro, fecha, sizeof(fechaDeRegistro));
    fechaDeRegistro[sizeof(fechaDeRegistro) - 1] = '\0';

    numFavoritos =0;
    capacidadFavoritos = capFav;

    if(capacidadFavoritos > 0){
        favoritos = new Cancion* [capacidadFavoritos];
    }
    else{
        favoritos = nullptr;
    }


}

Usuarios::~Usuarios(){
    if (favoritos != nullptr){
        for (int i = 0; i < numFavoritos; i++){
            delete favoritos[i];
        }
        delete[] favoritos;
    }
}



bool Usuarios::agregarFavorito(Cancion* c){
    if (strcmp(tipoDeMembresia, "Premium") != 0){
        cout << "Solo los usuarios Preimiun pueden usar esta opcion " << endl;
        return false;
    }

    if (numFavoritos >= capacidadFavoritos){
        cout << "Capacidad maxima de favoritos alcanzada para el sistema" << endl;
        return false;
    }

    favoritos[numFavoritos++] = c;
    return true;
}

bool Usuarios::agregarFavorito(int idCancion ){
    //Construir estructura una vez se tenga lista de canciones
    return false;
}

bool Usuarios::quitarFavorito(int idCancion){
    for (int i = 0; i < numFavoritos; i++){
        if (favoritos[i] -> getId() == idCancion){
            for (int j = i; j < numFavoritos; j++){
                favoritos[j] = favoritos[j + 1];
            }
            numFavoritos--;
            return true;
        }
    }
    return false;
}

void Usuarios::listaFavoritos(){
    cout << "Favoritos de: " << usuarios << ":" << endl;
    for (int i = 0; i < numFavoritos; i++){
        cout << " - " << favoritos[i] -> getTitulo() << endl;
    }
}

Usuarios& Usuarios::operator=(const Usuarios& otroUser){
    if (this != &otroUser){
        strncpy(usuarios, otroUser.usuarios, sizeof(usuarios)- 1);
        usuarios[sizeof(usuarios) - 1] = '\0';

        strncpy(tipoDeMembresia, otroUser.tipoDeMembresia, sizeof(tipoDeMembresia) - 1);
        tipoDeMembresia[sizeof(tipoDeMembresia) - 1] = '\0';

        strncpy(ciudad,otroUser.ciudad, sizeof(ciudad));
        ciudad[sizeof(ciudad) - 1] = '\0';

        strncpy(pais, otroUser.pais, sizeof(pais) - 1);
        pais[sizeof(pais) - 1] = '\0';

        strncpy(fechaDeRegistro, otroUser.fechaDeRegistro, sizeof(fechaDeRegistro) - 1);
        fechaDeRegistro[sizeof(fechaDeRegistro) - 1] = '\0';

        numFavoritos = otroUser.numFavoritos;
        capacidadFavoritos = otroUser.capacidadFavoritos;

        if(favoritos != nullptr) delete[] favoritos;
        favoritos = new Cancion*[capacidadFavoritos];
        for (int  i = 0; i < numFavoritos; i++){
            favoritos[i] = otroUser.favoritos[i];
        }
    }
    return *this;
}

bool Usuarios::operator == (const Usuarios& otroUser)  {
    return strcmp(usuarios, otroUser.favoritos);
}
