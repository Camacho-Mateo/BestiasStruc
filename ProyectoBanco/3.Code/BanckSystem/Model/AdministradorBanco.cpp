#include "AdministradorBanco.h"
#include <iostream>

AdministradorBanco::AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                                       Lector* lectorAhorro, Lector* lectorCorriente)
    : buscadorAhorro(buscadorAhorro), buscadorCorriente(buscadorCorriente),
      lectorAhorro(lectorAhorro), lectorCorriente(lectorCorriente) {}

void AdministradorBanco::buscarPorCedula(const std::string& cedula) {
    std::cout << "\n=== Resultados de búsqueda para cédula: " << cedula << " ===\n";
    
    bool encontrado = false;

    // Buscar en cuentas de ahorro
    if (buscadorAhorro->buscarPorCedula(cedula, true) != -1) {
        lectorAhorro->mostrarDatosPorCedula(cedula, true);
        encontrado = true;
    }

    // Buscar en cuentas corrientes
    if (buscadorCorriente->buscarPorCedula(cedula, false) != -1) {
        lectorCorriente->mostrarDatosPorCedula(cedula, false);
        encontrado = true;
    }

    if (!encontrado) {
        std::cout << "No se encontraron cuentas asociadas a esta cédula.\n";
    }
}

void AdministradorBanco::buscarPorNumeroCuenta() {
    std::string numeroCuenta;
    int tipoCuenta;

    std::cout << "\n=== Búsqueda por número de cuenta ===\n";
    std::cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
    std::cin >> tipoCuenta;
    std::cout << "Número de cuenta: ";
    std::cin >> numeroCuenta;

    if (tipoCuenta == 1) {
        lectorAhorro->mostrarDatosPorCuenta(numeroCuenta, true);
    } else if (tipoCuenta == 2) {
        lectorCorriente->mostrarDatosPorCuenta(numeroCuenta, false);
    } else {
        std::cout << "Tipo de cuenta inválido.\n";
    }
}