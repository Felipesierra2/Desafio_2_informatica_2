#include "GestionarUsuarios.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>



GestionarUsuarios::GestionarUsuarios()
{
    listaUsuarios = nullptr;
    cantidadUsuarios = 0;
    capacidadMaxima = 10;

    listaUsuarios = new Usuarios*[capacidadMaxima];

    CargarUsuarios();
}

GestionarUsuarios::~GestionarUsuarios()
{
    if (listaUsuarios != nullptr)
    {
        for (int i = 0; i < cantidadUsuarios; i++)
        {
            delete listaUsuarios[i];
        }
        delete[] listaUsuarios;
    }
}

void GestionarUsuarios::CargarUsuarios()
{
    std::ifstream archivo("database/usuarios.txt");

    if (!archivo.is_open())
    {
        std::cout << "Archivo usuarios.txt no encontrado. Se creará uno nuevo al guardar." << std::endl;
        return;
    }

    std::string linea;

    std::getline(archivo, linea);

    while (std::getline(archivo, linea))
    {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string usuario, membresia, ciudad, pais, fecha;

        std::getline(ss, usuario, ';');
        std::getline(ss, membresia, ';');
        std::getline(ss, ciudad, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, fecha, ';');

        if (cantidadUsuarios >= capacidadMaxima)
        {
            RedimensionarArreglo();
        }

        listaUsuarios[cantidadUsuarios] = new Usuarios(usuario, membresia, ciudad, pais, fecha);
        cantidadUsuarios++;
    }

    archivo.close();

    std::cout << "Se cargaron " << cantidadUsuarios << " usuarios correctamente." << std::endl;
}

void GestionarUsuarios::GuardarUsuarios()
{
    std::ofstream archivo("database/usuarios.txt");

    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo crear el archivo usuarios.csv" << std::endl;
        return;
    }


    archivo << "usuarios;membresia;ciudad;pais;fechaDeRegistro" << std::endl;

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        archivo << listaUsuarios[i]->getusuarios() << ";"
                << listaUsuarios[i]->getMembresia() << ";"
                << listaUsuarios[i]->getCiudad() << ";"
                << listaUsuarios[i]->getPais() << ";"
                << listaUsuarios[i]->getFechaDeRegistro() << std::endl;
    }

    archivo.close();
    std::cout << "Usuarios guardados correctamente en la base de datos." << std::endl;
}

Usuarios *GestionarUsuarios::Login(std::string nombreUsuario)
{
    int indice = BuscarUsuario(nombreUsuario);

    if (indice != -1)
    {
        std::cout << "¡Bienvenido " << nombreUsuario << "!" << std::endl;
        std::cout << "Membresía: " << listaUsuarios[indice]->getMembresia() << std::endl;
        std::cout << "Ciudad: " << listaUsuarios[indice]->getCiudad() << std::endl;

        return listaUsuarios[indice];
    }
    else
    {
        std::cout << "Usuario no encontrado. Por favor regístrate." << std::endl;
        return nullptr;
    }
}

bool GestionarUsuarios::Registrarse(std::string usuarios, std::string membresia,
                                    std::string ciudad, std::string pais, std::string fecha)
{
    if (BuscarUsuario(usuarios) != -1)
    {
        std::cout << "Error: El usuario '" << usuarios << "' ya existe." << std::endl;
        return false;
    }

    if (membresia != "premium" && membresia != "Premium" &&
        membresia != "estandar" && membresia != "Estandar")
    {
        std::cout << "Error: La membresía debe ser 'premium' o 'estandar'." << std::endl;
        return false;
    }

    if (cantidadUsuarios >= capacidadMaxima)
    {
        RedimensionarArreglo();
    }

    std::string fechaRegistro = fecha;
    if (fecha.empty())
    {
        time_t ahora = time(0);
        tm* tiempoLocal = localtime(&ahora);
        char buffer[11];
        strftime(buffer, 11, "%Y-%m-%d", tiempoLocal);
        fechaRegistro = buffer;
    }

    listaUsuarios[cantidadUsuarios] = new Usuarios(usuarios, membresia, ciudad, pais, fechaRegistro);
    cantidadUsuarios++;

    GuardarUsuarios();

    std::cout << "¡Usuario '" << usuarios << "' registrado exitosamente!" << std::endl;
    std::cout << "Membresía: " << membresia << std::endl;
    std::cout << "Fecha de registro: " << fechaRegistro << std::endl;

    return true;
}

