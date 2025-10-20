#ifndef ARTISTA_H
#define ARTISTA_H

class Album;

class Artista {
private:
    int idArtista; //5 Digitos
    int edad;
    char pais[30];  //Longitud fija
    int seguidores;
    int posicionTendencia;
    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

public:
    Artista();
    Artista(int id, int edadA, const char* p, int seg, int pos, int capAlb);
    Artista(const Artista& otro);
    ~Artista();

    bool agregarAlbum(Album* a);
};

#endif


