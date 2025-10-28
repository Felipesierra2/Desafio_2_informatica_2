#include "Sistema.h"
#include "Artista.h"
#include "auxiliares.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <sstream>


using namespace std;
Sistema::Sistema() {
    usuarioAutenticado = nullptr;
    gestionarUsuarios = new GestionarUsuarios();
    gestionarCanciones = new GestionarCanciones();
    gestionarPublicidad = new GestionarPublicidad();
    cancionesReproducidasSesion = 0;
    ultimoAnuncioMostradoId = -1;
    std::srand((unsigned int)time(nullptr));

    gestionarPublicidad->agregarPublicidad(Publicidad(1, "Compra 1 lleva 2", 'C'));
    gestionarPublicidad->agregarPublicidad(Publicidad(2, "Descuento 20% en audífonos", 'B'));
    gestionarPublicidad->agregarPublicidad(Publicidad(3, "Oferta exclusiva premium!", 'A'));

}

void Sistema::reiniciarContadoresSesion() {
    cancionesReproducidasSesion = 0;
    ultimoAnuncioMostradoId = -1;
}

std::string Sistema::seleccionarAnuncioAleatorio() {
    int total = gestionarPublicidad->getCantidad();
    if (total == 0) return std::string();

    int pesoTotal = 0;
    for (int i = 0; i < total; ++i) {
        Publicidad* p = gestionarPublicidad->getPublicidad(i);
        pesoTotal += p->getPrioridad();
    }
    if (pesoTotal == 0) return std::string();

    int* pool = new int[pesoTotal];
    int pos = 0;
    for (int i = 0; i < total; ++i) {
        int peso = gestionarPublicidad->getPublicidad(i)->getPrioridad();
        for (int j = 0; j < peso; ++j) pool[pos++] = i;
    }

    const int MAX_TRIES = 10;
    std::string seleccionado = std::string();
    int idSeleccionado = -1;

    for (int intento = 0; intento < MAX_TRIES; ++intento) {
        int idxPool = std::rand() % pesoTotal;
        int index = pool[idxPool];
        Publicidad* p = gestionarPublicidad->getPublicidad(index);
        int pid = p->getId();
        if (pid != ultimoAnuncioMostradoId) {
            seleccionado = p->getMensaje();
            idSeleccionado = pid;
            break;
        }
        if (intento == MAX_TRIES - 1) {

            seleccionado = p->getMensaje();
            idSeleccionado = pid;
        }
    }

    delete[] pool;
    if (idSeleccionado != -1) ultimoAnuncioMostradoId = idSeleccionado;
    return seleccionado;
}

void Sistema::reproducirConAnuncios(Usuarios* usuario, long id) {
    if (!gestionarCanciones) {
        std::cout << "Error: gestor de canciones no inicializado.\n";
        return;
    }

    gestionarCanciones->reproducirCancion(id);

    cancionesReproducidasSesion++;

    std::string tipo = usuario->getMembresia();
    bool esPremium = (tipo == "Premium" || tipo == "premium");
    if (esPremium) {

        Cancion* c = gestionarCanciones->buscarPorId(id);
        if (c) {
            std::cout << "Reproducción completada (Premium). Veces reproducida ahora: " << c->getVecesReproducida() << "\n";
            std::cout << "Calidad: 320 kbps\n";
        }
        return;
    }


    if ((cancionesReproducidasSesion % 2) == 0) {
        std::string anuncio = seleccionarAnuncioAleatorio();
        if (!anuncio.empty()) {
            if (anuncio.length() <= 500) {
                std::cout << "\n--- Anuncio ---\n" << anuncio << "\n---------------\n";
            } else {
                std::cout << "\n--- Anuncio ---\n" << anuncio.substr(0, 500) << "\n---------------\n";
            }
        }
    }
    Cancion* c = gestionarCanciones->buscarPorId(id);
    if (c) {
        std::cout << "Veces reproducida ahora: " << c->getVecesReproducida() << "\n";
        std::cout << "Calidad: 128 kbps\n";
    }
}

