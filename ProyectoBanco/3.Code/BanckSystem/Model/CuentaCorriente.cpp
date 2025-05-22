#include "CuentaCorriente.h"
#include <iostream>

CuentaCorriente::CuentaCorriente() {
    filas = 0;
    columnas = 3; // cedula, nombre, numeroCuenta (como string)
    datos = nullptr;
    saldos = nullptr;
}

CuentaCorriente::~CuentaCorriente() {
    if (datos != nullptr) {
        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }
        delete[] datos;
    }
    delete[] saldos;
}

void CuentaCorriente::resize(int nuevaCantidad) {
    string** tempDatos = new string*[nuevaCantidad];
    double* tempSaldos = new double[nuevaCantidad];

    for (int i = 0; i < nuevaCantidad; i++) {
        tempDatos[i] = new string[columnas];
        if (i < filas) {
            for (int j = 0; j < columnas; j++) {
                tempDatos[i][j] = datos[i][j];
            }
            tempSaldos[i] = saldos[i];
        } else {
            for (int j = 0; j < columnas; j++) {
                tempDatos[i][j] = "";
            }
            tempSaldos[i] = 0.0;
        }
    }

    if (datos != nullptr) {
        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }
        delete[] datos;
    }
    delete[] saldos;

    datos = tempDatos;
    saldos = tempSaldos;
    filas = nuevaCantidad;
}

int CuentaCorriente::getTotalCuentas() {
    return filas;
}

string CuentaCorriente::getCedula(int fila) {
    if (fila >= 0 && fila < filas) return datos[fila][0];
    else return "";
}

string CuentaCorriente::getNombre(int fila) {
    if (fila >= 0 && fila < filas) return datos[fila][1];
    else return "";
}

int CuentaCorriente::getNumeroCuenta(int fila) {
    if (fila >= 0 && fila < filas) {
        try {
            return stoi(datos[fila][2]);
        } catch (...) {
            return -1;
        }
    } else return -1;
}

double CuentaCorriente::getSaldo(int fila) {
    if (fila >= 0 && fila < filas) return saldos[fila];
    else return -1;
}

void CuentaCorriente::setSaldo(int fila, double nuevoSaldo) {
    if (fila >= 0 && fila < filas) {
        saldos[fila] = nuevoSaldo;
    }
}

void CuentaCorriente::agregarCuenta(const string& cedula, const string& nombre, int numeroCuenta, double saldo) {
    resize(filas + 1);
    datos[filas - 1][0] = cedula;
    datos[filas - 1][1] = nombre;
    datos[filas - 1][2] = to_string(numeroCuenta);
    saldos[filas - 1] = saldo;
}
