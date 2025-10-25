#include "auxiliares.h"
#include <iostream>
#include <cstring>

using namespace std;


/*========================================================================
 Duncion que se encarga de limpiar la basura del buffer
 */

void limpiarBuffer() {
    while (cin.get() != '\n') {
    }
}

bool esVacio(const char* correct) {
    for (int i = 0; correct[i] != '\0'; i++) {
        if (!isspace(correct[i])) return false; // hay algo distinto de espacio
    }
    return true;
}

bool contieneSeparador(const char* correct) {
    for (int i = 0; correct[i] != '\0'; i++) {
        if (correct[i] == ';') return true;
    }
    return false;
}

bool caracteresValidos(const char* texto, bool permitirNumeros, bool permitirGuionBajo) {
    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char c = texto[i];

        if (isalpha(c)) continue;
        if (isspace(c)) continue;
        if (permitirNumeros && isdigit(c)) continue;
        if (permitirGuionBajo && (c == '_' || c == '-')) continue;
        return false;
    }
    return true;
}

bool fechaValida(const char* fecha){
    if(fecha == nullptr) return false;

    if(std::strlen(fecha) != 10) return false;

    if (fecha[4] != '-' || fecha[7] != '-') return false;

    for (int i = 0; i < 10; i++){
        if(i == 4 || i == 7)continue;
        if(!std::isdigit(static_cast<unsigned char>(fecha[i]))) return false;
    }

    int year = (fecha[0] - '0')*1000 + (fecha[1] - '0')*100 + (fecha[2] - '0')*10 + (fecha[3] - '0');
    int mes = (fecha[5]-'0')*10 + (fecha[6]-'0');
    int dia = (fecha[8]-'0')*10 + (fecha[9]-'0');

    if(year < 1900 || year > 2026)return false;
    if(mes < 1 || mes > 12)return false;
    if(dia < 1 ) return false;

    int diasMes = 31;
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11 ) diasMes = 30;
    else if(mes == 2){

        bool bisiesto = (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
        diasMes = bisiesto ? 29:28;
    }

    if (dia > diasMes) return false;

    return true;
}


