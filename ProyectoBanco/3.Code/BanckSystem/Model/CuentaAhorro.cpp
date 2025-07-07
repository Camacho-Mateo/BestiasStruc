#include "CuentaAhorro.h"
#include <sstream>
#include <iomanip>
#include <cctype>

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

    if (numeroCuenta.rfind("AH", 0) == 0 && numeroCuenta.length() > 4) {
        size_t num = stoi(numeroCuenta.substr(5)); // salta "AH" + 2 dígitos código + "-" = 5
        if (num > contadorCuentas) {
            contadorCuentas = num;
        }
    }
}

string CuentaAhorro::generarNumeroCuenta() {
    ostringstream oss;
    oss << "AH" << codigoSucursal << "-" << setw(6) << setfill('0') << ++contadorCuentas;
    return oss.str();
}

void CuentaAhorro::setCodigoSucursal(const string& codigo) {
    if (codigo.size() == 2 && isdigit(codigo[0]) && isdigit(codigo[1])) {
        codigoSucursal = codigo;
    }
}

void CuentaAhorro::setContador(size_t nuevoValor) {
    contadorCuentas = nuevoValor;
}

size_t CuentaAhorro::getContador() {
    return contadorCuentas;
}