bool GestionarUsuarios::CambiarMembresia(std::string nombreUsuario, std::string nuevaMembresia)
{
    int indice = BuscarUsuario(nombreUsuario);

    if (indice == -1)
    {
        std::cout << "Error: Usuario '" << nombreUsuario << "' no encontrado." << std::endl;
        return false;
    }

    if (nuevaMembresia != "premium" && nuevaMembresia != "Premium" &&
        nuevaMembresia != "estandar" && nuevaMembresia != "Estandar")
    {
        std::cout << "Error: La membresía debe ser 'premium' o 'estandar'." << std::endl;
        return false;
    }

    std::string membresiaAnterior = listaUsuarios[indice]->getMembresia();

    listaUsuarios[indice]->setMembresia(nuevaMembresia);

    GuardarUsuarios();

    std::cout << "Membresía de '" << nombreUsuario << "' actualizada:" << std::endl;
    std::cout << "  Anterior: " << membresiaAnterior << std::endl;
    std::cout << "  Nueva: " << nuevaMembresia << std::endl;

    return true;
}

int GestionarUsuarios::BuscarUsuario(std::string nombreUsuario)
{
    std::cout << "Cantidad de usuarios: " << cantidadUsuarios << std::endl;
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        std::cout << "Lista usuarios: " <<listaUsuarios[i]->getusuarios() <<std::endl;
        if (listaUsuarios[i]->getusuarios() == nombreUsuario)
        {
            return i;
        }
    }
    return -1;
}

void GestionarUsuarios::RedimensionarArreglo()
{
    capacidadMaxima *= 2;
    Usuarios** nuevoArreglo = new Usuarios*[capacidadMaxima];

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        nuevoArreglo[i] = listaUsuarios[i];
    }

    delete[] listaUsuarios;
    listaUsuarios = nuevoArreglo;

    std::cout << "Arreglo redimensionado a capacidad: " << capacidadMaxima << std::endl;
}

void GestionarUsuarios::MostrarUsuarios()
{
    if (cantidadUsuarios == 0)
    {
        std::cout << "No hay usuarios registrados." << std::endl;
        return;
    }

    std::cout << "\n=== LISTA DE USUARIOS ===" << std::endl;
    std::cout << "Total: " << cantidadUsuarios << " usuarios\n" << std::endl;

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        std::cout << (i + 1) << ". " << listaUsuarios[i]->getusuarios()
        << " | " << listaUsuarios[i]->getMembresia()
        << " | " << listaUsuarios[i]->getCiudad()
        << " | " << listaUsuarios[i]->getPais()
        << " | " << listaUsuarios[i]->getFechaDeRegistro() << std::endl;
    }
    std::cout << std::endl;
}

Usuarios* GestionarUsuarios::buscarPorUsuario(const std::string& usuario) {
    for (int i = 0; i < cantidadUsuarios; ++i) {
        Usuarios* u = listaUsuarios[i];
        if (u != nullptr && u->getusuarios() == usuario) {
            return u;
        }
    }
    return nullptr;
}

int GestionarUsuarios::getCantidadUsuarios() const {
    return cantidadUsuarios;
}

Usuarios* GestionarUsuarios::getUsuario(int index) const {
    if (index >= 0 && index < cantidadUsuarios) {
        return listaUsuarios[index];
    }
    return nullptr;
}

void GestionarUsuarios::agregarUsuario(Usuarios* nuevo) {
    if (cantidadUsuarios >= capacidadMaxima) {
        RedimensionarArreglo();
    }
    listaUsuarios[cantidadUsuarios++] = nuevo;
}

