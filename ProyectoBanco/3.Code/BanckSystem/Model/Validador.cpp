#include "Validador.h"
#include <regex>
using namespace std;

bool Validador::validarNombre(const string& nombre) {
    regex pattern("^[A-Za-záéíóúÁÉÍÓÚñÑ ]+$");
    return regex_match(nombre, pattern);
}

bool Validador::validarApellido(const string& apellido) {
    return validarNombre(apellido);
}

bool Validador::validarCedula(const string& cedula) {
    // Simple validación Ecuador (10 dígitos, primer dígito < 3)
    if (cedula.size() != 10) return false;
    if (cedula[0] < '0' || cedula[0] > '2') return false;
    for (char c : cedula) if (!isdigit(c)) return false;
    return true;
}

bool Validador::validarCorreo(const string& correo) {
    regex pattern(R"(([\w.-]+)@([\w.-]+)\.([a-zA-Z]{2,6}))");
    return regex_match(correo, pattern);
}

bool Validador::validarTelefono(const string& telefono) {
    regex pattern(R"(^\d{7,10}$)");
    return regex_match(telefono, pattern);
}
