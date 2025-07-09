#include "CuentaCorriente.h"
#include <sstream>
#include <iomanip>
#include <cctype>

size_t CuentaCorriente::contadorCuentas = 2000;

CuentaCorriente::CuentaCorriente() {}

size_t CuentaCorriente::getTotalCuentas() const {
    return cedulas.size();
}

std::string CuentaCorriente::getCedula(size_t index) const {
    return (index < cedulas.size()) ? cedulas[index] : "";
}

std::string CuentaCorriente::getNombre(size_t index) const {
    return (index < nombres.size()) ? nombres[index] : "";
}

std::string CuentaCorriente::getNumeroCuentaStr(size_t index) const {
    return (index < numerosCuenta.size()) ? numerosCuenta[index] : "";
}

double CuentaCorriente::getSaldo(size_t index) const {
    return (index < saldos.size()) ? saldos[index] : -1.0;
}

std::string CuentaCorriente::getTelefono(size_t index) const {
    return (index < telefonos.size()) ? telefonos[index] : "";
}

std::string CuentaCorriente::getCorreo(size_t index) const {
    return (index < correos.size()) ? correos[index] : "";
}

std::string CuentaCorriente::getSucursal(size_t index) const {
    return (index < sucursales.size()) ? sucursales[index] : "";
}

void CuentaCorriente::setSaldo(size_t index, double nuevoSaldo) {
    if (index < saldos.size()) {
        saldos[index] = nuevoSaldo;
    }
}

void CuentaCorriente::agregarCuenta(const std::string& cedula, const std::string& nombre,
                                   const std::string& numeroCuenta, double saldoInicial,
                                   const std::string& telefono, const std::string& correo,
                                   const std::string& sucursal) {
    cedulas.push_back(cedula);
    nombres.push_back(nombre);
    numerosCuenta.push_back(numeroCuenta);
    saldos.push_back(saldoInicial);
    telefonos.push_back(telefono);
    correos.push_back(correo);
    sucursales.push_back(sucursal);

    if (numeroCuenta.rfind("CC", 0) == 0 && numeroCuenta.length() > 5) {
        size_t num = std::stoi(numeroCuenta.substr(5));
        if (num > contadorCuentas) {
            contadorCuentas = num;
        }
    }
}

std::string CuentaCorriente::generarNumeroCuenta() {
    std::ostringstream oss;
    oss << "CC" << codigoSucursal << "-" << std::setw(6) << std::setfill('0') << ++contadorCuentas;
    return oss.str();
}

void CuentaCorriente::setCodigoSucursal(const std::string& codigo) {
    if (codigo.size() == 2 && std::isdigit(codigo[0]) && std::isdigit(codigo[1])) {
        codigoSucursal = codigo;
    }
}

void CuentaCorriente::setContador(size_t nuevoValor) {
    contadorCuentas = nuevoValor;
}

size_t CuentaCorriente::getContador() {
    return contadorCuentas;
}
