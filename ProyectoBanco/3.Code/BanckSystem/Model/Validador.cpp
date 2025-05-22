#include "Validador.h"

void Validador::validar(const string& texto, const string& tipo) {
    if (tipo == "nombre" || tipo == "apellido") {
        regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$");
        if (!regex_match(texto, patron)) {
            throw invalid_argument("Error: " + tipo + " contiene caracteres inválidos.");
        }
    }
    else if (tipo == "telefono") {
        regex patron("^[0-9]{7,15}$"); // Números entre 7 y 15 dígitos
        if (!regex_match(texto, patron)) {
            throw invalid_argument("Error: telefono debe contener solo números válidos.");
        }
    }
    else if (tipo == "correo") {
        regex patron(R"(^[\w\.-]+@[\w\.-]+\.\w{2,4}$)");
        if (!regex_match(texto, patron)) {
            throw invalid_argument("Error: correo electrónico inválido.");
        }
    }
    else if (tipo == "cedula") {
        if (!validarCedulaEcuatoriana(texto)) {
            throw invalid_argument("Error: cédula ecuatoriana inválida.");
        }
    }
    else {
        throw invalid_argument("Error: tipo de validación desconocido.");
    }
}

bool Validador::validarCedulaEcuatoriana(const string& cedula) {
    if (cedula.length() != 10) return false;
    if (!regex_match(cedula, regex("^[0-9]{10}$"))) return false;

    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;

    int tercerDigito = cedula[2] - '0';
    if (tercerDigito >= 6) return false;

    int suma = 0;
    int coeficientes[9] = {2,1,2,1,2,1,2,1,2};

    for (int i = 0; i < 9; i++) {
        int valor = (cedula[i] - '0') * coeficientes[i];
        if (valor >= 10) valor -= 9;
        suma += valor;
    }

    int digitoVerificador = cedula[9] - '0';
    int decenaSuperior = ((suma + 9) / 10) * 10;
    int resultado = decenaSuperior - suma;

    if (resultado == 10) resultado = 0;

    return resultado == digitoVerificador;
}

