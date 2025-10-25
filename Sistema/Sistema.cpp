#include "Sistema.h"
#include "auxiliares.h"
#include <iostream>
#include <cstring>
#include <limits>


using namespace std;

bool esNickValido(const char* nick) {
    for (int i = 0; nick[i] != '\0'; i++) {
        unsigned char c = nick[i];
        if (isalpha(c) || isdigit(c) || c == '_' || c == '-') continue;
        return false;
    }
    return true;
}

bool esCiudadValida(const char* ciudad) {
    for (int i = 0; ciudad[i] != '\0'; i++) {
        unsigned char c = ciudad[i];
        if (isalpha(c) || isspace(c)) continue;
        return false;
    }
    return true;
}

/*============================================================
*Constructores:
*/

Sistema::Sistema(){
    usuarios = nullptr;
    numUsuarios = 0;
    capacidadUsuarios = 0;

    artistas = nullptr;
    numArtistas = 0;
    capacidadArtistas = 0;

    canciones = nullptr;
    numCanciones = 0;
    capacidadCanciones = 0;

    publicidad = nullptr;
    numPublicidad = 0;
}

//Liberamos memoria
Sistema::~Sistema(){
    if (usuarios) {
        for (int i = 0; i < numUsuarios; ++i) {
            if (usuarios[i]) delete usuarios[i];
        }
        delete[] usuarios;
    }

    /*    if (artistas) {
        for (int i = 0; i < numArtistas; ++i) if (artistas[i]) delete artistas[i];
        delete[] artistas;
    }
    if (canciones) {
        for (int i = 0; i < numCanciones; ++i) if (canciones[i]) delete canciones[i];
        delete[] canciones;
    }
    if (publicidad) {
        for (int i = 0; i < numPublicidad; ++i) if (publicidad[i]) delete publicidad[i];
        delete[] publicidad;
    }*/


}

/*============================================================================
 * Redimensionamiento de los arreglos(usuarios,artistas,canciones,publicidad)
=========================================================================*/

bool Sistema::tamUsuarios(int nuevo){
    if (nuevo <= capacidadUsuarios) return true;
    Usuarios** aux = new Usuarios*[nuevo];
    for (int i = 0; i < numUsuarios; i++)aux[i] = usuarios[i];
    for (int i = numUsuarios;i < nuevo; i++ )aux[i] = nullptr;
    delete[] usuarios;
    usuarios = aux;
    capacidadUsuarios = nuevo;
    return true;
}


/*===========================================================================
 * agregarUsuario: metodo que se encarga de agregar un usuario registrado
 ========================================================================*/

bool Sistema::agregarUsuario(Usuarios* u) {
    if (!u) return false;
    if (numUsuarios >= capacidadUsuarios) {
        int nuevoTam = (capacidadUsuarios == 0) ? 4 : capacidadUsuarios * 2;
        if (!tamUsuarios(nuevoTam)) {
            cout << "Error: No se pudo reservar memoria para usuarios\n";
            return false;
        }
    }
    usuarios[numUsuarios++] = u;
    return true;
}

/*=============================================================================
 * IniciarSesion: Metodo que revisa que el usuario este registrado en el sistema
 *
 *
=============================================================================*/

Usuarios* Sistema::iniciarSesion(const char* nickName){
    if(!nickName) return nullptr;
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i] && usuarios[i]->getusuarios()){
            if(strcmp(usuarios[i]->getusuarios(),nickName) == 0){
                return usuarios[i];
            }
        }
    }
    return nullptr;
}

/*===================================================================
 * cargarDatos: lee archivos
 * formato de cada linea: usuarios;membresia;ciudad;pais;fechaDeRegistro
 ============================================================================*/

void Sistema::cargarDatos(){
    const char* ruta = "database/usuarios.txt";
    FILE* archivo = std::fopen(ruta, "r");

    if(!archivo){
        cout << "No se encontro la ruta (cargarDatos\n";
        return;
    }

    const int TAM = 1024;
    char buffer[TAM];

    while(fgets(buffer,TAM,archivo)){
        size_t tam = strlen(buffer);

        if(tam > 0 && buffer[tam - 1] == '\n') buffer[tam - 1] = '\0';

        if(strlen(buffer) == 0)continue;

        char* copia = new char[strlen(buffer) + 1];
        strcpy(copia, buffer);

        char* separador = std::strtok(copia,";");
        if(!separador){delete[] copia;continue;}
        char* nick = separador;

        separador = std::strtok(nullptr, ";");
        char* membresia = separador ? separador:(char*) "estandar";

        separador = std::strtok(nullptr, ";");
        char* ciudad = separador ? separador:(char*)"";

        separador = std::strtok(nullptr, ";");
        char*pais = separador ? separador:(char*)"";

        separador = std::strtok(nullptr, ";");
        char*fecha = separador ? separador:(char*)"1999-08-14";

        Usuarios* u = new Usuarios(nick,membresia,ciudad,pais,fecha,0);
        if(!agregarUsuario(u)){
            delete u;
        }
        delete[] copia;
    }

    fclose(archivo);
    cout << "Carga de usuarios finalizada(cargarDatos)";
}


