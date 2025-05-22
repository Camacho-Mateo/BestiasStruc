#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <string>
using namespace std;

class Validador {
public:
    static bool validarNombre(const string& nombre);
    static bool validarApellido(const string& apellido);
    static bool validarCedula(const string& cedula);
    static bool validarCorreo(const string& correo);
    static bool validarTelefono(const string& telefono);
};

#endif
