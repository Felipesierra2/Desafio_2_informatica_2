#include <iostream>
#include "Sistema.h"
#include <windows.h>


using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Sistema* sistema = new Sistema();
    sistema->ejecutarAplicacion();
    return 0;
}
