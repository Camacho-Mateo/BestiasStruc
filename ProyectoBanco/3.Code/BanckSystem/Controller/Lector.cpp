#include "Lector.h"
#include <iostream>

Lector::Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b)
    : cuentaAhorro(ca), cuentaCorriente(cc), buscador(b) {}

void Lector::mostrarDatosPorCuenta(const std::string& numeroCuenta, bool esAhorro) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        std::cout << "Cuenta no encontrada." << std::endl;
        return;
    }

    std::cout << "\n=== Datos de la Cuenta ===\n";
    std::cout << "Tipo: " << (esAhorro ? "Ahorro" : "Corriente") << "\n";
    std::cout << "Número: " << numeroCuenta << "\n";
    std::cout << "Cédula: " << (esAhorro ? cuentaAhorro->getCedula(pos) : cuentaCorriente->getCedula(pos)) << "\n";
    std::cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    std::cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
}

void Lector::mostrarDatosPorCedula(const std::string& cedula, bool esAhorro) {
    int pos = buscador->buscarPorCedula(cedula, esAhorro);
    if (pos == -1) {
        std::cout << "Cliente no encontrado." << std::endl;
        return;
    }

    std::cout << "\n=== Datos del Cliente ===\n";
    std::cout << "Tipo Cuenta: " << (esAhorro ? "Ahorro" : "Corriente") << "\n";
    std::cout << "Cédula: " << cedula << "\n";
    std::cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    std::cout << "Número Cuenta: " << (esAhorro ? cuentaAhorro->getNumeroCuentaStr(pos) : cuentaCorriente->getNumeroCuentaStr(pos)) << "\n";
    std::cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
}