#include "Lector.h"
#include <iostream>
#include <fstream>

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

std::vector<Movimiento> Lector::leerMovimientos() {
    std::vector<Movimiento> movimientos;
    std::ifstream archivo("movimientos.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de movimientos." << std::endl;
        return movimientos;  // vacío
    }

    while (archivo.peek() != EOF) {
        Movimiento mov;

        size_t tamCedula;
        archivo.read(reinterpret_cast<char*>(&tamCedula), sizeof(tamCedula));
        if (archivo.eof()) break;
        mov.cedula.resize(tamCedula);
        archivo.read(&mov.cedula[0], tamCedula);

        size_t tamTipo;
        archivo.read(reinterpret_cast<char*>(&tamTipo), sizeof(tamTipo));
        mov.tipoMovimiento.resize(tamTipo);
        archivo.read(&mov.tipoMovimiento[0], tamTipo);

        archivo.read(reinterpret_cast<char*>(&mov.monto), sizeof(mov.monto));

        size_t tamFecha;
        archivo.read(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha));
        mov.fecha.resize(tamFecha);
        archivo.read(&mov.fecha[0], tamFecha);

        archivo.read(reinterpret_cast<char*>(&mov.saldoFinal), sizeof(mov.saldoFinal));

        movimientos.push_back(mov);
    }

    archivo.close();
    return movimientos;
}

void Lector::mostrarMovimientos() {
    std::vector<Movimiento> movimientos = leerMovimientos();

    if (movimientos.empty()) {
        std::cout << "No hay movimientos registrados." << std::endl;
        return;
    }

    std::cout << "\n=== Movimientos Registrados ===\n";
    for (const auto& mov : movimientos) {
        std::cout << "Cédula: " << mov.cedula << "\n";
        std::cout << "Tipo Movimiento: " << mov.tipoMovimiento << "\n";
        std::cout << "Monto: $" << mov.monto << "\n";
        std::cout << "Fecha: " << mov.fecha << "\n";
        std::cout << "Saldo Final: $" << mov.saldoFinal << "\n";
        std::cout << "---------------------------\n";
    }
}
