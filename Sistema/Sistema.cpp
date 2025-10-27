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

void Sistema::mostrarMenuUsuario(Usuarios* usuario){
    if (usuarioAutenticado == nullptr) {
        std::cout << "Error: no hay usuario activo.\n";
        return;
    }

    std::string tipo = usuarioAutenticado->getMembresia();
    bool esPremium = (tipo == "Premium" || tipo == "premium");

    int opcion = -1;
    do {
        std::cout << "\n========================================\n";
        std::cout << "    🎧 MENU DE USUARIO - " << usuarioAutenticado->getusuarios() << "\n";
        std::cout << "    Tipo de membresía: " << tipo << "\n";
        std::cout << "========================================\n";

        std::cout << "1. Buscar canción por nombre\n";
        std::cout << "2. Buscar canción por ID\n";
        std::cout << "3. Reproducir canción\n";

        if (esPremium) {
            std::cout << "4. Agregar canción a favoritos\n";
            std::cout << "5. Ver lista de favoritos\n";
            std::cout << "6. Seguir lista de otro usuario Premium\n";
        } else {
            std::cout << "4. Ver anuncios pendientes\n";
        }

        std::cout << "0. Cerrar sesión\n";
        std::cout << "Seleccione una opción: ";

        opcion = leerOpcion();

        switch (opcion) {
        case 1:
            std::cout << "\n(Buscar canción por nombre)\n";
            break;

        case 2:
            std::cout << "\n(Buscar canción por ID)\n";
            break;

        case 3:
            std::cout << "\n(Reproducir canción)\n";
            break;

        case 4:
            if (esPremium) {
                std::cout << "\n(Agregar canción a favoritos)\n";
            } else {
                std::cout << "\n(Mostrar anuncios)\n";
            }
            break;

        case 5:
            if (esPremium) {
                std::cout << "\n(Mostrar lista de favoritos)\n";
            } else {
                std::cout << "Opción inválida.\n";
            }
            break;

        case 6:
            if (esPremium) {
                std::cout << "\n(Seguir lista de otro usuario Premium)\n";
            } else {
                std::cout << "Opción inválida.\n";
            }
            break;

        case 0:
            std::cout << "Cerrando sesión...\n";
            break;

        default:
            std::cout << "Opción inválida, intente de nuevo.\n";
        }

    } while (opcion != 0);

    usuarioAutenticado = nullptr; // limpiar sesión al salir
}
