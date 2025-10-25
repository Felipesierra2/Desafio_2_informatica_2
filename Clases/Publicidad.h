#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

class Publicidad {
private:
    char mensaje[501];
    char categoria[5]; // 'C', 'B' y 'AAA'

public:
    Publicidad();
    Publicidad(const char* msg, const char*cat);

    int prioridad() const;
    void mostrarAnuncio() const;
};

#endif

