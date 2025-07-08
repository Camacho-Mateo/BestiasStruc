#include "Ordenador.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

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

    bucketSort(registros);
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
    Registro pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        bool menor;
        if (ordenarPorNombre) {
            if (vec[j].nombre != pivot.nombre) {
                menor = vec[j].nombre < pivot.nombre;
            } else if (vec[j].cedula != pivot.cedula) {
                menor = vec[j].cedula < pivot.cedula;
            } else {
                menor = vec[j].numeroCuenta < pivot.numeroCuenta;
            }
        } else {
            if (vec[j].numeroCuenta != pivot.numeroCuenta) {
                menor = vec[j].numeroCuenta < pivot.numeroCuenta;
            } else if (vec[j].nombre != pivot.nombre) {
                menor = vec[j].nombre < pivot.nombre;
            } else {
                menor = vec[j].cedula < pivot.cedula;
            }
        }

        if (menor) {
            ++i;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);
    return i + 1;
}

void Ordenador::bucketSort(vector<Registro>& registros) {
    const int numBuckets = 10;
    vector<vector<Registro>> buckets(numBuckets);

    for (const auto& r : registros) {
        string numStr = r.numeroCuenta.substr(2);
        int numero = stoi(numStr);

        int index = (numero / 100) % numBuckets;
        buckets[index].push_back(r);
    }

    registros.clear();
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end(), [](const Registro& a, const Registro& b) {
            return a.numeroCuenta < b.numeroCuenta;
        });
        registros.insert(registros.end(), bucket.begin(), bucket.end());
    }
}

void Ordenador::imprimir(const vector<Registro>& vec, bool esAhorro) {
    cout << "\n=== Cuentas " << (esAhorro ? "de Ahorro" : "Corrientes") << " Ordenadas ===\n\n";

    cout << left
         << setw(20) << "Nombre"
         << setw(15) << "Cedula"
         << setw(20) << "Cuenta" << "\n";

    cout << string(55, '-') << "\n";

    for (const auto& r : vec) {
        cout << left
             << setw(20) << r.nombre
             << setw(15) << r.cedula
             << setw(20) << r.numeroCuenta
             << "\n";
    }

    cout << "\nTotal de cuentas mostradas: " << vec.size() << "\n";
}
