#include "Buscador.h"

Buscador::Buscador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

int Buscador::buscarPorCedula(const std::string& cedula, bool esAhorro) {
    if (esAhorro) {
        for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
            if (cuentaAhorro->getCedula(i) == cedula)
                return static_cast<int>(i);
        }
    } else {
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            if (cuentaCorriente->getCedula(i) == cedula)
                return static_cast<int>(i);
        }
    }
    return -1;
}

int Buscador::buscarPorNombre(const std::string& nombre, bool esAhorro) {
    if (esAhorro) {
        for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
            if (cuentaAhorro->getNombre(i) == nombre)
                return static_cast<int>(i);
        }
    } else {
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            if (cuentaCorriente->getNombre(i) == nombre)
                return static_cast<int>(i);
        }
    }
    return -1;
}

int Buscador::buscarPorCuenta(const std::string& numeroCuenta, bool esAhorro) {
    if (esAhorro) {
        for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
            if (cuentaAhorro->getNumeroCuentaStr(i) == numeroCuenta)
                return static_cast<int>(i);
        }
    } else {
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            if (cuentaCorriente->getNumeroCuentaStr(i) == numeroCuenta)
                return static_cast<int>(i);
        }
    }
    return -1;
}
