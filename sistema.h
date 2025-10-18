#ifndef SISTEMA_H
#define SISTEMA_H

#include "usuario.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"
#include "publicidad.h"

#define MAX_USUARIOS 100
#define MAX_ARTISTAS 100
#define MAX_CANCIONES 1000
#define MAX_ALBUMES 200

class Sistema {
private:
    Usuario usuarios[MAX_USUARIOS];
    Artista artistas[MAX_ARTISTAS];
    Cancion canciones[MAX_CANCIONES];
    Album albums[MAX_ALBUMES];
    int numUsuarios;
    int numArtistas;
    int numCanciones;
    int numAlbums;

public:
    Sistema();
    void cargarDatos();
    void registrarUsuario();
    void listarUsuarios();
    void buscarCancion();
    void reproducirCancion();
};

#endif

