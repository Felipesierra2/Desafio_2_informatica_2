#ifndef ARTISTA_H
#define ARTISTA_H

class Album;

class Artista {
private:
    int idArtista;
    int edad;
    char* pais;
    int seguidores;
    int posicionTendencia;
    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

public:
    Artista();
    Artista(int id, int edadA, char* p, int seg, int pos, int capAlb);
    Artista(const Artista& otro);
    ~Artista();

    bool agregarAlbum(Album* a);
};

#endif


