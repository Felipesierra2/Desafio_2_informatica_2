#include <iostream>
#include "Sistema.h"
#include "auxiliares.h"
using namespace std;



/*========================================================================
 *Funcion que se encarga de revisar que el numero sea un enetero
 pasamos el valor ingresado por el usuario en la variable opcion, revisamos
que el cin corresponda al tipo de dato solicitado, en caso de error
returnamos -1 para repetir la peticion y enviarle un mensje al...
 */

int leerOpcion() {
    int opcion;
    cin >> opcion;
    if (cin.fail()) {
        cin.clear();
        limpiarBuffer();
        return -1;
    }
    limpiarBuffer();
    return opcion;
}

/*==============================================================================
 * mostrarMenu: Funcion que interactua con el usuario, en esta se llaman los metodos
 que contienen las funcionalidades principales del codigo, como las siguientes:

***Registrar usuarios***
***Iniciar seccion***
 */

void mostrarMenu(Sistema &s) {
    int opcion = 0;
    bool salir = false;

    while (!salir) {
        cout << "\n=== MENU PRINCIPAL ===" << endl;
        cout << "1. Registrar usuario" << endl;
        cout << "2. Iniciar sesion" << endl;
        cout << "3. Reproduccion aleatoria" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";

        opcion = leerOpcion();

        if (opcion == -1) {
            cout << "Error: Por favor ingrese un numero valido." << endl;
            continue;
        }

        if (opcion < 1 || opcion > 4) {
            cout << "Opcion invalida. Por favor seleccione entre 1 y 4." << endl;
            continue;
        }

        switch (opcion) {
        case 1:
            s.registrarUsuario();
            break;
        case 2: {
            char nickname[100];
            cout << "Ingrese su nickname: ";
            cin.getline(nickname, 100);

            Usuarios* usuario = s.iniciarSesion(nickname);
            if (usuario != nullptr) {
                cout << "¡Sesion iniciada correctamente!" << endl;
            } else {
                cout << "Usuario no encontrado." << endl;
            }
            break;
        }
        case 3:
            cout << "Funcionalidad de reproduccion aleatoria en desarrollo..." << endl;
            break;
        case 4:
            salir = true;
            cout << "¡Hasta pronto!" << endl;
            break;
        }
    }
}

