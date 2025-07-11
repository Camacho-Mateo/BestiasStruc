#include "CuentaAhorro.h"
#include <sstream>
#include <iomanip>
#include <cctype>

size_t CuentaAhorro::contadorCuentas = 1000;

CuentaAhorro::CuentaAhorro() {}

size_t CuentaAhorro::getTotalCuentas() const {
    return cedulas.size();
}

std::string CuentaAhorro::getCedula(size_t index) const {
    return (index < cedulas.size()) ? cedulas[index] : "";
}

std::string CuentaAhorro::getNombre(size_t index) const {
    return (index < nombres.size()) ? nombres[index] : "";
}

std::string CuentaAhorro::getNumeroCuentaStr(size_t index) const {
    return (index < numerosCuenta.size()) ? numerosCuenta[index] : "";
}

double CuentaAhorro::getSaldo(size_t index) const {
    return (index < saldos.size()) ? saldos[index] : -1.0;
}

std::string CuentaAhorro::getTelefono(size_t index) const {
    return (index < telefonos.size()) ? telefonos[index] : "";
}

std::string CuentaAhorro::getCorreo(size_t index) const {
    return (index < correos.size()) ? correos[index] : "";
}

std::string CuentaAhorro::getSucursal(size_t index) const {
    return (index < sucursales.size()) ? sucursales[index] : "";
}

std::string CuentaAhorro::getFechaRegistro(size_t index) const {
    return (index < fechasRegistro.size()) ? fechasRegistro[index] : "";
}

// Setters

void CuentaAhorro::setCedula(size_t index, const std::string& nuevaCedula) {
    if (index < cedulas.size()) {
        cedulas[index] = nuevaCedula;
    }
}

void CuentaAhorro::setNombre(size_t index, const std::string& nuevoNombre) {
    if (index < nombres.size()) {
        nombres[index] = nuevoNombre;
    }
}

void CuentaAhorro::setTelefono(size_t index, const std::string& nuevoTelefono) {
    if (index < telefonos.size()) {
        telefonos[index] = nuevoTelefono;
    }
}

void CuentaAhorro::setCorreo(size_t index, const std::string& nuevoCorreo) {
    if (index < correos.size()) {
        correos[index] = nuevoCorreo;
    }
}

void CuentaAhorro::setSucursal(size_t index, const std::string& nuevaSucursal) {
    if (index < sucursales.size()) {
        sucursales[index] = nuevaSucursal;
    }
}

void CuentaAhorro::setFechaRegistro(size_t index, const std::string& nuevaFecha) {
    if (index < fechasRegistro.size()) {
        fechasRegistro[index] = nuevaFecha;
    }
}

void CuentaAhorro::setSaldo(size_t index, double nuevoSaldo) {
    if (index < saldos.size()) {
        saldos[index] = nuevoSaldo;
    }
}

void CuentaAhorro::agregarCuenta(const std::string& cedula, const std::string& nombre,
                                 const std::string& numeroCuenta, double saldoInicial,
                                 const std::string& telefono, const std::string& correo,
                                 const std::string& sucursal,
                                 const std::string& fechaRegistro) {
    cedulas.push_back(cedula);
    nombres.push_back(nombre);
    numerosCuenta.push_back(numeroCuenta);
    saldos.push_back(saldoInicial);
    telefonos.push_back(telefono);
    correos.push_back(correo);
    sucursales.push_back(sucursal);
    fechasRegistro.push_back(fechaRegistro);

    if (numeroCuenta.rfind("AH", 0) == 0 && numeroCuenta.length() > 4) {
        size_t num = std::stoi(numeroCuenta.substr(5));
        if (num > contadorCuentas) {
            contadorCuentas = num;
        }
    }
}

std::string CuentaAhorro::generarNumeroCuenta() {
    std::ostringstream oss;
    oss << "AH" << codigoSucursal << "-" << std::setw(6) << std::setfill('0') << ++contadorCuentas;
    return oss.str();
}

void CuentaAhorro::setCodigoSucursal(const std::string& codigo) {
    if (codigo.size() == 2 && std::isdigit(codigo[0]) && std::isdigit(codigo[1])) {
        codigoSucursal = codigo;
    }
}

void CuentaAhorro::setContador(size_t nuevoValor) {
    contadorCuentas = nuevoValor;
}

size_t CuentaAhorro::getContador() {
    return contadorCuentas;
}
