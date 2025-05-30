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
    cout << "Numero: " << numeroCuenta << "\n";
    cout << "Cedula: " << (esAhorro ? cuentaAhorro->getCedula(pos) : cuentaCorriente->getCedula(pos)) << "\n";
    cout << "Nombre: " << (esAhorro ? cuentaAhorro->getNombre(pos) : cuentaCorriente->getNombre(pos)) << "\n";
    cout << "Saldo: $" << (esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos)) << "\n";
}

void Lector::mostrarDatosPorCedula(const string& cedula, bool esAhorro) {
    bool encontrado = false;

    if (esAhorro) {
        for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
            if (cuentaAhorro->getCedula(i) == cedula) {
                cout << "\n=== Cuenta de Ahorro ===\n";
                cout << "Cedula: " << cedula << "\n";
                cout << "Nombre: " << cuentaAhorro->getNombre(i) << "\n";
                cout << "Numero Cuenta: " << cuentaAhorro->getNumeroCuentaStr(i) << "\n";
                cout << "Saldo: $" << cuentaAhorro->getSaldo(i) << "\n";
                encontrado = true;
            }
        }
    } else {
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            if (cuentaCorriente->getCedula(i) == cedula) {
                cout << "\n=== Cuenta Corriente ===\n";
                cout << "Cedula: " << cedula << "\n";
                cout << "Nombre: " << cuentaCorriente->getNombre(i) << "\n";
                cout << "Numero Cuenta: " << cuentaCorriente->getNumeroCuentaStr(i) << "\n";
                cout << "Saldo: $" << cuentaCorriente->getSaldo(i) << "\n";
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron cuentas " << (esAhorro ? "de ahorro" : "corrientes") << " asociadas a esta cedula.\n";
    }
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
        cout << "Cedula: " << mov.cedula << "\n";
        cout << "Tipo Movimiento: " << mov.tipoMovimiento << "\n";
        cout << "Monto: $" << mov.monto << "\n";
        cout << "Fecha: " << mov.fecha << "\n";
        cout << "Saldo Final: $" << mov.saldoFinal << "\n";
        cout << "---------------------------\n";
    }
}
