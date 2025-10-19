#include <iostream>
#include "Sistema.h"

using namespace std;

void mostrarMenu(Sistema &s) {
    int opcion = 0;
    do {
        cout << "\n===== UdeATunes =====\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Listar usuarios\n";
        cout << "3. Buscar cancion\n";
        cout << "4. Reproducir cancion\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: s.registrarUsuario(); break;
        case 2: s.listarUsuarios(); break;
        case 3: s.buscarCancion(); break;
        case 4: s.reproducirCancion(); break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida.\n"; break;
        }
    } while(opcion != 0);
}

