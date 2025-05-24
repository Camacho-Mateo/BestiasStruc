#include "Registrador.h"
#include "../Model/Persona.h"
#include "../Model/Fecha.h"
#include "../Model/Validador.h"
#include <iostream>
#include <string>

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void Registrador::registrar() {
    std::string cedula, nombre, apellido, correo, telefono;
    Fecha fechaNacimiento;

    // Validación de cédula
    while (true) {
        try {
            std::cout << "Ingrese la cédula: ";
            std::cin >> cedula;
            Validador::validar(cedula, "cedula");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // Validación de nombre
    while (true) {
        try {
            std::cout << "Ingrese el nombre: ";
            std::cin.ignore();
            std::getline(std::cin, nombre);
            Validador::validar(nombre, "nombre");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // Validación de apellido
    while (true) {
        try {
            std::cout << "Ingrese el apellido: ";
            std::getline(std::cin, apellido);
            Validador::validar(apellido, "apellido");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // Validación de correo
    while (true) {
        try {
            std::cout << "Ingrese el correo: ";
            std::getline(std::cin, correo);
            Validador::validar(correo, "correo");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // Validación de teléfono
    while (true) {
        try {
            std::cout << "Ingrese el teléfono: ";
            std::getline(std::cin, telefono);
            Validador::validar(telefono, "telefono");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA):\n";
    fechaNacimiento.pedirFecha();

    Persona persona(cedula, nombre, apellido, correo, telefono, fechaNacimiento);

    int tipoCuenta;
    std::cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
    std::cin >> tipoCuenta;

    if (tipoCuenta == 1) {
        cuentaAhorro->agregarCuenta(persona.getCedula(), persona.getNombre(), 
                                   cuentaAhorro->generarNumeroCuenta(), 0.0);
        std::cout << "Cuenta de ahorro registrada exitosamente.\n";
    } else if (tipoCuenta == 2) {
        cuentaCorriente->agregarCuenta(persona.getCedula(), persona.getNombre(), 
                                      cuentaCorriente->generarNumeroCuenta(), 0.0);
        std::cout << "Cuenta corriente registrada exitosamente.\n";
    } else {
        std::cout << "Tipo de cuenta inválido.\n";
    }
}