void Sistema::ejecutarAplicacion() {
    int opcion;
    cargarUsuarios();
    do {
        mostrarMenuPrincipal();
        cout << "Seleccione una opción: ";
        int opcion = leerOpcion();

        switch (opcion) {
        case 1:
            manejarRegistro();
            break;
        case 2:
            manejarLogin();
            break;
        case 3:
            gestionarUsuarios->MostrarUsuarios();
            break;
        case 0:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 0);
}

void Sistema::mostrarMenuPrincipal() {
    cout << "\n=== MENÚ PRINCIPAL ===\n";
    cout << "1. Registrar nuevo usuario\n";
    cout << "2. Iniciar sesión\n";
    cout << "3. Mostrar todos los usuarios\n";
    cout << "0. Salir\n";
}

void Sistema::manejarRegistro() {
    string usuario, membresia, ciudad, pais, fecha;

    do {
        cout << "Nombre de usuario (1-15 caracteres): ";
        getline(cin, usuario);
        if (usuario.empty() || usuario.length() >= 15)
            cout << "Longitud inválida. Debe tener entre 1 y 15 caracteres.\n";
    } while (usuario.empty() || usuario.length() >= 15);

    do {
        cout << "Membresía (premium/estandar): ";
        getline(cin, membresia);
        if (!validarMembresia(membresia))
            cout << "Opción inválida. Solo se acepta 'premium' o 'estandar'.\n";
    } while (!validarMembresia(membresia));

    do {
        cout << "Ciudad: ";
        getline(cin, ciudad);
        if (!validarTexto(ciudad))
            cout << "La ciudad solo puede contener letras y espacios.\n";
    } while (!validarTexto(ciudad));

    do {
        cout << "País: ";
        getline(cin, pais);
        if (!validarTexto(pais))
            cout << "El país solo puede contener letras y espacios.\n";
    } while (!validarTexto(pais));

    fecha = "";

    bool exito = gestionarUsuarios->Registrarse(usuario, membresia, ciudad, pais, fecha);

    if (exito)
        cout << "Usuario registrado correctamente.\n";
    else
        cout << "No se pudo registrar el usuario.\n";
}

void Sistema::manejarLogin() {
    std::string nombre;
    std::cout << "\n--- INICIO DE SESIÓN ---\n";
    std::cout << "Ingrese su nombre de usuario: ";
    std::getline(std::cin, nombre);

    Usuarios* usuario = gestionarUsuarios->Login(nombre);

    if (usuario != nullptr) {
        usuarioAutenticado = usuario;
        usuarioAutenticado->cargarFavoritosDesdeArchivo();
        mostrarMenuUsuario(usuarioAutenticado);

    } else {
        char respuesta;
        std::cout << "Usuario no encontrado. ¿Desea registrarse? (s/n): ";
        std::cin >> respuesta;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (respuesta == 's' || respuesta == 'S') {
            manejarRegistro();
        }
    }


}

void Sistema::mostrarMenuUsuario(Usuarios* usuario) {
    if (usuario == nullptr) {
        std::cout << "Error: no hay usuario activo.\n";
        return;
    }

    reiniciarContadoresSesion();

    std::string tipo = usuario->getMembresia();
    bool esPremium = (tipo == "Premium" || tipo == "premium" || tipo == "PREMIUM");

    int opcion = -1;
    while (true) {
        std::cout << "\n===== MENÚ DE USUARIO =====\n";
        std::cout << "Usuario: " << usuario->getusuarios() << "    Membresía: " << tipo << "\n\n";
        std::cout << "1. Listar canciones disponibles\n";
        std::cout << "2. Reproducir canción por ID\n";
        std::cout << "3. Agregar canción a Favoritos\n";
        std::cout << "4. Ver lista de Favoritos\n";
        std::cout << "5. Seguir lista de favoritos de otro usuario premium\n";
        std::cout << "6. Información de membresía / beneficios\n";
        std::cout << "7. Eliminar de favoritos\n";

        std::cout << "Seleccione una opción: ";
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 1) {
            if (gestionarCanciones) {
                gestionarCanciones->listarTodas();
            } else {
                std::cout << "Error: gestor de canciones no disponible.\n";
            }
        }
        else if (opcion == 2) {
            long id;
            std::cout << "Ingrese ID de la canción a reproducir: ";
            if (!(std::cin >> id)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ID inválido.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            reproducirConAnuncios(usuario, id);
        }
        else if (opcion == 3) {
            if(!esPremium){
                std::cout << "Solo los usuarios Premium pueden realizar esta acción. " <<std::endl;
                continue;
            }

            std::cout << "Ingrese el ID de la cancion: ";
            long id;

            if (!(std::cin >> id)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ID inválido.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Cancion* cancion = gestionarCanciones->buscarPorId(id);
            if (cancion == nullptr) {
                std::cout << "No existe una canción con ese ID.\n";
                continue;
            }

            bool ok = usuario->addFavorito(id);
            if (ok){
                usuario->guardarFavoritoEnArchivo(id, cancion);
                std::cout << "Canción agregada a Favoritos.\n";
            }else std::cout << "No se pudo agregar. ¿ID existe o ya está en favoritos? ¿Límite alcanzado?\n";
        }
        else if (opcion == 4) {
            if(!esPremium){
                std::cout << "Solo los usuarios Premium pueden realizar esta acción. " <<std::endl;
                continue;
            }
            this->verFavoritos(usuario);
        }
        else if (opcion == 5) {
            if(!esPremium){
                std::cout << "Solo los usuarios Premium pueden realizar esta acción. " <<std::endl;
                continue;
            }
            std::string otroUsuarioNick;
            std::cout << "Ingrese el nombre/usuario de la persona a seguir: ";
            std::getline(std::cin, otroUsuarioNick);
            if (otroUsuarioNick.empty()) {
                std::cout << "Nombre vacío.\n";
                continue;
            }

            Usuarios* otro = gestionarUsuarios->buscarPorUsuario(otroUsuarioNick);
            if (otro == nullptr) {
                std::cout << "Usuario no encontrado.\n";
                continue;
            }

            std::string tipoOtro = otro->getMembresia();
            bool otroEsPremium = (tipoOtro == "Premium" || tipoOtro == "premium" || tipoOtro == "PREMIUM");
            if (!otroEsPremium) {
                std::cout << "Solo puedes seguir la lista de favoritos de usuarios premium.\n";
                continue;
            }

            bool ok = usuario->seguirListaDe(otro);
            if (ok){
                seguirListaDeOtroUsuario(usuario, otro);
                std::cout << "Ahora sigues la lista de favoritos de " << otro->getusuarios() << ".\n";
            }
            else std::cout << "No fue posible seguir la lista.\n";

        }
        else if (opcion == 6) {
            std::cout << "\n--- Beneficios de la membresía ---\n";
            if (esPremium) {
                std::cout << "Premium (pago mensual 19900 COP):\n";
                std::cout << " - Lista de favoritos personalizada (hasta 10000 canciones)\n";
                std::cout << " - Seguir en tiempo real la lista de favoritos de otro usuario premium\n";
                std::cout << " - Calidad de audio: 320 kbps\n";
                std::cout << " - Reproducción sin publicidad\n";
            } else {
                std::cout << "Estándar (gratuito):\n";
                std::cout << " - Calidad de audio: 128 kbps\n";
                std::cout << " - Cada 2 canciones reproducidas verás un anuncio (máx 500 caracteres)\n";
            }
            std::cout << "----------------------------------\n";
        }
        else if (opcion == 7) {
            eliminarFavorito(usuario);
            std::cout << "Eliminando de favoritos..\n";
        }else if(opcion == 8){
            reiniciarContadoresSesion();
        }
        else {
            std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }
}


void Sistema::buscarCancionPorNombre() {
    if (!gestionarCanciones) {
        cout << "Error: gestor de canciones no inicializado.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la canción: ";
    getline(cin, nombre);

    Cancion* c = gestionarCanciones->buscarPorNombre(nombre);
    if (!c) {
        cout << "No se encontró ninguna canción con ese nombre.\n";
        return;
    }

    cout << "\n=== Canción encontrada ===\n";
    c->mostrarCancion();
    c->mostrarCreditos();
}

void Sistema::buscarCancionPorId() {
    if (!gestionarCanciones) {
        cout << "Error: gestor de canciones no inicializado.\n";
        return;
    }

    long id;
    cout << "Ingrese el ID de la canción: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Cancion* c = gestionarCanciones->buscarPorId(id);
    if (!c) {
        cout << "No se encontró ninguna canción con ese ID.\n";
        return;
    }

    cout << "\n=== Canción encontrada ===\n";
    c->mostrarCancion();
    c->mostrarCreditos();
}

void Sistema::reproducirCancionUsuario(Usuarios* usuario) {
    if (!gestionarCanciones) {
        cout << "Error: gestor de canciones no inicializado.\n";
        return;
    }

    long id;
    cout << "Ingrese el ID de la canción a reproducir: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Cancion* c = gestionarCanciones->buscarPorId(id);
    if (!c) {
        cout << "No se encontró ninguna canción con ese ID.\n";
        return;
    }

    gestionarCanciones->reproducirCancion(id);

    cout << "Reproducción completada.\n";
    cout << "Veces reproducida ahora: " << c->getVecesReproducida() << "\n";
}

void Sistema::verFavoritos(Usuarios* usuario) {
    usuario->cargarFavoritosDesdeArchivo();
    if (usuario == nullptr) {
        std::cout << "Error: usuario no válido.\n";
        return;
    }

    Usuarios* origen = usuario;
    Usuarios* seguido = usuario->getUsuarioQueSigue();

    if (seguido != nullptr) {
        std::cout << "Mostrando tus favoritos combinados con los de " << seguido->getNombre() << ":\n";
        for (int i = 0; i < seguido->getCantidadFavoritos(); ++i) {
            long id = seguido->getFavorito(i);
            if (usuario->addFavorito(id)) {
                Cancion* c = gestionarCanciones->buscarPorId(id);
                usuario->guardarFavoritoEnArchivo(id, c);
            }
        }
    }


    int cantidad = origen->getCantidadFavoritos();
    if (cantidad == 0) {
        std::cout << "No hay canciones favoritas para mostrar.\n";
        return;
    }

    std::cout << "\n=== FAVORITOS ===\n";
    for (int i = 0; i < cantidad; ++i) {
        long idCancion = origen->getFavorito(i);
        Cancion* c = gestionarCanciones->buscarPorId(idCancion);
        if (c != nullptr) {
            std::cout << (i + 1) << ". " << c->getNombre()
            << " (" << c->getDuracion() << " min, "
            << c->getVecesReproducida() << " rep.)\n";
        } else {
            std::cout << (i + 1) << ". ID " << idCancion << " (no encontrado)\n";
        }
    }
    std::cout << "=================\n";
}


void Sistema::agregarFavorito(Usuarios* usuario) {
    if (usuario == nullptr) {
        std::cout << "Error: usuario no válido.\n";
        return;
    }

    long id;
    std::cout << "Ingrese el ID de la canción que desea agregar a favoritos: ";
    std::cin >> id;

    Cancion* cancion = gestionarCanciones->buscarPorId(id);
    if (cancion == nullptr) {
        std::cout << "No se encontró una canción con ese ID.\n";
        return;
    }

    if (usuario->addFavorito(id)) {
        usuario->guardarFavoritoEnArchivo(id, cancion);
        std::cout << "Canción agregada a tus favoritos.\n";
    } else {
        std::cout << "Esa canción ya está en tus favoritos.\n";
    }
}

void Sistema::eliminarFavorito(Usuarios* usuario){
    if (usuario == nullptr) {
        std::cout << "Error: usuario no válido.\n";
        return;
    }

    long id;
    std::cout << "Ingrese el ID de la canción que desea eliminar de favoritos: ";
    std::cin >> id;

    usuario->eliminarFavorito(id);
}

void Sistema::seguirListaDeOtroUsuario(Usuarios* actual, Usuarios* otro) {
    if (!actual || !otro) {
        std::cout << "Error: usuarios inválidos.\n";
        return;
    }
    if (actual == otro) {
        std::cout << "No puedes seguirte a ti mismo.\n";
        return;
    }
    if (otro->getMembresia() != "Premium" && otro->getMembresia() != "premium") {
        std::cout << "Solo puedes seguir listas de usuarios Premium.\n";
        return;
    }

    if (!actual->seguirListaDe(otro)) {
        std::cout << "No se pudo establecer el seguimiento.\n";
        return;
    }

    std::cout << actual->getNombre() << " ahora sigue la lista de " << otro->getNombre() << ".\n";
    {
        std::ofstream out("database/seguimientos.txt", std::ios::app);
        if (!out) {
            std::cout << "Error: no se pudo abrir seguimientos.txt\n";
        } else {
            out << actual->getNombre() << ";" << otro->getNombre() << "\n";
            out.close();
        }
    }
    std::cout << "Cantidad favoritos: " << otro->getCantidadFavoritos() << std::endl;
    for (int i = 0; i < otro->getCantidadFavoritos(); ++i) {
        long idCancion = otro->getFavorito(i);

        if (actual->addFavorito(idCancion)) {
            Cancion* c = gestionarCanciones->buscarPorId(idCancion);
            actual->guardarFavoritoEnArchivo(idCancion, c);
        }
    }
}


Usuarios* Sistema::buscarUsuarioPorNombre(const std::string& nombre) {
    int pos = gestionarUsuarios->BuscarUsuario(nombre);
    if (pos != -1)
        return gestionarUsuarios->getUsuario(pos);
    return nullptr;
}

void Sistema::cargarUsuarios() {
    const char* ruta = "database/usuarios.txt";
    std::ifstream in(ruta);

    if (!in) {
        std::cout << "Advertencia: no se encontró el archivo de usuarios (" << ruta << ").\n";
        return;
    }

    std::string linea;
    bool primera = true;
    int cargados = 0;

    while (std::getline(in, linea)) {
        if (primera) {
            primera = false;
            continue;
        }

        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string usuario, membresia, ciudad, pais, fecha, seguido;

        std::getline(ss, usuario, ';');
        std::getline(ss, membresia, ';');
        std::getline(ss, ciudad, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, fecha, ';');
        std::getline(ss, seguido, ';');

        std::string extra;
        std::getline(ss, extra, ';');

        Usuarios* nuevo = new Usuarios(usuario, membresia, ciudad, pais, fecha);
        gestionarUsuarios->agregarUsuario(nuevo);
        cargados++;
    }

    in.close();

    std::cout << "Usuarios cargados correctamente: " << cargados << "\n";

    cargarSeguimientos();
}


void Sistema::cargarSeguimientos() {
    std::ifstream in("database/seguimientos.txt");
    if (!in) {
        return;
    }

    std::string linea;
    while (std::getline(in, linea)) {
        if (linea.empty()) continue;

        size_t sep = linea.find(';');
        if (sep == std::string::npos) continue;
        std::string seguidor = linea.substr(0, sep);
        std::string seguido = linea.substr(sep + 1);

        Usuarios* uSeguidor = gestionarUsuarios->buscarPorUsuario(seguidor);
        Usuarios* uSeguido  = gestionarUsuarios->buscarPorUsuario(seguido);
        if (!uSeguidor || !uSeguido) continue;

        uSeguidor->seguirListaDe(uSeguido);

        for (int i = 0; i < uSeguido->getCantidadFavoritos(); ++i) {
            long id = uSeguido->getFavorito(i);
            if (uSeguidor->addFavorito(id)) {
                Cancion* c = gestionarCanciones->buscarPorId(id);
                uSeguidor->guardarFavoritoEnArchivo(id, c);
            }
        }
    }
    in.close();
}











