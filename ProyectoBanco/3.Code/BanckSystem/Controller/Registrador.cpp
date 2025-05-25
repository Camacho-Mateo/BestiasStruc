#include "Registrador.h"
#include "../Model/Persona.h"
#include "../Model/Fecha.h"
#include "../Model/Validador.h"
#include <iostream>
#include <string>
#include <limits>

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void Registrador::registrar() {
    std::string cedula, nombre, apellido, correo, telefono;
    Fecha fechaNacimiento;

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

    std::cin.ignore();

    while (true) {
        try {
            std::cout << "Ingrese el nombre: ";
            std::getline(std::cin, nombre);
            Validador::validar(nombre, "nombre");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tipoCuenta == 1) {
        cuentaAhorro->agregarCuenta(
            persona.getCedula(),
            persona.getNombre(),
            cuentaAhorro->generarNumeroCuenta(),
            0.0
        );
        std::cout << "Cuenta de ahorro registrada exitosamente.\n";

        administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    } else if (tipoCuenta == 2) {
        cuentaCorriente->agregarCuenta(
            persona.getCedula(),
            persona.getNombre(),
            cuentaCorriente->generarNumeroCuenta(),
            0.0
        );
        std::cout << "Cuenta corriente registrada exitosamente.\n";

        administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    } else {
        std::cout << "Tipo de cuenta inválido.\n";
    }

    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}
