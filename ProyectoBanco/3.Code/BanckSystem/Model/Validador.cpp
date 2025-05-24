#include "Validador.h"

void Validador::validar(const std::string& texto, const std::string& tipo) {
    if (tipo == "nombre" || tipo == "apellido") {
        std::regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$");
        if (!std::regex_match(texto, patron)) {
            throw std::invalid_argument("Error: " + tipo + " contiene caracteres inválidos.");
        }
    }
    else if (tipo == "telefono") {
        std::regex patron("^[0-9]{7,15}$");
        if (!std::regex_match(texto, patron)) {
            throw std::invalid_argument("Error: teléfono debe contener solo números (7-15 dígitos).");
        }
    }
    else if (tipo == "correo") {
        std::regex patron(R"(^[\w\.-]+@[\w\.-]+\.\w{2,4}$)");
        if (!std::regex_match(texto, patron)) {
            throw std::invalid_argument("Error: formato de correo electrónico inválido.");
        }
    }
    else if (tipo == "cedula") {
        if (!validarCedulaEcuatoriana(texto)) {
            throw std::invalid_argument("Error: cédula ecuatoriana inválida.");
        }
    }
    else {
        throw std::invalid_argument("Error: tipo de validación desconocido.");
    }
}

bool Validador::validarCedulaEcuatoriana(const std::string& cedula) {
    if (cedula.length() != 10) return false;
    
    // Validar que todos sean dígitos
    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }
    
    // Validar provincia (primeros dos dígitos)
    int provincia = std::stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;
    
    // Validar tercer dígito
    int tercerDigito = cedula[2] - '0';
    if (tercerDigito > 5) return false;
    
    // Algoritmo de validación
    int coeficientes[9] = {2,1,2,1,2,1,2,1,2};
    int suma = 0;
    
    for (int i = 0; i < 9; i++) {
        int valor = (cedula[i] - '0') * coeficientes[i];
        suma += (valor >= 10) ? valor - 9 : valor;
    }
    
    int digitoVerificador = cedula[9] - '0';
    int resultado = (suma % 10 == 0) ? 0 : 10 - (suma % 10);
    
    return resultado == digitoVerificador;
}