#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <string>
#include <regex>
#include <stdexcept>

class Validador {
public:
    static void validar(const std::string& texto, const std::string& tipo);
    
private:
    static bool validarCedulaEcuatoriana(const std::string& cedula);
};

#endif