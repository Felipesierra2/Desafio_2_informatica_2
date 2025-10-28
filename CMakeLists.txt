cmake_minimum_required(VERSION 3.16)

project(desafio_2_informatica_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    Sistema
    Clases
    Interfaz
)

add_executable(desafio_2_informatica_2
    main.cpp
    Clases/Publicidad.h Clases/Publicidad.cpp
    Clases/Credito.h Clases/Credito.cpp
    Clases/Cancion.h Clases/Cancion.cpp
    Clases/Album.h Clases/Album.cpp
    Clases/Artista.h Clases/Artista.cpp
    Clases/Usuarios.h Clases/Usuarios.cpp
    Sistema/Sistema.h Sistema/Sistema.cpp
    Sistema/auxiliares.h Sistema/auxiliares.cpp
    Sistema/GestionarUsuarios.h Sistema/GestionarUsuarios.cpp
    Sistema/GestionarCanciones.h Sistema/GestionarCanciones.cpp
    Sistema/GestionarPublicidad.h Sistema/GestionarPublicidad.cpp

)


include(GNUInstallDirs)
install(TARGETS desafio_2_informatica_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
