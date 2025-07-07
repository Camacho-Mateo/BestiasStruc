#include "CuentaCorriente.h"
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

size_t CuentaCorriente::contadorCuentas = 2000;

CuentaCorriente::CuentaCorriente() {}

size_t CuentaCorriente::getTotalCuentas() const {
    return cuentas.size();
}

string CuentaCorriente::getCedula(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].cedula : "";
}

string CuentaCorriente::getNombre(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].nombre : "";
}

string CuentaCorriente::getNumeroCuentaStr(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].numeroCuenta : "";
}

double CuentaCorriente::getSaldo(size_t index) const {
    return (index < cuentas.size()) ? cuentas[index].saldo : -1.0;
}

void CuentaCorriente::setSaldo(size_t index, double nuevoSaldo) {
    if (index < cuentas.size()) {
        cuentas[index].saldo = nuevoSaldo;
    }
}

void CuentaCorriente::agregarCuenta(const string& cedula, const string& nombre,
                                     const string& numeroCuenta, double saldoInicial) {
    cuentas.push_back({cedula, nombre, numeroCuenta, saldoInicial});

    if (numeroCuenta.rfind("CC", 0) == 0 && numeroCuenta.length() > 5) {
        size_t num = stoi(numeroCuenta.substr(5));
        if (num > contadorCuentas) {
            contadorCuentas = num;
        }
    }
}

string CuentaCorriente::generarNumeroCuenta() {
    ostringstream oss;
    oss << "CC" << codigoSucursal << "-" << setw(6) << setfill('0') << ++contadorCuentas;
    return oss.str();
}

void CuentaCorriente::setContador(size_t nuevoValor) {
    contadorCuentas = nuevoValor;
}

size_t CuentaCorriente::getContador() {
    return contadorCuentas;
}

void CuentaCorriente::setCodigoSucursal(const string& codigo) {
    if (codigo.size() == 2 && isdigit(codigo[0]) && isdigit(codigo[1])) {
        codigoSucursal = codigo;
    }
}
