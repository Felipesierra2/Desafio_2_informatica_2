#include "auxiliares.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

using namespace std;


/**/

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

/*========================================================================
 Duncion que se encarga de limpiar la basura del buffer
 */

bool validarTexto(const string& texto) {
    if (texto.empty()) return false;
    for (char c : texto) {
        if (!isalpha(static_cast<unsigned char>(c)) && !isspace(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

bool validarMembresia(const string& membresia) {
    string m = membresia;
    // Pasar a minúsculas
    for (char& c : m) c = tolower(static_cast<unsigned char>(c));
    return (m == "premium" || m == "estandar");
}


