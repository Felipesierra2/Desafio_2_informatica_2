#include "Cancion.h"
#include <iostream>
#include <cstring>


using namespace std;

Cancion::Cancion(){
    id = 0;
    nameCantante[0] = '\0';
    duracion = 0.0f;
    rut128[0] = '\0';
    rut320[0] = '\0';
    creditos = 0;
    numCreditos = 0;
    numReproducciones = 0;
}

Cancion::Cancion(long idC, const char* nameC, float timeD, const char* r128,
                 const char* r320, int credit, int nC, int nR){

    id = idC;
    duracion = timeD;
    creditos = credit;
    numCreditos = nC;
    numReproducciones = nR;

    if (nameC != nullptr){
        strncpy(nameCantante, nameC, sizeof(nameCantante) - 1);
        nameCantante[sizeof(nameCantante) - 1] = '\0';
    }else{
        nameCantante[0] = '\0';
    }

    if (r128 != nullptr){
        strncpy(rut128, r128, sizeof(rut128) - 1);
        rut128[sizeof(rut128) - 1] = '\0';
    }else{
        rut128[0] = '\0';
    }

    if (r320 != nullptr){
        strncpy(rut320, r320, sizeof(rut320) - 1);
        rut320[sizeof(rut320) - 1] = '\0';
    }else{
        rut320[0] = '\0';
    }
}

Cancion::Cancion(const Cancion& otroUser){
    id = otroUser.id;
    duracion = otroUser.duracion;
    creditos = otroUser.creditos;
    numCreditos = otroUser.numCreditos;
    numReproducciones = otroUser.numReproducciones;


    strncpy(nameCantante , otroUser.nameCantante, sizeof(nameCantante) - 1);
    nameCantante[sizeof(nameCantante) - 1] = '\0';

    strncpy(rut128, otroUser.rut128, sizeof(rut128) - 1);
    rut128[sizeof(rut128) - 1] = '\0';

    strncpy(rut320, otroUser.rut320, sizeof(rut320) - 1);
    rut320[sizeof(rut320) - 1] = '0';
}

Cancion::~Cancion(){

}

Cancion& Cancion::operator = (const Cancion& otroUser){
    if(this != &otroUser){
        id = otroUser.id;
        duracion = otroUser.duracion;
        creditos = otroUser.creditos;
        numCreditos = otroUser.numCreditos;
        numReproducciones = otroUser.numReproducciones;

        strncpy(nameCantante , otroUser.nameCantante, sizeof(nameCantante) - 1);
        nameCantante[sizeof(nameCantante) - 1] = '\0';

        strncpy(rut128, otroUser.rut128, sizeof(rut128) - 1);
        rut128[sizeof(rut128) - 1] = '\0';

        strncpy(rut320, otroUser.rut320, sizeof(rut320) - 1);
        rut320[sizeof(rut320) - 1] = '0';

    }

    return *this;
}

bool Cancion::operator ==(const Cancion& otroUser) const{
    return id == otroUser.id;
}

void Cancion::mostrarRutas(bool calidadAlta) const {
    cout << "Portada: " << rut128 << endl;
    if(calidadAlta)
        cout << "Audio: " << rut320 << endl;
    else
        cout << "Audio: " << rut128 << endl;
}

void Cancion::reproducir(bool calidadAlta ){
    cout << "Reproduciendo cancion ID: " << id << endl;
    cout << "Cantante: " << nameCantante << endl;
    cout << "Duracion: " << duracion << endl;
    mostrarRutas(calidadAlta);
    numReproducciones++;
}
