#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <string>
#include <regex>
#include <stdexcept>

using namespace std;

class Validador {
public:
    static void validar(const string& texto, const string& tipo);

private:
    static bool validarCedulaEcuatoriana(const string& cedula);
};

#endif