/*=========================================================
 * registrarUsuario: metodo por el cual un usuario puede crearse
 * una cuenta de UdeATune
 */

void Sistema::registrarUsuario(){
    const int MAX = 200;
    char nick[MAX], membresia[MAX], ciudad[MAX], pais[MAX], fecha[MAX];

    cout << "REGISTRAR NUEVO USUARIO: " <<endl;

    //Nickname
    do{
        cout << "Nickname (solo letras, numeros, _ o -): ";
        cin.getline(nick, MAX);
        if (esVacio(nick) || !esNickValido(nick) || contieneSeparador(nick))
            cout << "Nickname inválido.\n";
    }while(esVacio(nick) || !esNickValido(nick) || contieneSeparador(nick));

    //Membresia
    while(true){
        cout << "Membresía (Estandar/Premium): ";
        cin.getline(membresia,MAX);
        if (strcmp(membresia,"Estandar") == 0 || strcmp(membresia,"Premium") == 0)
            break;
        cout << "Entrada invalida. Solo se permite 'Estandar' o 'Premium'" <<endl;
    }

    //Ciudad
    do {
        cout << "Ciudad (solo letras y espacios): ";
        cin.getline(ciudad, MAX);
        if (esVacio(ciudad) || !esCiudadValida(ciudad) || contieneSeparador(ciudad))
            cout << "Ciudad invalida.\n";
    } while (esVacio(ciudad) || !esCiudadValida(ciudad) || contieneSeparador(ciudad));

    //Pais
    do {
        cout << "Pais (solo letras y espacios): ";
        cin.getline(pais, MAX);
        if (esVacio(pais) || !esCiudadValida(pais) || contieneSeparador(pais))
            cout << "Pais invalido.\n";
    } while (esVacio(pais) || !esCiudadValida(pais) || contieneSeparador(pais));

    //Fecha
    do {
        cout << "Fecha de registro (YYYY-MM-DD): ";
        cin.getline(fecha, MAX);
        if (!fechaValida(fecha)) cout << "Formato inválido.\n";
    } while (!fechaValida(fecha));

    int capFav = (std::strcmp(membresia, "Premium") == 0) ? 4:0;

    Usuarios* u = new Usuarios(nick, membresia, ciudad , pais, fecha, capFav);
    if(agregarUsuario(u)){
        cout << "Usuario registrado correctamente.\n";

        const char* ruta = "database/usuarios.txt";
        FILE* archivo = std::fopen(ruta, "a");
        if(archivo){
            fprintf(archivo, "%s;%s;%s;%s;%s\n", nick, membresia, ciudad, pais, fecha);
            fclose(archivo);
        }else{
            cout << "No se pudo guardar el archivo en registrarUsuarios\n";
        }
    }else{
        delete u;
    }
}


/*========================================================================
 * guardarUsuarios: funcion que se encarga de actualizar los arreglos
 * de los usuarios
=======================================================================*/

void Sistema::guardarUsuarios(){
    const char* ruta = "database/usuarios.txt";
    FILE* archivo = std::fopen(ruta, "w");

    if(!archivo){
        cout << "No se pudo abrir archivo en -> guardarUsuarios\n";
        return;
    }

    for (int i = 0; i < numUsuarios; i++){
        Usuarios* u = usuarios[i];
        if (!u) continue;

        const char* nick = u->getusuarios() ? u->getusuarios() : "";
        const char* membresia = u->getMembresia() ? u->getMembresia() : "estandar";
        const char* ciudad = u->getCiudad() ? u->getCiudad() : "";
        const char* pais = u->getPais() ? u->getPais() : "";
        const char* fecha = u->getFechaDeRegistro() ? u-> getFechaDeRegistro() : "";

        std::fprintf(archivo, "%s;%s;%s;%s;%s;", nick, membresia, ciudad, pais, fecha);

    }
    std::fclose(archivo);
    cout << "Usuario guardado corectamente\n";
}

void Sistema::imprimirUsuarios(){
    std::cout << "=== Lista de usuarios (" << numUsuarios << ") ===\n";
    for (int i = 0; i < numUsuarios; ++i) {
        Usuarios* u = usuarios[i];
        if (!u) continue;
        const char* nick = u->getusuarios() ? u->getusuarios() : "(sin nick)";
        const char* mem = u->getMembresia() ? u->getMembresia() : "(sin membresia)";
        std::cout << (i+1) << ". " << nick << "  [" << mem << "]\n";
    }
    std::cout << "===============================\n";
}

/*===========================================================================
 * buscarCancion: busca en el arreglo canciones
====================================================================== */

Cancion* Sistema::buscarCancionId(long id) {
    if (!canciones) return nullptr;
    for (int i = 0; i < numCanciones; ++i) {
        if (canciones[i] && canciones[i]->getId() == id) return canciones[i];
    }
    return nullptr;
}

/*=====================================================================
  reproduccionAleatoria y medirRecursos:
=====================================================================*/
void Sistema::reproduccionAleatoria(class Usuarios* u, int k) {
    // Implementar lógica
    cout << "reproduccionAleatoria: en desarrollo (k=" << k << ")\n";
}

void Sistema::medirRecursos() {
    cout << "medirRecursos: en desarrollo\n";
}



