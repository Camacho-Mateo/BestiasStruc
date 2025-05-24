#include "CuentaCorriente.h"
#include <sstream>
#include <iomanip>

size_t CuentaCorriente::contadorCuentas = 2000;

CuentaCorriente::CuentaCorriente() {}

size_t CuentaCorriente::getTotalCuentas() const {
    return cuentas.size();
}

std::string CuentaCorriente::getCedula(size_t index) const {
    if (index < cuentas.size()) {
        return cuentas[index].cedula;
    }
    return "";
}

std::string CuentaCorriente::getNombre(size_t index) const {
    if (index < cuentas.size()) {
        return cuentas[index].nombre;
    }
    return "";
}

std::string CuentaCorriente::getNumeroCuentaStr(size_t index) const {
    if (index < cuentas.size()) {
        return cuentas[index].numeroCuenta;
    }
    return "";
}

double CuentaCorriente::getSaldo(size_t index) const {
    if (index < cuentas.size()) {
        return cuentas[index].saldo;
    }
    return -1;
}

void CuentaCorriente::setSaldo(size_t index, double nuevoSaldo) {
    if (index < cuentas.size()) {
        cuentas[index].saldo = nuevoSaldo;
    }
}

void CuentaCorriente::agregarCuenta(const std::string& cedula, const std::string& nombre, 
                                  const std::string& numeroCuenta, double saldoInicial) {
    Cuenta nueva;
    nueva.cedula = cedula;
    nueva.nombre = nombre;
    nueva.numeroCuenta = numeroCuenta;
    nueva.saldo = saldoInicial;
    cuentas.push_back(nueva);
}

std::string CuentaCorriente::generarNumeroCuenta() {
    std::ostringstream oss;
    oss << "CC" << std::setw(8) << std::setfill('0') << ++contadorCuentas;
    return oss.str();
}