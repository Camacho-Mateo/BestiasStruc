#include "Buscador.h"

Buscador::Buscador(CuentaAhorro* ahorro, CuentaCorriente* corriente)
    : cuentaAhorro(ahorro), cuentaCorriente(corriente) {}

int Buscador::buscarPorCedula(const std::string& cedula, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        std::string ced = esAhorro ? cuentaAhorro->getCedula(i) : cuentaCorriente->getCedula(i);
        if (ced == cedula) {
            return i;
        }
    }
    return -1;
}

int Buscador::buscarPorNombre(const std::string& nombre, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        std::string nom = esAhorro ? cuentaAhorro->getNombre(i) : cuentaCorriente->getNombre(i);
        if (nom == nombre) {
            return i;
        }
    }
    return -1;
}

int Buscador::buscarPorCuenta(const std::string& numeroCuenta, bool esAhorro) {
    int totalCuentas = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    for (int i = 0; i < totalCuentas; i++) {
        std::string numCta = esAhorro ? cuentaAhorro->getNumeroCuentaStr(i) : cuentaCorriente->getNumeroCuentaStr(i);
        if (numCta == numeroCuenta) {
            return i;
        }
    }
    return -1;
}