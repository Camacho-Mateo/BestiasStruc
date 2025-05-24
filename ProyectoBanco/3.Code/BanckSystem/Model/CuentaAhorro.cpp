#include "CuentaAhorro.h"
#include <sstream>
#include <iomanip>

using namespace std;

size_t CuentaAhorro::contadorCuentas = 1000;

CuentaAhorro::CuentaAhorro() {}

size_t CuentaAhorro::getTotalCuentas() const {
    return cuentas.size();
}

string CuentaAhorro::getCedula(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].cedula : "";
}

string CuentaAhorro::getNombre(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].nombre : "";
}

string CuentaAhorro::getNumeroCuentaStr(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].numeroCuenta : "";
}

double CuentaAhorro::getSaldo(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].saldo : -1.0;
}

void CuentaAhorro::setSaldo(size_t index, double nuevoSaldo) {
    if (index < cuentas.size()) {
        cuentas[index].saldo = nuevoSaldo;
    }
}

void CuentaAhorro::agregarCuenta(const string& cedula, const string& nombre, 
                               const string& numeroCuenta, double saldoInicial) {
    cuentas.push_back({cedula, nombre, numeroCuenta, saldoInicial});
}

string CuentaAhorro::generarNumeroCuenta() {
    ostringstream oss;
    oss << "AH" << setw(8) << setfill('0') << ++contadorCuentas;
    return oss.str();
}