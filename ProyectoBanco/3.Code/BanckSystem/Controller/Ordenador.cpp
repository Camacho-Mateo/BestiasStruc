#include "Ordenador.h"
#include <iostream>
#include <iomanip>

using namespace std;

Ordenador::Ordenador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void Ordenador::ordenarPorNombre(bool esAhorro) {
    vector<Registro> registros;
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();

    for (size_t i = 0; i < total; ++i) {
        Registro r;
        r.nombre = esAhorro ? cuentaAhorro->getNombre(i) : cuentaCorriente->getNombre(i);
        r.cedula = esAhorro ? cuentaAhorro->getCedula(i) : cuentaCorriente->getCedula(i);
        r.numeroCuenta = esAhorro ? cuentaAhorro->getNumeroCuentaStr(i) : cuentaCorriente->getNumeroCuentaStr(i);
        r.saldo = esAhorro ? cuentaAhorro->getSaldo(i) : cuentaCorriente->getSaldo(i);
        registros.push_back(r);
    }

    quickSort(registros, 0, registros.size() - 1, true);
    imprimir(registros, esAhorro);
}

void Ordenador::ordenarPorNumeroCuenta(bool esAhorro) {
    vector<Registro> registros;
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();

    for (size_t i = 0; i < total; ++i) {
        Registro r;
        r.nombre = esAhorro ? cuentaAhorro->getNombre(i) : cuentaCorriente->getNombre(i);
        r.cedula = esAhorro ? cuentaAhorro->getCedula(i) : cuentaCorriente->getCedula(i);
        r.numeroCuenta = esAhorro ? cuentaAhorro->getNumeroCuentaStr(i) : cuentaCorriente->getNumeroCuentaStr(i);
        r.saldo = esAhorro ? cuentaAhorro->getSaldo(i) : cuentaCorriente->getSaldo(i);
        registros.push_back(r);
    }

    quickSort(registros, 0, registros.size() - 1, false);
    imprimir(registros, esAhorro);
}

void Ordenador::quickSort(vector<Registro>& vec, int low, int high, bool ordenarPorNombre) {
    if (low < high) {
        int pi = partition(vec, low, high, ordenarPorNombre);
        quickSort(vec, low, pi - 1, ordenarPorNombre);
        quickSort(vec, pi + 1, high, ordenarPorNombre);
    }
}

int Ordenador::partition(vector<Registro>& vec, int low, int high, bool ordenarPorNombre) {
    string pivot = ordenarPorNombre ? vec[high].nombre : vec[high].numeroCuenta;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        string valor = ordenarPorNombre ? vec[j].nombre : vec[j].numeroCuenta;
        if (valor < pivot) {
            ++i;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}

void Ordenador::imprimir(const vector<Registro>& vec, bool esAhorro) {
    cout << "\n=== Cuentas " << (esAhorro ? "de Ahorro" : "Corrientes") << " Ordenadas ===\n\n";

    // Encabezado de tabla
    cout << left
         << setw(20) << "Nombre"
         << setw(15) << "Cedula"
         << setw(20) << "Cuenta"
         << setw(10) << "Saldo" << "\n";

    cout << string(65, '-') << "\n";

    for (const auto& r : vec) {
        cout << left
             << setw(20) << r.nombre
             << setw(15) << r.cedula
             << setw(20) << r.numeroCuenta
             << fixed << setprecision(2)
             << "$" << setw(9) << r.saldo
             << "\n";
    }

    cout << "\nTotal de cuentas mostradas: " << vec.size() << "\n";
}
