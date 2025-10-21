#include "Publicidad.h"
#include <iostream>
#include <cstring>

using namespace std;

Publicidad::Publicidad(){
    mensaje[0] = '\0';
    categoria[0] = '\0';
}

Publicidad::Publicidad(const char* msg, const char* cat){
    if (msg != nullptr){
        strncpy(mensaje,msg, sizeof(mensaje) - 1);
        mensaje[sizeof(mensaje) -1 ] = '\0';
    }else{
        mensaje[0] = '\0';
    }

    //Copiamos la categoria (C,B,AAA)
    if(cat != nullptr){
        strncpy(categoria, cat, sizeof(categoria) - 1);
        categoria[sizeof(categoria) - 1];
    }else{
        categoria[0] = '\0';
    }
}

int Publicidad::prioridad() const{
    if (strcmp(categoria, "C") == 0)
        return 1;
    else if (strcmp(categoria, "B") == 0)
        return 2;
    else if(strcmp(categoria, "AAA") == 0)
        return 3;
    else
        return 0;
}

void Publicidad::mostrarAnuncio() const{
    cout << "Mensaje: " << mensaje << endl;
    cout << "Categoria: " << categoria << endl;
    cout << "Prioridad: " << prioridad() << endl;
}
