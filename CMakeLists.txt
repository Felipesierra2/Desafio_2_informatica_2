cmake_minimum_required(VERSION 3.16)

project(desafio_2_informatica_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(desafio_2_informatica_2 main.cpp
    menu.h menu.cpp
    publicidad.h publicidad.cpp
    credito.h credito.cpp
    cancion.h cancion.cpp
    album.h album.cpp
    Artista.h Artista.cpp
    usuario.h usuario.cpp
    Sistema.h Sistema.cpp)

include(GNUInstallDirs)
install(TARGETS desafio_2_informatica_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
