#include "AdministradorBanco.h"
#include <iostream>

using namespace std;

AdministradorBanco::AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                                       Lector* lectorAhorro, Lector* lectorCorriente)
    : buscadorAhorro(buscadorAhorro), buscadorCorriente(buscadorCorriente),
      lectorAhorro(lectorAhorro), lectorCorriente(lectorCorriente) {}

void AdministradorBanco::buscarPorCedula(const string& cedula) {
    cout << "\n=== Resultados de búsqueda para cédula: " << cedula << " ===\n";
    
    bool encontrado = false;

    if (buscadorAhorro->buscarPorCedula(cedula, true) != -1) {
        lectorAhorro->mostrarDatosPorCedula(cedula, true);
        encontrado = true;
    }

    if (buscadorCorriente->buscarPorCedula(cedula, false) != -1) {
        lectorCorriente->mostrarDatosPorCedula(cedula, false);
        encontrado = true;
    }

    if (!encontrado) {
        cout << "No se encontraron cuentas asociadas a esta cédula.\n";
    }
}

void AdministradorBanco::buscarPorNumeroCuenta() {
    string numeroCuenta;
    int tipoCuenta;

    cout << "\n=== Búsqueda por número de cuenta ===\n";
    cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
    cin >> tipoCuenta;
    cout << "Número de cuenta: ";
    cin >> numeroCuenta;

    if (tipoCuenta == 1) {
        lectorAhorro->mostrarDatosPorCuenta(numeroCuenta, true);
    } else if (tipoCuenta == 2) {
        lectorCorriente->mostrarDatosPorCuenta(numeroCuenta, false);
    } else {
        cout << "Tipo de cuenta inválido.\n";
    }
}
