#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

class Publicidad {
private:
    char mensaje[50];
    char categoria[5]; // A, B, C

public:
    Publicidad();
    Publicidad(const char*, const char*);
    void mostrarAnuncio() const;
};

#endif

