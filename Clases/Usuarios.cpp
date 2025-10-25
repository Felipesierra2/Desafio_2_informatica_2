#include "Usuarios.h"
#include <iostream>
#include <cstring>

using namespace std;


/*======================================================================
 Auxiliarex: en esta parte del proyecto, implementamos las funciones
mas internas del sistema, basicamente manejo de memoria y de archivos

=========================================================================*/

char* Usuarios::nuevoChar(const char* cade){
    if(!cade) return nullptr;
    size_t tam = std::strlen(cade);
    char* destino = new char[tam + 1];
    std::strcpy(destino,cade);
    return destino;
}

bool Usuarios::redimensionarFav(int n){
    if( n <= capacidadFavoritos ) return true;
    Cancion** aux = new Cancion*[n];
    for(int i = 0; i < numFavoritos; i++) aux[i] = favoritos[i];
    for (int i = numFavoritos; i < n; i++) aux[i] = nullptr;
    delete[] favoritos;
    favoritos = aux;
    capacidadFavoritos = n;
    return true;
}



/*============================
 * Constructores y destructores
 *
 *Usuarios(): En este metodo, solo inciializamos los arreglos char vacios

*/

Usuarios::Usuarios()
    :usuarios(nullptr),
    membresia(nullptr),
    ciudad(nullptr),
    pais(nullptr),
    fechaDeRegistro(nullptr),
    favoritos(nullptr),
    numFavoritos(0),
    capacidadFavoritos(0)
{

}

Usuarios::Usuarios(const char* us, const char* tipo, const char* ciu,
                   const char* pa, const char* fecha, int capFav)

    :usuarios(nullptr),
    membresia(nullptr),
    ciudad(nullptr),
    pais(nullptr),
    fechaDeRegistro(nullptr),
    favoritos(nullptr),
    numFavoritos(0),
    capacidadFavoritos(0)

{
    usuarios = nuevoChar(us);
    membresia = nuevoChar(tipo);
    ciudad = nuevoChar(ciu);
    pais = nuevoChar(pa);
    fechaDeRegistro = nuevoChar(fecha);

    numFavoritos = 0;
    capacidadFavoritos = (capFav > 0) ? capFav : 0;
    if(capacidadFavoritos > 0){
        favoritos = new Cancion*[capacidadFavoritos];
        for(int i = 0; i < capacidadFavoritos; i++)favoritos[i] = nullptr;
    }else{
        favoritos = nullptr;
    }

}

Usuarios::Usuarios(const Usuarios& otroUser)
    :usuarios(nullptr),
    membresia(nullptr),
    ciudad(nullptr),
    pais(nullptr),
    fechaDeRegistro(nullptr),
    favoritos(nullptr),
    numFavoritos(0),
    capacidadFavoritos(0)

{
    usuarios = nuevoChar(otroUser.usuarios);
    membresia = nuevoChar(otroUser.membresia);
    ciudad = nuevoChar(otroUser.ciudad);
    pais = nuevoChar(otroUser.pais);
    fechaDeRegistro = nuevoChar(otroUser.fechaDeRegistro);

    numFavoritos = otroUser.numFavoritos;
    capacidadFavoritos = otroUser.capacidadFavoritos;
    if (capacidadFavoritos > 0) {
        favoritos = new Cancion*[capacidadFavoritos];
        for (int i = 0; i < numFavoritos; ++i) {
            favoritos[i] = otroUser.favoritos[i];
        }
        for (int i = numFavoritos; i < capacidadFavoritos; ++i) favoritos[i] = nullptr;
    } else {
        favoritos = nullptr;
    }

}

Usuarios::~Usuarios(){
    if (usuarios) delete[] usuarios;
    if (membresia) delete[] membresia;
    if (ciudad) delete[] ciudad;
    if (pais) delete[] pais;
    if (fechaDeRegistro) delete[] fechaDeRegistro;

    if (favoritos) {
        delete[] favoritos;
    }
}

/*===================================================================================
 * Operadores

*/

Usuarios& Usuarios::operator=(const Usuarios& otroUser) {
    if(this == &otroUser)return *this;
    if (usuarios) delete[] usuarios;
    if (membresia) delete[] membresia;
    if (ciudad) delete[] ciudad;
    if (pais) delete[] pais;
    if (fechaDeRegistro) delete[] fechaDeRegistro;

    if (favoritos) {
        delete[] favoritos;
    }

    usuarios = nuevoChar(otroUser.usuarios);
    membresia = nuevoChar(otroUser.membresia);
    ciudad = nuevoChar(otroUser.ciudad);
    pais = nuevoChar(otroUser.pais);
    fechaDeRegistro = nuevoChar(otroUser.fechaDeRegistro);

    numFavoritos = otroUser.numFavoritos;
    capacidadFavoritos = otroUser.capacidadFavoritos;
    if (capacidadFavoritos > 0) {
        favoritos = new Cancion*[capacidadFavoritos];
        for (int i = 0; i < numFavoritos; ++i) favoritos[i] = otroUser.favoritos[i];
        for (int i = numFavoritos; i < capacidadFavoritos; ++i) favoritos[i] = nullptr;
    } else {
        favoritos = nullptr;
    }

    return *this;

}

bool Usuarios::operator == (const Usuarios& otroUser) const{
    if(usuarios == nullptr && otroUser.usuarios == nullptr) return true;
    if(usuarios == nullptr || otroUser.usuarios == nullptr) return false;
    return(std::strcmp(usuarios, otroUser.usuarios) == 0);
}

bool Usuarios::agregarFavorito(Cancion* c){
    if(!c) return false;
    if(!membresia){
        cout << " Error" << endl;
        return false;
    }

    if (std::strcmp(membresia, "Premium") != 0){
        cout << "Solo los usuarios Premium pueden realizar esta opcion\n";
        return false;
    }

    if (numFavoritos >= capacidadFavoritos){
        int nuevot = (capacidadFavoritos == 0) ? 4: capacidadFavoritos * 2;
        if(!redimensionarFav(nuevot)){
            cout << "No se pudo redimensionar favoritos\n";
            return false;
        }
    }
    favoritos[numFavoritos++] = c;
    return true;

}

bool Usuarios::agregarFavorito(int idCancion ){
    //Construir estructura una vez se tenga lista de canciones
    return false;
}

bool Usuarios::quitarFavorito(int idCancion){
    for (int i = 0; i < numFavoritos;i++){
        if (favoritos[i] && favoritos[i] ->getId() == idCancion){
            for(int j = i; j < numFavoritos - 1; j++ ){
                favoritos[j] = favoritos[j + 1];
            }
            favoritos[numFavoritos - 1] = nullptr;
            numFavoritos--;
            return true;
        }
    }
    return false;
}

void Usuarios::listaFavoritos() const{
    cout << "Favoritos de: " << usuarios << ":" << endl;
    for (int i = 0; i < numFavoritos; i++){
        cout << " - " << favoritos[i] -> getTitulo() << endl;
    }
}

