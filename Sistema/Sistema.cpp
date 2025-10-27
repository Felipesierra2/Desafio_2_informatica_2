#include "Sistema.h"
#include "Artista.h"
#include "auxiliares.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>


using namespace std;
Sistema::Sistema() {
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
    int opcion = 0;
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
            cout << "Longitud inválida. Debe tener entre 1 y 9 caracteres.\n";
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
        std::cout << "7. Cerrar sesión\n";
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

            bool ok = usuario->addFavorito(id);
            if (ok) std::cout << "Canción agregada a Favoritos.\n";
            else std::cout << "No se pudo agregar. ¿ID existe o ya está en favoritos? ¿Límite alcanzado?\n";
        }
        else if (opcion == 4) {
            this->verFavoritos(usuario);
        }
        else if (opcion == 5) {
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
            if (ok) std::cout << "Ahora sigues la lista de favoritos de " << otro->getusuarios() << ".\n";
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
            std::cout << "Cerrando sesión...\n";
            reiniciarContadoresSesion();
            break;
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
    if (usuario == nullptr) {
        std::cout << "Error: usuario no válido.\n";
        return;
    }

    int cantidad = usuario->getCantidadFavoritos();
    if (cantidad == 0) {
        std::cout << "No tienes canciones favoritas aún.\n";
        return;
    }

    std::cout << "\n=== TUS CANCIONES FAVORITAS ===\n";
    for (int i = 0; i < cantidad; ++i) {
        long idCancion = usuario->getFavorito(i);
        Cancion* c = gestionarCanciones->buscarPorId(idCancion);

        if (c != nullptr) {
            std::cout << (i + 1) << ". " << c->getNombre()
            << " (" << c->getDuracion() << " min, "
            << c->getVecesReproducida() << " reproducciones)\n";
        } else {
            std::cout << (i + 1) << ". ID " << idCancion << " (no encontrado)\n";
        }
    }
    std::cout << "===============================\n";
}








