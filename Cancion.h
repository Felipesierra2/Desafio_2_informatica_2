#ifndef CANCION_H
#define CANCION_H

#include "Credito.h"

class Cancion {
private:
    long id;
    char nameCantante[50];
    float duracion;
    char rut128[128]; // ruta absoluta al archivo a 128 kbps
    char rut320[128]; // ruta absoluta al archivo a 320 kbps
    int creditos;
    int numCreditos;
    int numReproducciones;

public:
    Cancion();
    Cancion(long idC, const char* nameC, float timeD, const char* r128,
            const char* r320, int credit, int nC, int nR);

    Cancion(const Cancion& otraCan);
    ~Cancion();

    Cancion& operator =(const Cancion& otraCan);
    bool operator ==(const Cancion& otraCan) const;

    void mostrarRutas(bool calidadAlta)const;
    void reproducir(bool calidadAlta);

    long getId() const {return id;}
    const char* getTitulo() const {return nameCantante;}
    int getNumReproducciones() const {return numReproducciones;}

};

#endif
