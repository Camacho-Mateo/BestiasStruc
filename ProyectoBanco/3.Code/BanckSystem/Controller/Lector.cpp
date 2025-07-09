#include "Lector.h"
#include <iostream>

using namespace std;

Lector::Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b)
    : cuentaAhorro(ca), cuentaCorriente(cc), buscador(b) {}

void Lector::mostrarDatosPorCuenta(const string& numeroCuenta, bool esAhorro) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        cout << "Cuenta no encontrada." << endl;
        return;
    }

    cout << "\n=== Datos de la Cuenta ===\n";
    cout << "Tipo: " << (esAhorro ? "Ahorro" : "Corriente") << "\n";
    cout << "Numero de Cuenta: " << numeroCuenta << "\n";
    cout << "Cedula: " << (esAhorro ? cuentaAhorro->getCedula(pos) : cuentaCorriente->getCedula(pos)) << "\n";
    cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
    cout << "Telefono: " << (esAhorro ? cuentaAhorro->getTelefono(pos) : cuentaCorriente->getTelefono(pos)) << "\n";
    cout << "Correo: " << (esAhorro ? cuentaAhorro->getCorreo(pos) : cuentaCorriente->getCorreo(pos)) << "\n";
    cout << "Sucursal: " << (esAhorro ? cuentaAhorro->getSucursal(pos) : cuentaCorriente->getSucursal(pos)) << "\n";
}

void Lector::mostrarDatosPorCedula(const string& cedula, bool esAhorro) {
    bool encontrado = false;

    if (esAhorro) {
        for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
            if (cuentaAhorro->getCedula(i) == cedula) {
                cout << "\n=== Cuenta de Ahorro ===\n";
                cout << "Cedula: " << cedula << "\n";
                cout << "Nombre: " << cuentaAhorro->getNombre(i) << "\n";
                cout << "Numero Cuenta: " << cuentaAhorro->getNumeroCuentaStr(i) << "\n";
                cout << "Saldo: $" << cuentaAhorro->getSaldo(i) << "\n";
                cout << "Telefono: " << cuentaAhorro->getTelefono(i) << "\n";
                cout << "Correo: " << cuentaAhorro->getCorreo(i) << "\n";
                cout << "Sucursal: " << cuentaAhorro->getSucursal(i) << "\n";
                encontrado = true;
            }
        }
    } else {
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            if (cuentaCorriente->getCedula(i) == cedula) {
                cout << "\n=== Cuenta Corriente ===\n";
                cout << "Cedula: " << cedula << "\n";
                cout << "Nombre: " << cuentaCorriente->getNombre(i) << "\n";
                cout << "Numero Cuenta: " << cuentaCorriente->getNumeroCuentaStr(i) << "\n";
                cout << "Saldo: $" << cuentaCorriente->getSaldo(i) << "\n";
                cout << "Telefono: " << cuentaCorriente->getTelefono(i) << "\n";
                cout << "Correo: " << cuentaCorriente->getCorreo(i) << "\n";
                cout << "Sucursal: " << cuentaCorriente->getSucursal(i) << "\n";
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron cuentas " << (esAhorro ? "de ahorro" : "corrientes") << " asociadas a esta cedula.\n";
    }
}
