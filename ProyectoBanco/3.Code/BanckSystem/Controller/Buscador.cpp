#include "Buscador.h"

Buscador::Buscador(CuentaAhorro* ahorro, CuentaCorriente* corriente)
    : cuentaAhorro(ahorro), cuentaCorriente(corriente) {}

int Buscador::buscarPorCedula(const string& cedula, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        string ced = esAhorro ? cuentaAhorro->getCedula(i) : cuentaCorriente->getCedula(i);
        if (ced == cedula) {
            return i;
        }
    }
    return -1;
}

int Buscador::buscarPorNombre(const string& nombre, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        string nom = esAhorro ? cuentaAhorro->getNombre(i) : cuentaCorriente->getNombre(i);
        if (nom == nombre) {
            return i;
        }
    }
    return -1;
}

int Buscador::buscarPorCuenta(int numeroCuenta, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        int numCta = esAhorro ? cuentaAhorro->getNumeroCuenta(i) : cuentaCorriente->getNumeroCuenta(i);
        if (numCta == numeroCuenta) {
            return i;
        }
    }
    return -1;
}
