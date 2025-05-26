#include "Lector.h"
#include <iostream>
#include <fstream>

using namespace std;

Lector::Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b)
    : cuentaAhorro(ca), cuentaCorriente(cc), buscador(b) {}

void Lector::mostrarDatosPorCuenta(const string& numeroCuenta, bool esAhorro) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        cout << "Cuenta no encontrada." << endl;
        return;
    }

    cout << "\n=== Datos de la Cuenta ===\n";
    cout << "Tipo: " << (esAhorro ? "Ahorro" : "Corriente") << "\n";
    cout << "Número: " << numeroCuenta << "\n";
    cout << "Cédula: " << (esAhorro ? cuentaAhorro->getCedula(pos) : cuentaCorriente->getCedula(pos)) << "\n";
    cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
}

void Lector::mostrarDatosPorCedula(const string& cedula, bool esAhorro) {
    int pos = buscador->buscarPorCedula(cedula, esAhorro);
    if (pos == -1) {
        cout << "Cliente no encontrado." << endl;
        return;
    }

    cout << "\n=== Datos del Cliente ===\n";
    cout << "Tipo Cuenta: " << (esAhorro ? "Ahorro" : "Corriente") << "\n";
    cout << "Cédula: " << cedula << "\n";
    cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    cout << "Número Cuenta: " << (esAhorro ? cuentaAhorro->getNumeroCuentaStr(pos) : cuentaCorriente->getNumeroCuentaStr(pos)) << "\n";
    cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
}

vector<Movimiento> Lector::leerMovimientos() {
    vector<Movimiento> movimientos;
    ifstream archivo("movimientos.bin", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de movimientos." << endl;
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
    vector<Movimiento> movimientos = leerMovimientos();

    if (movimientos.empty()) {
        cout << "No hay movimientos registrados." << endl;
        return;
    }

    cout << "\n=== Movimientos Registrados ===\n";
    for (const auto& mov : movimientos) {
        cout << "Cédula: " << mov.cedula << "\n";
        cout << "Tipo Movimiento: " << mov.tipoMovimiento << "\n";
        cout << "Monto: $" << mov.monto << "\n";
        cout << "Fecha: " << mov.fecha << "\n";
        cout << "Saldo Final: $" << mov.saldoFinal << "\n";
        cout << "---------------------------\n";
    }
}
