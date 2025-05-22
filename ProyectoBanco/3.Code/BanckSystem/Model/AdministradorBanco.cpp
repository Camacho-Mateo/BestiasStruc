#include "AdministradorBanco.h"
#include <iostream>

using namespace std;

AdministradorBanco::AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                                       Lector* lectorAhorro, Lector* lectorCorriente) {
    this->buscadorAhorro = buscadorAhorro;
    this->buscadorCorriente = buscadorCorriente;
    this->lectorAhorro = lectorAhorro;
    this->lectorCorriente = lectorCorriente;
}

void AdministradorBanco::buscarPorCedula(const string& cedula) {
    cout << "Buscando cuentas asociadas a la cédula: " << cedula << endl;

    int filaAhorro = buscadorAhorro->buscarPorCedula(cedula);
    int filaCorriente = buscadorCorriente->buscarPorCedula(cedula);

    if (filaAhorro == -1 && filaCorriente == -1) {
        cout << "No se encontraron cuentas asociadas a esta cédula.\n";
        return;
    }

    if (filaAhorro != -1) {
        cout << "\n--- Cuenta de Ahorro ---\n";
        lectorAhorro->mostrarDatosPorCedula(cedula);
    }

    if (filaCorriente != -1) {
        cout << "\n--- Cuenta Corriente ---\n";
        lectorCorriente->mostrarDatosPorCedula(cedula);
    }
}

void AdministradorBanco::buscarPorNumeroCuenta() {
    string tipo, numero;

    cout << "¿Qué tipo de cuenta desea consultar? (1 = Ahorro, 2 = Corriente): ";
    int opcion;
    cin >> opcion;

    cout << "Ingrese el número de cuenta: ";
    cin >> numero;

    if (opcion == 1) {
        lectorAhorro->mostrarDatosPorCuenta(numero);
    } else if (opcion == 2) {
        lectorCorriente->mostrarDatosPorCuenta(numero);
    } else {
        cout << "Opción inválida.\n";
    }
}
