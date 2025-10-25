#ifndef AUXILIARES_H
#define AUXILIARES_H

void limpiarBuffer();
bool esVacio(const char* correct);
bool contieneSeparador(const char* correct);
bool caracteresValidos(const char* texto, bool permitirNumeros, bool permitirGuionBajo);
bool fechaValida(const char* fecha);

#endif // AUXILIARES_H
